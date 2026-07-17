// ═══════════════════════════════════════════════════════════════════
//  Virtus Scale — nRF52840 + NAU7802 load-cell firmware
//
//  Speaks the Virtus Harvest app protocol over Nordic UART Service:
//    TX (scale → app), newline-terminated:
//      P:<net>,L:<gross>,S:<stable 0/1>,U:0
//      INFO:firmware=x.y.z,model=VirtusScale,serial=XXXXXX
//      STATUS:batt=87,batt_v=3.92,ext_v=12.4,charging=0
//    RX (app → scale):
//      TARE / ZERO / CAL:<f> / SENS:<mV/V> / CAP:<kg> / RESTORE
//      INFO / STATUS / FIRMWARE / OTA_CHECK / RESET
//      SCAN / PINTEST / FINDBUS   (bring-up diagnostics)
//
//  Board:  Adafruit nRF52 core (tested target: pca10056 / nRF52840)
//  Libs:   Adafruit Bluefruit (bundled with core),
//          SparkFun Qwiic Scale NAU7802
// ═══════════════════════════════════════════════════════════════════

#include <Adafruit_TinyUSB.h>
#include <bluefruit.h>
#include <Wire.h>
#include <SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

// ───────────────────────── CONFIG ─────────────────────────
#define FIRMWARE_VERSION   "1.3.3"
#define MODEL_NAME         "VirtusScale"
#define BLE_NAME           "HarvestScale"   // matches app's scan filter
#define MAX_CONNECTIONS    4                // simultaneous BLE clients

// I2C pins the NAU7802 is wired to. Defaults to the selected board's
// standard Wire pins: on the pca10056 target that's P0.26/P0.27 (the
// custom Virtus board routing), on a Feather nRF52840 it's the pins
// labeled SDA/SCL. Override with explicit numbers for custom routing.
#define I2C_SDA_PIN        PIN_WIRE_SDA    // custom board: 26 = P0.26
#define I2C_SCL_PIN        PIN_WIRE_SCL    // custom board: 27 = P0.27
#define NAU_DRDY_PIN       7               // P0.07 — wired but unused (I2C polling)
#define ACCEL_INT_PIN      6               // P0.06 — LIS2DH12 INT1, future motion wake

// NAU7802 is I2C-only, fixed address 0x2A
#define NAU_ADDR           0x2A
#define NAU_GAIN           NAU7802_GAIN_128
#define NAU_LDO            NAU7802_LDO_3V0  // LDO output feeding the load cell
#define NAU_RATE           NAU7802_SPS_10

// Battery sense. Boards whose variant defines PIN_VBAT (Feather
// nRF52840 / Sense: onboard 100k/100k divider) are detected
// automatically; otherwise set an analog pin here, or -1 for none.
// DIVIDER = Vbat / Vpin (2.0 for a 100k/100k divider).
#if defined(PIN_VBAT)
  #define BATT_SENSE_PIN   PIN_VBAT
#else
  #define BATT_SENSE_PIN   -1
#endif
#define BATT_DIVIDER       2.0f

// Defaults used until the app pushes CAL/SENS/CAP (kept in flash)
#define DEFAULT_SENS_MVV   2.0f      // load-cell sensitivity, mV/V
#define DEFAULT_CAPACITY   1000.0f   // rated capacity, kg
#define DEFAULT_CALFACTOR  1.0f
#define DEFAULT_RESOLUTION 10.0f     // reported weight rounds to this (kg);
                                     // change at runtime with RES:<kg>, e.g.
                                     // RES:0.1 for bench testing

// Stability: reading is "stable" when the spread of the last
// STABLE_WINDOW readings is under STABLE_BAND (kg)
#define STABLE_WINDOW      8
#define STABLE_BAND        0.5f

// ─────────────────────── GLOBALS ───────────────────────
NAU7802 nau;
BLEUart  bleuart;
BLEDis   bledis;
BLEDfu   bledfu;    // OTA DFU entry service — lets nRF Connect flash updates

using namespace Adafruit_LittleFS_Namespace;
#define CAL_FILE "/virtus_cal.dat"

struct CalData {
  uint32_t magic;          // 0x56495254 "VIRT" when valid
  float    calFactor;
  float    sensMvV;
  float    capacity;
  int32_t  tareOffset;     // raw counts at zero
  float    resolution;     // reported weight rounds to this (kg)
};
CalData cal;

float   countsPerKg   = 1.0f;
int32_t rawFiltered   = 0;
bool    haveReading   = false;
bool    nauReady      = false;
uint32_t lastNauRetry = 0;
float   recentNet[STABLE_WINDOW];
uint8_t recentIdx     = 0;
uint8_t recentCount   = 0;
char    serialNum[13];
String  rxLine;
uint32_t lastStatusMs = 0;
uint32_t lastSampleMs = 0;   // last successful NAU7802 conversion

// ─────────────────────── CALIBRATION MATH ───────────────────────
// Full-scale ADC input is ±(AVDD/gain); cell output at rated load is
// sens(mV/V) × AVDD. AVDD cancels:  counts@rated = sens·gain/1000 · 2^23
void recomputeScale() {
  float sens = (cal.sensMvV  > 0.01f) ? cal.sensMvV  : DEFAULT_SENS_MVV;
  float capk = (cal.capacity > 0.01f) ? cal.capacity : DEFAULT_CAPACITY;
  countsPerKg = (sens * 128.0f / 1000.0f) * 8388608.0f / capk;
}

void calDefaults() {
  cal.magic      = 0x56495254;
  cal.calFactor  = DEFAULT_CALFACTOR;
  cal.sensMvV    = DEFAULT_SENS_MVV;
  cal.capacity   = DEFAULT_CAPACITY;
  cal.tareOffset = 0;
  cal.resolution = DEFAULT_RESOLUTION;
}

void calSave() {
  InternalFS.remove(CAL_FILE);
  File f(InternalFS);
  if (f.open(CAL_FILE, FILE_O_WRITE)) {
    f.write((uint8_t*)&cal, sizeof(cal));
    f.close();
  }
}

void calLoad() {
  int got = 0;
  File f(InternalFS);
  if (f.open(CAL_FILE, FILE_O_READ)) {
    got = f.read((uint8_t*)&cal, sizeof(cal));
    f.close();
  }
  // struct grew in v1.3.0 — a short read means stale layout, start fresh
  if (got != (int)sizeof(cal) || cal.magic != 0x56495254) calDefaults();
  if (cal.resolution < 0.01f || cal.resolution > 1000.0f) cal.resolution = DEFAULT_RESOLUTION;
  recomputeScale();
}

// ─────────────────────── BLE OUTPUT ───────────────────────
bool bleReady = false;   // true once Bluefruit.begin() has succeeded

// fan out to every connected client that enabled notifications.
// BLEUart::write sends ONE notification per call and silently drops
// anything longer than the connection MTU allows — so slice every
// line into MTU-sized chunks (clients reassemble on the newline).
void bleSend(const String& s) {
  if (bleReady) {
    String line = s + "\n";
    const uint8_t* p = (const uint8_t*)line.c_str();
    size_t total = line.length();
    for (uint16_t h = 0; h < BLE_MAX_CONNECTION; h++) {
      if (!Bluefruit.connected(h) || !bleuart.notifyEnabled(h)) continue;
      BLEConnection* conn = Bluefruit.Connection(h);
      size_t maxChunk = conn ? (size_t)(conn->getMtu() - 3) : 20;
      for (size_t off = 0; off < total; off += maxChunk) {
        size_t n = total - off;
        if (n > maxChunk) n = maxChunk;
        bleuart.write(h, p + off, n);
      }
    }
  }
  Serial.println(s);
}

void sendInfo() {
  bleSend(String("INFO:firmware=") + FIRMWARE_VERSION +
          ",model=" + MODEL_NAME + ",serial=" + serialNum);
}

void sendStatus() {
  String s = "STATUS:";
  if (BATT_SENSE_PIN >= 0) {
    analogReference(AR_INTERNAL);      // 0.6 V ref × gain 1/6 → 3.6 V range
    analogReadResolution(12);
    float vpin = analogRead(BATT_SENSE_PIN) * 3.6f / 4095.0f;
    float vbat = vpin * BATT_DIVIDER;
    int pct = (int)((vbat - 3.30f) / (4.20f - 3.30f) * 100.0f);
    pct = constrain(pct, 0, 100);
    s += "batt=" + String(pct) + ",batt_v=" + String(vbat, 2) + ",";
  }
  s += "charging=0";
  bleSend(s);
}

// ─────────────────────── I2C BRING-UP HELPERS ───────────────────────
// nRF52 TWIM cannot do the classic 0-byte-write address probe — a
// documented hardware limitation (zero-length transfers generate no
// completion events), so all detection here probes with a 1-byte READ.
bool i2cProbe(uint8_t addr) {
  bool present = (Wire.requestFrom(addr, (size_t)1) == 1);
  while (Wire.available()) Wire.read();
  return present;
}

// Walks the whole bus and reports every device that ACKs a read.
void i2cScan() {
  uint8_t found = 0;
  bleSend(String("SCAN: SDA=P") + I2C_SDA_PIN + " SCL=P" + I2C_SCL_PIN + " (read-probe) ...");
  for (uint8_t addr = 1; addr < 127; addr++) {
    if (i2cProbe(addr)) {
      found++;
      const char* who = "";
      if (addr == NAU_ADDR) who = "  <-- NAU7802";
      if (addr == 0x18 || addr == 0x19) who = "  <-- LIS2DH12";
      // Feather nRF52840 Sense onboard sensors, for reference-rig tests
      if (addr == 0x6A) who = "  <-- LSM6DS33 (Feather IMU)";
      if (addr == 0x1C) who = "  <-- LIS3MDL (Feather mag)";
      if (addr == 0x44) who = "  <-- SHT31 (Feather humidity)";
      if (addr == 0x39) who = "  <-- APDS9960 (Feather light)";
      if (addr == 0x77) who = "  <-- BMP280 (Feather pressure)";
      bleSend(String("SCAN: device at 0x") + String(addr, HEX) + who);
    }
  }
  if (!found) {
    // raw write-probe error code, to tell failure modes apart
    Wire.beginTransmission(NAU_ADDR);
    uint8_t e = Wire.endTransmission();
    bleSend(String("SCAN: no devices found (0x2A write-err=") + e +
            ", 2=addr NACK: check wiring/power, 4=bus error: check SDA/SCL lines)");
  }
}

bool nauInit() {
  if (!i2cProbe(NAU_ADDR)) return false;   // chip must ACK a real read first

  // The library's begin() gates on a 0-byte-write ACK check that can
  // false-fail on nRF52 TWIM. It binds the Wire port before that check,
  // so when the read-probe above already proved the chip is present,
  // fall back to running its init sequence manually.
  if (!nau.begin(Wire)) {
    bleSend("NAU7802: begin() probe failed (nRF52 0-byte write) — manual init");
    nau.reset();
    delay(10);
    if (!nau.powerUp()) {
      bleSend("NAU7802 ACKs reads but power-up failed");
      return false;
    }
  }
  nau.setLDO(NAU_LDO);
  nau.setGain(NAU_GAIN);
  nau.setSampleRate(NAU_RATE);
  nau.calibrateAFE();            // re-cal analog front end after config
  haveReading = false;
  recentCount = 0;
  lastSampleMs = millis();
  bleSend(String("NAU7802 ready (revision 0x") + String(nau.getRevisionCode(), HEX) + ")");
  return true;
}

// FINDBUS: brute-force every plausible GPIO pair as SDA/SCL and probe
// for the NAU7802 (0x2A) and LIS2DH12 (0x18/0x19). If the sensors are
// wired to ANY pins, this finds them; if it hits nothing anywhere, the
// chips are not ACKing at all (power/solder) regardless of pin choice.
bool findbusSkip(uint8_t p) {
  return p == 0 || p == 1 ||          // P0.00/P0.01: 32 kHz crystal
         p == 9 || p == 10 ||         // P0.09/P0.10: NFC antenna by default
         p == 18;                     // P0.18: reset
}

void findBus() {
  bleSend("FINDBUS: sweeping all pin pairs, probing 0x2A/0x18/0x19 ...");
  int hits = 0, tested = 0;
  for (uint8_t sda = 2; sda < PINS_COUNT; sda++) {
    if (findbusSkip(sda)) continue;
    for (uint8_t scl = 2; scl < PINS_COUNT; scl++) {
      if (scl == sda || findbusSkip(scl)) continue;

      // I2C needs both lines idle-high; a stuck-low net can hang TWIM,
      // so check levels with pull-ups before committing the peripheral
      pinMode(sda, INPUT_PULLUP);
      pinMode(scl, INPUT_PULLUP);
      delayMicroseconds(50);
      bool ok = digitalRead(sda) && digitalRead(scl);
      pinMode(sda, INPUT);
      pinMode(scl, INPUT);
      if (!ok) continue;

      Wire.end();
      Wire.setPins(sda, scl);
      Wire.begin();
      tested++;
      bool nauHit = i2cProbe(NAU_ADDR);
      bool accHit = i2cProbe(0x18) || i2cProbe(0x19);
      if (nauHit || accHit) {
        hits++;
        bleSend(String("FINDBUS: HIT  SDA=P") + sda + " SCL=P" + scl +
                (nauHit ? "  NAU7802" : "") + (accHit ? "  LIS2DH12" : ""));
      }
    }
  }
  Wire.end();
  Wire.setPins(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.begin();
  if (hits) {
    bleSend(String("FINDBUS: done, ") + hits +
            " hit(s) — set I2C_SDA_PIN/I2C_SCL_PIN to the pair above");
  } else {
    bleSend(String("FINDBUS: ") + tested + " pairs tested, no ACK anywhere — "
            "sensors are unpowered or not soldered (hardware, not pins)");
  }
}

// PINTEST: takes over SDA/SCL as plain GPIO so the nets can be
// verified with a multimeter at the sensor pads, then restores I2C.
void pinTest() {
  Wire.end();

  // idle level with no pulls: 1 = external pull-up (or short to VDD)
  pinMode(I2C_SDA_PIN, INPUT);
  pinMode(I2C_SCL_PIN, INPUT);
  delay(5);
  bleSend(String("PINTEST: floating levels  SDA=") + digitalRead(I2C_SDA_PIN) +
          " SCL=" + digitalRead(I2C_SCL_PIN) + "  (1=pulled up, 0=low/floating)");

  pinMode(I2C_SDA_PIN, OUTPUT);
  pinMode(I2C_SCL_PIN, OUTPUT);
  bleSend("PINTEST: toggling 10 s — probe SDA/SCL at the SENSOR pads");
  for (int i = 0; i < 10; i++) {
    bool sdaHigh = (i % 2) == 0;
    digitalWrite(I2C_SDA_PIN, sdaHigh);
    digitalWrite(I2C_SCL_PIN, !sdaHigh);
    bleSend(String("PINTEST: SDA=") + (sdaHigh ? "3.3V" : "0V") +
            "  SCL=" + (sdaHigh ? "0V" : "3.3V"));
    delay(1000);
  }

  pinMode(I2C_SDA_PIN, INPUT);
  pinMode(I2C_SCL_PIN, INPUT);
  Wire.setPins(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.begin();
  bleSend("PINTEST: done — I2C restored");
}

// ─────────────────────── COMMANDS ───────────────────────
void handleCommand(String cmd) {
  cmd.trim();
  if (!cmd.length()) return;
  Serial.println("CMD: " + cmd);

  if (cmd == "TARE" || cmd == "ZERO") {
    if (haveReading) {
      cal.tareOffset = rawFiltered;
      calSave();
      recentCount = 0;               // stability resets after tare
      bleSend("TARE_OK");
    }
  }
  else if (cmd.startsWith("CAL:")) {
    float f = cmd.substring(4).toFloat();
    if (f > 0.0001f) { cal.calFactor = f; calSave(); bleSend("CAL_OK"); }
  }
  else if (cmd.startsWith("SENS:")) {
    float f = cmd.substring(5).toFloat();
    if (f > 0.01f) { cal.sensMvV = f; recomputeScale(); calSave(); bleSend("SENS_OK"); }
  }
  else if (cmd.startsWith("CAP:")) {
    float f = cmd.substring(4).toFloat();
    if (f > 0.01f) { cal.capacity = f; recomputeScale(); calSave(); bleSend("CAP_OK"); }
  }
  else if (cmd.startsWith("RES:")) {
    float f = cmd.substring(4).toFloat();
    if (f >= 0.01f && f <= 1000.0f) { cal.resolution = f; calSave(); bleSend("RES_OK"); }
  }
  else if (cmd == "RESTORE") {
    calDefaults();
    recomputeScale();
    calSave();
    bleSend("RESTORE_OK");
  }
  else if (cmd == "SCAN")                      i2cScan();
  else if (cmd == "PINTEST")                   pinTest();
  else if (cmd == "FINDBUS")                   findBus();
  else if (cmd == "INFO" || cmd == "FIRMWARE") sendInfo();
  else if (cmd == "STATUS")                    sendStatus();
  else if (cmd == "OTA_CHECK")                 bleSend("OTA_UP_TO_DATE");
  else if (cmd.startsWith("OTA_BEGIN"))        bleSend("OTA_ERR:use nRF52 DFU, not BLE-UART OTA");
  else if (cmd == "RESET")                     NVIC_SystemReset();
}

void pollBleRx() {
  while (bleuart.available()) {
    char c = (char)bleuart.read();
    if (c == '\n' || c == '\r') {
      handleCommand(rxLine);
      rxLine = "";
    } else if (rxLine.length() < 64) {
      rxLine += c;
    }
  }
}

// ─────────────────────── SETUP ───────────────────────
// advertising stops when a client connects — flag a restart so the
// next client can also find us. The restart happens in loop(), not
// here: calling Advertising.start() from inside the BLE event
// callback can race the connection setup.
volatile bool advRestartPending = false;
volatile uint32_t infoDueAt = 0;   // when to volunteer INFO+STATUS after a connect

void connectCallback(uint16_t conn_hdl) {
  (void)conn_hdl;
  advRestartPending = true;
  // the app's own INFO/STATUS request often races the notification
  // setup and its one-shot reply gets lost — send them unsolicited
  // once the pipe has had time to open
  infoDueAt = millis() + 2500;
}

void setup() {
  Serial.begin(115200);

  snprintf(serialNum, sizeof(serialNum), "%08lX",
           (unsigned long)NRF_FICR->DEVICEID[0]);

  InternalFS.begin();
  calLoad();

  // NAU7802 init — setPins must come before begin
  Wire.setPins(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.begin();
  i2cScan();
  nauReady = nauInit();
  if (!nauReady) Serial.println("ERR: NAU7802 not found at 0x2A — retrying in loop");

  // BLE init
  bleReady = Bluefruit.begin(MAX_CONNECTIONS, 0);
  Serial.println(bleReady ? "BLE stack started"
                          : "ERR: BLE stack failed to start (connection count too high?)");
  Bluefruit.setTxPower(4);
  Bluefruit.setName(BLE_NAME);
  Bluefruit.Periph.setConnectCallback(connectCallback);

  bledfu.begin();              // must start before other services
  bledis.setManufacturer("Virtus");
  bledis.setModel(MODEL_NAME);
  bledis.begin();
  bleuart.begin();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);   // app filters on NUS UUID
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);

  Serial.println(String("Virtus Scale v") + FIRMWARE_VERSION +
                 " advertising as " + BLE_NAME);
}

// ─────────────────────── LOOP ───────────────────────
void loop() {
  if (advRestartPending) {
    advRestartPending = false;
    if (Bluefruit.Periph.connected() < MAX_CONNECTIONS &&
        !Bluefruit.Advertising.isRunning()) {
      Bluefruit.Advertising.start(0);
    }
  }

  if (infoDueAt && millis() > infoDueAt) {
    infoDueAt = 0;
    sendInfo();
    sendStatus();
  }

  pollBleRx();

  // commands over USB serial too, so bring-up works without BLE
  while (Serial.available()) {
    static String serLine;
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') { handleCommand(serLine); serLine = ""; }
    else if (serLine.length() < 64) serLine += c;
  }

  // unsolicited status every 30 s keeps the app's battery pill fresh
  // (must run even when the NAU7802 is missing)
  if (Bluefruit.connected() && millis() - lastStatusMs > 30000) {
    lastStatusMs = millis();
    sendStatus();
  }

  // sensor missing at boot (or unplugged): rescan every 3 s
  if (!nauReady) {
    if (millis() - lastNauRetry > 3000) {
      lastNauRetry = millis();
      nauReady = nauInit();
      if (!nauReady) bleSend("NAU7802 not found at 0x2A (SCAN to list bus)");
    }
    return;
  }

  // sensor stall watchdog: a power/bus glitch can silently reset the
  // NAU7802 mid-run (conversions stop, battery keeps reporting). If no
  // sample arrives for 3 s, drop to the auto-reinit path above.
  if (millis() - lastSampleMs > 3000) {
    nauReady = false;
    bleSend("NAU7802 stalled — reinitializing");
    return;
  }

  if (nau.available()) {
    lastSampleMs = millis();
    int32_t raw = nau.getReading();

    // 24-bit ADC clips at ±8388607: weight freezes even as load grows.
    // Report it so an over-range cell/gain mismatch is visible.
    static uint32_t lastOvlMs = 0;
    if ((raw > 8300000 || raw < -8300000) && millis() - lastOvlMs > 2000) {
      lastOvlMs = millis();
      bleSend("WARN: ADC saturated — load beyond range for current gain");
    }

    // light IIR smoothing on raw counts
    if (!haveReading) { rawFiltered = raw; haveReading = true; }
    else rawFiltered += (raw - rawFiltered) / 4;

    float gross = rawFiltered            / countsPerKg * cal.calFactor;
    float net   = (rawFiltered - cal.tareOffset) / countsPerKg * cal.calFactor;

    // report at the configured resolution (default 10 kg, RES:<kg> to change)
    float q = cal.resolution;
    float netR   = roundf(net   / q) * q;
    float grossR = roundf(gross / q) * q;

    // stability: spread of recent net readings inside the band
    recentNet[recentIdx] = net;
    recentIdx = (recentIdx + 1) % STABLE_WINDOW;
    if (recentCount < STABLE_WINDOW) recentCount++;
    bool stable = false;
    if (recentCount == STABLE_WINDOW) {
      float mn = recentNet[0], mx = recentNet[0];
      for (uint8_t i = 1; i < STABLE_WINDOW; i++) {
        if (recentNet[i] < mn) mn = recentNet[i];
        if (recentNet[i] > mx) mx = recentNet[i];
      }
      stable = (mx - mn) < STABLE_BAND;
    }

    bleSend("P:" + String(netR, 1) + ",L:" + String(grossR, 1) +
            ",S:" + (stable ? "1" : "0") + ",U:0");
  }
}
