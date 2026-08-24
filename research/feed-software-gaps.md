# Feed Management Software — Producer Complaints and Unmet Needs

Research date: 2026-08-24
Purpose: competitive gap analysis for a feed management product competing with
Libra Feed (Bitstrata/Agrimatics), TAP FEED (Topcon/Digi-Star), FeedComp and
FeedWatch (VAS), Feed Supervisor (Supervisor Systems), and EZfeed (Amelicor),
with an explicit fit assessment for Brazil and Paraguay.

---

## 0. Sourcing integrity — read this first

The research plan asked for Reddit threads, farm forums, app-store reviews and
YouTube comments, fetched directly. **Most of that was not reachable from this
environment.** What follows is an exact account, because the difference between
sourced and inferred material changes how much weight each finding can carry.

### What was blocked

`WebFetch` returned `EGRESS_BLOCKED` for **every domain attempted**, including
control tests. Direct page fetches were impossible for the entire session.

| Target | Method | Result |
|---|---|---|
| `old.reddit.com` (all 5 subreddit searches) | WebFetch | "unable to fetch from old.reddit.com" |
| `old.reddit.com` (all 5 subreddit searches) | `curl` via egress proxy | `CONNECT tunnel failed, 403` — policy denial logged proxy-side |
| `www.reddit.com` | WebFetch | "unable to fetch from www.reddit.com" |
| `reddit.com` | WebSearch `allowed_domains` | API error: domain not accessible to the search user agent |
| `thecombineforum.com` | WebFetch | `EGRESS_BLOCKED` |
| `talk.newagtalk.com` / `newagtalk.com` | WebFetch | `EGRESS_BLOCKED` |
| `thefarmingforum.co.uk` | WebFetch | `EGRESS_BLOCKED` |
| `play.google.com` (all competitor apps) | WebFetch | `EGRESS_BLOCKED` |
| `apps.apple.com` (all competitor apps) | WebFetch | `EGRESS_BLOCKED` |
| `youtube.com` (comment sections) | WebFetch | `EGRESS_BLOCKED` |
| `bitstrata.com`, `businesswire.com`, `en.wikipedia.org` (control tests) | WebFetch | `EGRESS_BLOCKED` |

**Zero Reddit content was obtained.** Not "the searches returned nothing" —
the platform was unreachable by every available route. Every one of the eleven
requested search terms is therefore unrun against r/dairyfarming, r/cattle,
r/farming, r/Agriculture and r/Feedlot. **No claim in this document is
supported by Reddit.**

**Zero YouTube comments were obtained.** Relevant demo videos were identified
by URL (Libra TMR "Weighback (Feed Refusal)", "Loading and Feeding"; Digi-Star
TMR Tracker) but their comment sections could not be read.

**Zero app-store review pages were read directly.**

### What did work

`WebSearch` remained available, and its result summariser can reach into pages
that `WebFetch` cannot — including AgTalk/NewAgTalk thread bodies and Apple App
Store review text. That is the source of essentially all primary producer voice
below. It is a weaker instrument than reading the thread: it returns one or two
extracted passages per thread, usually without a full date, poster identity,
operation size, or the surrounding replies. **Operation type and head count —
requested capture field #4 — are absent from nearly every primary item**,
because the summariser did not surface them and the threads could not be opened
to check.

### Evidence labels used throughout

- **[PRODUCER]** — a farmer/operator speaking, retrieved via search summariser
  from a forum thread or app-store review. Strongest available evidence.
- **[SUPPORT]** — existence and title of a vendor support/KB article. Weak
  individually; a vendor writes a troubleshooting article because the issue
  recurs, so titles are a usable proxy for common failure modes.
- **[INDUSTRY]** — extension service, peer-reviewed/trade research, or trade
  press. Reliable on practice and magnitude, but not a complaint.
- **[VENDOR]** — vendor marketing. Useful only as evidence of what vendors
  believe buyers care about, and of feature parity.
- **[INFERRED]** — my reasoning. Carries no source. Flagged every time.

### Honest assessment of ranking validity

The brief asked to rank themes "by how often it came up and how loudly."
**A frequency count is not possible from this evidence base.** With Reddit,
four forums, both app stores and YouTube all unreadable, I have on the order of
eight distinct primary producer utterances, not the hundreds a frequency
ranking needs. The ranking below is therefore **evidence strength × strategic
weight**, and is labelled as such. Treat it as a prioritised hypothesis list,
not a measured demand signal. Section 4 lists exactly what to go re-verify.

### A finding that emerged from the failure itself

Searching the review-aggregator layer (SoftwareWorld, Solevant, SourceForge,
SoftwareSuggest, G2, Capterra) for these six products returned **no genuine
user reviews for any of them** — only vendor-derived feature copy rewritten as
"pros and cons." Agriculture-Xprt explicitly showed zero reviews for FeedComp.
This category has no public review surface. [INDUSTRY/observed]

Two consequences. First, it confirms the brief's instinct that forums were the
right place to look. Second — and more useful — **a competitor cannot be
out-reviewed here, because no one is reviewing.** Word of mouth through
nutritionists and scale dealers is the actual distribution channel, which is a
strategic conclusion, not a research inconvenience. See §3.6 and §5.

---

## 1. Themes, ranked

Ranking basis: evidence strength × strategic weight. **⚙️ = a manual workaround
is documented** — the brief's highest-value marker.

| # | Theme | Primary evidence | Workaround? |
|---|---|---|---|
| 1 | App reliability and crash-loops | [PRODUCER] ×2 + [SUPPORT] | ⚙️ |
| 2 | Bluetooth pairing and reconnect | [PRODUCER] ×1 + [SUPPORT] ×3 | ⚙️ |
| 3 | Offline / connectivity behaviour | [PRODUCER] ×1, [VENDOR] ×5, [INDUSTRY] ×1 | — |
| 4 | Loading accuracy and operator behaviour | [INDUSTRY] ×3 | ⚙️ |
| 5 | Nutritionist / advisor collaboration | [PRODUCER] ×1, [VENDOR] ×3 | — |
| 6 | Platform lock: iOS-only, Android-excluded | [PRODUCER-adjacent] + [VENDOR] | ⚙️ |
| 7 | Pricing model | [PRODUCER] ×1 (a number), [VENDOR] ×2 | — |
| 8 | Inventory, shrink, run-out forecasting | [INDUSTRY] ×3, [VENDOR] ×3 | ⚙️ |
| 9 | Glove / cold / dust / legibility | [PRODUCER] ×1, [VENDOR] ×3 | ⚙️ |
| 10 | Multi-operator, multi-mixer workflows | [VENDOR] only | — |
| 11 | Reporting: IOFC, conversion, cost/pen | [INDUSTRY] ×3, [VENDOR] ×3 | — |
| 12 | Data export, integration, lock-in | [INDUSTRY] adjacent-domain only | — |

Themes 10, 11 and 12 are **not evidenced as producer complaints** in anything I
could reach. They are on the list because the brief named them and because
vendors compete on them — not because a producer was found asking for them.
Do not treat their position as a demand measurement.

---

## 2. Theme detail

### 1. App reliability and crash-loops — **strongest direct evidence**

**Signal: loudest single producer voice found. ⚙️ Workaround documented.**

The one unambiguous, angry, first-person complaint in the entire corpus is an
Apple App Store review of **TAP Feed**: the user says they love it when it
works, which isn't often, that it crashes frequently, and that they have had to
delete and reinstall the app **at least fifteen times in two months**.
[PRODUCER] ([TAP Feed, App Store](https://apps.apple.com/us/app/tap-feed/id1505326585);
retrieved via search summariser — individual review date not surfaced)

Delete-and-reinstall fifteen times in eight weeks *is* the manual workaround,
and it is a brutal one: it means a feed crew standing at a mixer, twice a day,
with a dead app and cattle waiting.

Corroborating, weaker: Agrimatics maintains a dedicated support article titled
**"Feed – App Crashing"** for Libra Feed, whose advice is to ensure the latest
version is installed. [SUPPORT]
(https://support.agrimatics.com/article/191-app-crashing)

**Workflow this breaks.** Feeding is a fixed-clock, twice-daily, non-deferrable
task. Unlike planting software, there is no "try again tomorrow." An app that
fails 1% of sessions fails roughly five times a year per mixer per shift — and
each failure lands with a loaded mixer and a crew idle.

**Product implication.** Crash-free session rate is the primary product metric,
above every feature. Two concrete asks fall out: (a) the app must be able to
resume a **partially loaded batch** after a crash or force-quit, reading current
weight back from the indicator rather than restarting the load; (b) crash
telemetry must reach you without the farm having connectivity at crash time.

---

### 2. Bluetooth pairing and reconnect reliability

**Signal: strong. ⚙️ Workaround documented.**

Users of **Libra Cart** — Bitstrata/Agrimatics' sibling product on the same
Bluetooth stack — report **intermittent Bluetooth connectivity**, and separately
that the Android build lagged the Apple build and would not connect to their
equipment. [PRODUCER-adjacent — this is the grain-cart product, not Libra Feed;
the shared hardware/BLE lineage is why it is included, and it is *not* proof
against Libra Feed] ([Libra Cart, Google Play](https://play.google.com/store/apps/details?id=com.bitstrata.libra))

Agrimatics maintains **at least three separate Bluetooth pairing troubleshooting
articles** across its product line:
- [Cart – Bluetooth Pairing Issues](https://support.agrimatics.com/article/67-trouble-pairing)
- [Serial Link – Bluetooth Pairing Issues](https://support.agrimatics.com/article/568-serial-link-not-pairing)
- plus [Feed – Calibration](https://support.agrimatics.com/article/151-feed-calibration)
  and a "Phantom Loads" article on the Harvest product
  (https://support.agrimatics.com/article/423-phantom-loads) [SUPPORT]

**⚙️ The documented workaround is a ritual**: toggle Bluetooth off and on,
toggle airplane mode on and off, restart the phone. Also required: **Location
permission must be enabled** for the app to use BLE at all — an Android/iOS
platform requirement that reads as nonsense to an operator and generates
support calls on its own. [SUPPORT]

"Phantom loads" — spurious weight events recorded without a real load — is a
notable failure name to have needed a KB article for, and points at link-layer
instability producing *bad data* rather than merely *no data*. Bad data is worse:
no-connection is visible, a phantom load silently corrupts a pen's record.

**Product implication.** This is the single most defensible technical moat for a
team that already owns its scale firmware — which this repository is. Concretely:
persistent auto-reconnect with no user-visible pairing step after first setup;
the indicator buffers weights during a dropout and replays them on reconnect so
a link failure mid-load never loses the load; a permanent, glanceable link-state
indicator; and phantom-load rejection in firmware (plausibility gating on
weight deltas) rather than in the app.

---

### 3. Offline / connectivity behaviour

**Signal: high strategic weight, but this is table stakes, not a gap.**

This theme inverts the brief's assumption. Offline is not an unmet need —
**every serious competitor already claims it**, and in Brazil it is a headline
feature on every local product:

- Libra Feed: works entirely offline over Bluetooth; load and feed out without
  cellular or internet. [VENDOR] (https://agrimatics.com/libra-feed)
- iRancho (BR): collection is native and **100% offline**, with automatic sync
  on reconnect. [VENDOR]
- ArrobaPlus (BR): feed, bunk reading, movement and weighing entered offline,
  synced later; explicitly pitched at low-connectivity farms. [VENDOR]
- TGC / Ponta Agro (BR): offline with online sync. [VENDOR]
- iRancho "BOS": on-device NLP so operators can log by **voice** with no
  connection at all. [VENDOR]

The one primary datapoint runs the other way — toward *wanting* connectivity:
in a January 2024 NewAgTalk thread, a dairy explicitly looking to replace
Digi-Star/TMR Tracker was answered by a user running **MILC Feed for about a
year**, with **Android tablets in the loader and the feed truck on sub-$15/month
data plans**, valued for **remote monitoring**. [PRODUCER]
(https://talk.newagtalk.com/forums/thread-view.asp?tid=1146283&mid=10595267)

Note what that producer did: paid for two cellular data plans to escape offline
operation. Offline is the floor; **live visibility from the house is the thing
worth paying for.**

Underlying market fact for Brazil: **73% of rural producers lack connectivity**
and roughly **195 million hectares remain offline**. [INDUSTRY]
(https://campoenegocios.com/falta-de-conectividade-na-area-rural-atinge-73-dos-produtores/,
https://www.cocapec.com.br/noticias/apesar-de-expansao-mais-de-70-das-propriedades-rurais-no-brasil-nao-tem-acesso-a-internet)

**Product implication.** Shipping "works offline" wins nothing. The differentiator
is the **sync layer**: deterministic conflict resolution when two devices fed the
same pen while both were offline, a visible per-device sync queue, and no silent
data loss. Nobody found in this research markets against sync *correctness* —
they all market against sync *existence*. [INFERRED]

---

### 4. Loading accuracy and operator behaviour

**Signal: strong industry evidence, no direct producer voice. ⚙️ Workaround —
and it is a behavioural one, which is more interesting.**

A study of **26 California dairies using FeedWatch 7** found per-ingredient
deviation from target spanning a very wide band (reported as 78.7% to 21.9%;
the summariser did not surface the metric's definition, so **treat the exact
figures as unverified** — the directional finding is that accuracy varies
enormously by ingredient). **Alfalfa hay, corn silage and canola** were loaded
with the worst precision; **rolled corn and almond hulls** the best. [INDUSTRY]
(https://www.agproud.com/articles/31582-6-tips-to-improve-feeding-accuracy)

**⚙️ The behavioural workaround, and it is a genuine finding:** feeders who get
reprimanded for over-loading expensive ingredients conclude that on expensive
items they should **always err under target**. [INDUSTRY, same source] The
software's reporting layer, used as a disciplinary instrument, systematically
biases the ration — a management-visible metric producing a management-invisible
nutritional error.

Supporting: dosing accuracy is driven by loading technique, operator expertise,
and the physical properties of each ingredient (size, shape, density) — i.e.
**a single global tolerance band is wrong by construction.** [INDUSTRY]
(https://www.researchgate.net/publication/333718801_Deviations_of_feedstuffs_loading_in_TMR_preparation)

Vendors already do some of this: software can flag an ingredient loaded too
quickly after the previous one. [INDUSTRY/VENDOR]

**Product implication — probably the best pure-software differentiator found.**
(a) **Per-ingredient tolerance bands**, defaulted from ingredient class and
tightened for high-cost items, instead of one number; (b) report **signed bias**
per operator per ingredient, not absolute error, so chronic under-loading is as
visible as over-loading — directly countering the documented distortion;
(c) a **real-time target approach cue** on the loading screen (rate-aware, "ease
off now"), which is worth more than any after-the-fact report because it changes
the load while it is happening. [INFERRED, built on sourced findings]

---

### 5. Nutritionist and advisor collaboration

**Signal: moderate; one clear producer-stated value driver.**

In a March 2018 AgTalk thread on Performance Beef, the stated main advantage was
that **everything is stored in the cloud so records and inventories update
instantly and consultants can check records at any time.** [PRODUCER]
(https://talk.newagtalk.com/forums/thread-view.asp?tid=767237&mid=6616988)

That is the clearest articulation found of *why* a producer chose one of these
products — and it is not about the mixer. It is about the advisor.

Every vendor now claims this ground: Topcon ships **TAP FEED Advisor** as a
customer-management tool for feed advisors, consultants and nutritionists
[VENDOR]; FeedComp advertises **export files for consultants** [VENDOR]
(https://web.vas.com/feedcomp/); Zoetis Connect is positioned squarely as
shared producer/nutritionist ration decisions [VENDOR].

**Product implication.** The nutritionist is the **distribution channel**, not
just a user — in a category with no public review surface (§0), the consultant
is who producers actually ask. An advisor-side console that manages *many* client
operations, with ration push and closeout pull, is a growth mechanism rather
than a feature. [INFERRED]

---

### 6. Platform lock — iOS-only, and what it costs in Brazil

**Signal: verified competitive fact with a direct strategic consequence. ⚙️**

**Libra Feed is iOS-only.** Agrimatics' own compatibility article states iOS 10+
and **not available for Android**; there is no Google Play listing for Libra
Feed (there is for Libra Cart and Libra Harvest). [VENDOR/SUPPORT]
(https://support.agrimatics.com/article/146-compatible-mobile-devices)

Against that: **Android holds ~81.45% of the Brazilian smartphone market**,
driven by sub-$100 handsets versus iPhones starting near $799. [INDUSTRY]
(https://www.statista.com/statistics/262167/market-share-held-by-mobile-operating-systems-in-brazil)
Paraguay-specific split was **not found** — do not assume it, but the economic
drivers are the same or stronger.

**⚙️ The workaround this forces is a purchasing one:** to run Libra Feed a
Brazilian operation must buy iPads for the loader and the feed truck — the most
expensive, most theft-attractive, least rugged option — purely as a software
dependency. And the Libra Cart complaint above shows the *other* failure mode:
where Android does exist, it **lags the Apple build and stops connecting**.

**Product implication.** Android-first, with genuine build parity, is close to a
free win in this market. Target cheap, replaceable Android hardware explicitly:
assume a BRL 800 handset with a cracked screen and 2 GB of RAM is the reference
device, not the exception. [INFERRED]

---

### 7. Pricing model

**Signal: one hard producer-sourced number; otherwise thin.**

From AgTalk: **Performance Beef at $3,600 plus $300/year tech support.**
[PRODUCER] (https://talk.newagtalk.com/forums/thread-view.asp?tid=767237&mid=6616988)

Feed Supervisor and FeedComp **do not publish pricing**, and Feed Supervisor
additionally **requires custom hardware and installation**. [VENDOR/INDUSTRY]
(https://www.supervisorsystems.com/feed-supervisor/) Topcon runs a tiered ladder
— free TAP FEED App, paid TAP FEED Lite / Pro / Feedlot — where the free tier is
the Bluetooth indicator client and the paid tiers hold the management layer.
[VENDOR]

Adjacent-category pricing anchors, for reference only: AgriWebb from ~$34/month
with per-head scaling; Cattlytics from ~$6.79–7.99/month priced on active cattle
rather than users. [VENDOR]

**I found no producer complaining about feed-software pricing.** The brief listed
"pricing model gripes" as a theme of interest; on this evidence base it is
**unevidenced**. Quoted Brazilian pricing for TGC and iRancho could not be
found either — both are quote-only.

**⚠️ Structural warning for Brazil/Paraguay [INFERRED]:** per-head SaaS is a poor
fit for feedlot economics there. A *boitel* (custom-feeding yard) or a seasonal
confinement runs cattle in cycles; per-head-per-month billing punishes exactly
the high-throughput operator you most want. Per-head-per-*cycle*, or per-mixer,
tracks the value delivered far better. Also note FX: USD-denominated subscriptions
against BRL/PYG revenue are a live objection in both countries, and Paraguay is
the smaller market where a USD price list will bite hardest.

---

### 8. Inventory, shrink, and run-out forecasting

**Signal: large documented economic magnitude; no producer complaint found. ⚙️**

Typical shrink on **commodities in open bays runs 10–15%**. [INDUSTRY]
(https://standarddairyconsultants.com/dont-stop-the-count-inventory-tracking-and-management/,
https://www.supervisorsystems.com/managing-your-feed-shrink/)

Given feed is **50–60% of dairy production cost**, 10–15% shrink is roughly
5–9% of total cost of production leaking through an inventory gap. [INDUSTRY]

Forecasting exists but is described in weak terms: feed software "may be a
helpful tool" that "will project inventory usage based on current rations."
[INDUSTRY] BinMaster's FeedView pitches bin sensors plus weighing to forecast
consumption and prevent outages — notable because **it is sold as a separate
product**, implying the feed software's own forecasting is not trusted to prevent
run-outs. [VENDOR] (https://binmaster.com/feedview/)

**⚙️ Inferred workaround:** the persistence of physical bin-level sensors and
manual inventory counts alongside feed software is itself the workaround — but
**I did not find a producer describing it**, so this is reasoning, not a sourced
complaint.

**Product implication.** Forecasting must be a **dated, actionable alert** —
"corn silage runs out Thursday at current call, order by Tuesday" — not a report
someone has to open. Shrink should be surfaced continuously as
book-versus-actual per commodity, which is computable from data you already
capture at the mixer. [INFERRED]

---

### 9. Glove, cold, dust, and screen legibility

**Signal: one excellent old producer datapoint; the rest is display-vendor
marketing and must be discounted. ⚙️**

The genuine article, from March 2014 on AgTalk, is a thread titled
**"Helping a guy read his scale head on feed wagon from inside payloader?"** —
the operator cannot read the mixer's scale head from the loader cab. The
recommended fix was a Central City Scale wireless remote readout (Digi-Star Cab
Control 400) with **~1.5-inch digits**, which the respondent had used for years
and called well worth having. [PRODUCER]
(https://talk.newagtalk.com/forums/thread-view.asp?tid=461970&DisplayType=nested)

That is the workflow in one line: **the person loading is in the loader cab,
the scale is on the wagon, and the number has to be legible across that gap
through two windows.** It is a 2014 thread and the problem is structural, not
dated — it is precisely the gap a phone-based system claims to close, which
means **phone legibility at loader-cab distance is a hard requirement, not a
nice-to-have.**

The supporting material is display-industry marketing and should be weighted
accordingly: consumer tablets reportedly suffer screen-visibility failure within
30 days in dusty conditions, thermal shutdown in season, and moisture-related
connectivity drops; 500 cd/m² is described as near-invisible in direct sun with
1000+ nits needed; glove operation needs appropriate touch layers; IP65+ is the
stated durability bar. [VENDOR — all of it is sold by people selling rugged
tablets] (https://farmonaut.com/precision-farming/agricultural-touchscreen-revolution-7-innovations-for-2026,
https://www.waysion.com/blog/best-rugged-tablet-precision-agriculture-2026/)

One more [VENDOR] item worth keeping because it names the right failure:
farmers stop using agritech apps when the interface fails under real field
conditions, and the listed must-haves are offline function, sunlight-readable
high contrast, **large touch targets for gloved hands**, and voice input.

**Product implication.** A "loading mode" that renders the current ingredient
target and live weight as a **full-screen, very-high-contrast, few-elements
display** readable at cab distance, driven by rate not by pixels. Every action
required during loading must be reachable with a gloved thumb. Voice or
hardware-button confirmation removes the glove problem entirely for the
highest-frequency action. [INFERRED, built on the 2014 thread]

Note for Brazil/Paraguay specifically: cold is largely the wrong variable.
**Heat, dust, sun glare and humidity** are the field conditions in Mato Grosso
and the Chaco. Thermal throttling of a cheap Android handset in a loader cab at
40 °C is the realistic failure, not a frozen touchscreen. [INFERRED]

---

### 10. Multi-operator and multi-mixer workflows

**Signal: no producer evidence found. Vendor-claimed only.**

What exists is all vendor copy: TAP FEED Lite schedules deliveries to one or
multiple pens per load [VENDOR]; Cattlytics claims elimination of duplicate
entry across platforms and automatic sync [VENDOR]; generic feedlot-software
copy claims mobile/desktop parity and "multi-user conflict resolution" [VENDOR].

That last phrase is the tell. **Vendors are advertising conflict resolution,
which means conflicts happen.** But I could not source a producer describing a
double-fed pen, a lost shift handoff, or two operators colliding on one pen.

**Do not fund work here on the strength of this section.** It is the highest
priority item for re-verification (§4) — a large Brazilian feedlot runs multiple
mixers, multiple *tratoristas* and multiple shifts, so the theme is
*a priori* important for the target market and simply lacks evidence. [INFERRED]

---

### 11. Reporting: IOFC, feed conversion, cost per pen

**Signal: well-documented industry practice; zero producer complaint found.**

IOFC is a standard, well-defined metric: milk income remaining after purchased
and raised feed costs, computed from milk yield, milk price and feed cost per
cow per day, with feed at 30–70% of milk income. [INDUSTRY]
(https://www.pubs.ext.vt.edu/DASC/DASC-51/DASC-51.html,
https://extension.psu.edu/managing-income-over-feed-costs)
Standard companions: feed cost per cwt, feed cost per cow, IOFC. Dairy Margin
Tracker consumes **daily feed cost from on-farm feed software** to plot the IOFC
margin — i.e. the integration pattern already exists. [INDUSTRY]

Vendors claim the reports: TAP FEED exports DMI per head, operator accuracy and
ingredient usage; Feed Supervisor claims ECM/components analysis, bunk
management, weather impact; FeedComp claims consultant exports, graphing,
customisable reports and forecast inventories. [VENDOR]

**Searches for feedlot closeout and cost-per-pen producer discussion returned
nothing usable** — the results were dairy-IOFC extension material and vendor
pages. This theme is unevidenced as a complaint.

**Brazil note [INFERRED]:** the metric that matters there is not IOFC. It is
**custo da arroba produzida** (cost per finished arroba, 15 kg carcass) and
**margin per head per cycle**, benchmarked against the boi gordo price. A product
that ships IOFC as its flagship report is speaking the wrong language to a
Brazilian feedlot; for a *boitel* the flagship is per-client, per-lot billing
reconciliation.

---

### 12. Data export, integration, and lock-in

**Signal: weakest in the document. Adjacent-domain evidence only.**

Nothing found about lock-in **in feed software specifically**. The material is
general agricultural data governance and centres on John Deere Operations
Center: farmers cannot easily export yield or soil data into independent apps;
historical data is trapped in proprietary formats with switching costs described
as ruinous; ownership is signed away through unread EULAs. [INDUSTRY]
(https://www.vice.com/en/article/john-deere-tractor-hacking-big-data-surveillance/,
https://www.ifpri.org/blog/beyond-the-algorithm-the-need-for-farmer-participation-and-data-justice-in-digital-agricultural-technology/,
https://farmtario.com/machinery/the-legal-mess-of-farm-data-ownership/)

**Transferring machinery-data grievances onto feed software is an assumption.**
It is a plausible one — same structural setup, proprietary format, high switching
cost — but it is unsourced for this category and marked as such.

The single closest feed-specific item points the opposite way: FeedComp
advertises **export files for consultants** as a feature. [VENDOR] Export exists;
whether it is sufficient or resented, I cannot say from here.

**Product implication [INFERRED]:** a published, documented export (CSV plus a
stable API) is cheap to build and easy to market, and the John Deere backdrop
means the *language* of data ownership will land with producers even if the
specific grievance is unproven in this category. Low cost, plausible upside,
weak evidence — build it, don't lead with it.

---

## 3. Brazil and Paraguay market fit

The brief added this requirement last. It is treated as a first-class filter
here, because several of the US-derived conclusions above **change or invert**
in these markets.

### 3.1 Market size and structure — Brazil [INDUSTRY, well sourced]

- **9.25 million head** on feed in 2025, **+16% year over year**.
- Spread across **2,445 properties** in **1,095 municipalities**.
- **Mato Grosso leads with 2.2M head (+29.6%)**; São Paulo 1.4M (+7.7%);
  Goiás 1.4M (+13.6%).
- **The 100 largest properties hold 48% of all confined cattle** — extreme
  concentration.
- **Boitel (custom/third-party feeding) hit a record 1.76M head, +19%.**
- 2026 projected at **9.78M head (+5.7%)**.

Sources: https://girodoboi.canalrural.com.br/pecuaria/confinamento-cresce-16-e-supera-9-milhoes-de-cabecas-em-2025,
https://www.brasilagro.com.br/conteudo/confinamento-de-gado-cresceu-16-em-2025-no-brasil.html,
https://portaldbo.com.br/top-20-confinadores-2025/

**What this dictates.** 48% of the market sits in ~100 accounts. This is an
enterprise sales motion into a concentrated list, not self-serve app-store
distribution — the opposite of the go-to-market a Bluetooth scale app implies in
North America. And the **boitel segment is the sharpest wedge**: a custom yard
feeds cattle it does not own, so per-lot, per-owner cost attribution and billing
are not reporting niceties, they are the invoice. No competitor found in this
research is positioned on boitel billing.

### 3.2 Market size and structure — Paraguay [INDUSTRY, thinner]

- Roughly **5% of Paraguayan cattle production is intensive/feedlot**; feedlots
  are about **5.6% of establishments by type**.
- Dominant model: raise to **300–350 kg** on grass, then **~90 days** on feed to
  **480–500 kg**.
- Traditional pasture finishing still dominates; confinement is gaining, pushed
  by cropland competition.

Sources: https://www.valoragro.com.py/ganaderia/la-escala-define-el-negocio-del-feedlot/,
https://www.abc.com.py/negocios/abc-campo/2025/03/11/el-ganadero-debe-apostar-al-confinamiento/

**Establishment counts and head-on-feed totals for Paraguay were not found.**
ARP (Asociación Rural del Paraguay, https://www.arp.org.py/) is the right primary
source and was not reachable. **Do not size the Paraguayan opportunity from this
document.**

**What this dictates.** Paraguay is a secondary market — smaller, less
concentrated, ~90-day cycles. Treat it as a Spanish-language extension of the
Brazilian product with a *very* short feeding cycle, not a separate build. A
90-day cycle makes **fast onboarding** disproportionately important: a system
that takes three weeks to configure has burned a third of the cycle.

### 3.3 Connectivity — the assumption that must be re-examined

Two facts in tension:

1. **73% of Brazilian rural producers lack connectivity; ~195M ha offline.**
   [INDUSTRY]
2. **Starlink is live and changing this fast**, in both countries. In Paraguay,
   fibre in the Chaco is described as economically unviable due to distance and
   terrain, and Starlink is explicitly framed as breaking that constraint —
   installable in under 20 minutes, low power draw, already supporting cloud ERP
   and electronic invoicing from ranch offices, with government deployment of
   1,600 kits and 500 school/community sites. [INDUSTRY]
   (https://www.forbes.com.py/innovacion/starlink-desarrollada-spacex-lleva-internet-alta-velocidad-comunidades-aisladas-chaco-n92290,
   https://www.tecnologia.com.py/contectividad/por-que-starlink-esta-cambiando-la-conectividad-en-el-interior-de-paraguay,
   https://mitic.gov.py/paraguay-llevara-internet-de-alta-velocidad-y-fiabilidad-de-starlink-a-500-escuelas-y-comunidades-rurales/)

**The synthesis [INFERRED]:** the *farm office* is getting connected; the
*pen alley and the loader cab* are not. Starlink lands at the headquarters, not
at the bunk line 4 km away. This is the architecture the market actually needs
and it is the middle path between the two facts: **field devices assume no
connectivity and sync opportunistically to a hub at HQ; the hub is the thing that
talks to the cloud.** Building cloud-first because "Starlink solved it" is the
mistake this data warns against.

### 3.4 The real incumbent is not on the brief's list

**TGC (Tecnologia de Gestão em Confinamentos, Ponta Agro) is reported to be in
almost 70% of Brazilian feedlots.** [INDUSTRY/VENDOR — this figure comes from
industry/vendor-adjacent content, not an independent audit; verify before
relying on it] (https://pontaagro.com/software-para-pecuaria-e-gestao-de-corte/)

The competitive set named in the brief — Libra Feed, TAP FEED, FeedComp, Feed
Supervisor, EZfeed — is a **North American** set. In Brazil the field is:

| Product | Notes |
|---|---|
| **TGC / Ponta Agro** | Reported ~70% of BR feedlots. Manejo, feeding, per-lot performance, stock, contracts, individual financial closeout. Offline + sync. Ships a dedicated **leitura de cocho** app. |
| **iRancho** | Web + iOS/Android. **100% offline** native capture. Launched "BOS" with on-device NLP **voice logging with no connection**. |
| **ArrobaPlus** | Offline mobile for feeding, bunk reading, movement, weighing; explicitly for low-connectivity farms. |
| **FeedTratto** | Equipment-integrated: plans, manufactures and delivers to plan, reporting in real time, with corral scale integration. Closest to a hardware+software play. |
| **Bovitrato (SEYS)** | Web-based, local or internet access. |
| **Gestão Exacta** | Manejos, ingredients, nutrients, weights, health events, nutrition plan tied to the daily feeding schedule. |
| **Leigado** | **LG4040 panel — a TMR wagon scale head.** Direct hardware competitor. |
| **MultBovinos (Multsoft)**, **Farmin**, **Perfarm** | Broader herd/farm management with feedlot modules. |

Paraguay/Southern Cone: Control Ganadero, BovControl, VacApp are in use though
not Paraguayan; **Balanzas Vesta** manufactures mixer scales regionally; local
feedlot software is advertised on Clasipar. [VENDOR]

**Strategic consequence.** Against the US incumbents, "offline-capable Bluetooth
mixer app" is a differentiator. **Against TGC, iRancho and ArrobaPlus it is
parity** — they all shipped it, and iRancho has already moved past it to on-device
voice. Entering Brazil on an offline story means arriving late to a fight that is
over. §3.7 sets out where the actual opening is.

### 3.5 Leitura de cocho — the workflow the US products do not have

Brazilian and Paraguayan feeding is organised around **leitura de cocho** (bunk
reading): a scored assessment of bunk residue that drives the next *trato*.
Described as going beyond looking at yesterday's leftovers — reading herd
behaviour, the consumption curve and the physiological moment of the lot — to
forecast intake and therefore what to manufacture and deliver. [INDUSTRY]
(https://girodoboi.canalrural.com.br/pecuaria/leitura-de-cocho-confira-dicas-infaliveis-para-garantir-lucro-no-confinamento/,
https://pecuariadealtaperformance.com.br/confinamento/leitura-de-cocho/)

Every serious Brazilian product ships a leitura de cocho module — Ponta Agro
sells a **dedicated app** for it (https://pontaagro.com/leitura-de-cocho/); TGC
emphasises standardising the score parameters across readers so the analysis is
comparable and the adjustment can be made **at each feeding**, not the next day.

The US products handle the same physical reality as **weighback / refusals**:
weigh back what's left, subtract, adjust. That is a *weight-based* model.
Leitura de cocho is a *score-based* model — a trained reader assigns a score
(commonly a 0–4 style scale) without weighing anything.

**This is a genuine structural gap and the clearest localisation requirement in
this document.** A product built around weighback will feel wrong in Brazil, and
a product built only around cocho scores will feel wrong in the US. The right
build supports **both, on the same pen, converging**: score-driven daily
adjustment as the primary loop, with weighback used periodically to calibrate
each reader's scores against measured refusal weight. That last part —
**quantifying and correcting inter-reader bias, which TGC's "standardise the
parameters" framing identifies as the known weakness** — is a defensible feature
nobody was found shipping. [INFERRED, built on sourced findings]

### 3.6 Distribution

The review-aggregator layer is empty for this category (§0), so purchase
decisions run through people. In Brazil that means the **nutritional consultant**
and the **scale/mixer dealer**. Topcon's Brazilian channel is a data point in
your favour: its exclusive distributor is **Embratop**, a geo-technology
distributor (https://www.facebook.com/embratop.geo/videos/980237152538540/) —
a surveying-equipment channel selling into feedlots. Portuguese support portals
exist (https://topconagstore.com/portuguese/support/,
https://mytopcon-v1.topconpositioning.com/br/support), but the channel is not
livestock-native. [VENDOR/INFERRED]

### 3.7 ⚠️ Regulatory: legal metrology — the hardest gate, and it is on the hardware

This repository is scale firmware. That makes the following a **blocking
commercial issue in both target countries**, not a compliance footnote.

**Brazil — INMETRO.** Non-automatic weighing instruments are governed by
**Portaria INMETRO nº 157/2022**. A manufacturer intending to commercialise a
weighing instrument must submit it for testing; passing yields a **Portaria de
Aprovação de Modelo**, which is what permits sale nationally. Instruments used
in **commercial buy/sell transactions must be approved and verified**. ABRAPEM
specifically presses the case for buying only **cattle scales with INMETRO model
approval**. [INDUSTRY]
(https://www.toledobrasil.com/blog/aprovacoes-e-verificacoes-que-uma-balanca-deve-ser-submetida,
https://www.gov.br/inmetro/pt-br/, https://balmak.com.br/novo/wp-content/uploads/2024/02/Portaria-157-2022.pdf,
https://folhaagricola.com.br/2026/07/10/alerta-para-riscos-economicos-e-juridicos-no-uso-de-balancas-sem-homologacao-do-inmetro/)

**Paraguay — INTN.** The Organismo Nacional de Metrología runs a Department of
Technical Regulation and Model Approval (homologación) and a Department for
Verification of Regulated Instruments covering weighing instruments.
**Manufacturers, importers and representatives must submit regulated instruments
for model approval and initial verification**, and regulated instruments may not
be held or transferred without initial verification. [INDUSTRY]
(https://intn.gov.py/onm-departamentos/)

**Three consequences [INFERRED, from sourced regulation]:**

1. **A boitel is the worst case and your best segment.** Custom feeding bills a
   third party for delivered feed — that is a commercial transaction measured by
   your scale. INMETRO approval is likely mandatory precisely in the segment
   §3.1 identifies as the sharpest wedge. Get a legal opinion on this before
   committing; the two findings point at each other and neither was researched
   with the other in view.
2. **Model approval is long and expensive, and it gates hardware, not software.**
   It should be started in parallel with development, not after. It is also a
   moat once cleared — it is the same barrier that keeps competitors out.
3. **A software-only, bring-your-own-indicator path de-risks entry.** Supporting
   existing INMETRO-approved indicators (including Brazilian ones — Leigado's
   LG4040, and Balanzas Vesta mixer scales regionally) lets the software enter
   while the firmware clears approval. Given this repo is the firmware, that is a
   sequencing decision worth taking deliberately rather than by default.

### 3.8 Localisation checklist [INFERRED unless marked]

- **Portuguese (pt-BR) and Spanish (es-PY), not translated-from-English.** Domain
  vocabulary: *trato*, *leitura de cocho*, *lote*, *piquete/curral*, *arroba*,
  *boitel*, *tratorista*, *confinamento*, *ganho médio diário (GMD)*,
  *conversão alimentar*, *matéria seca*.
- **Metric throughout** — kg, tonnes, and **arroba (15 kg carcass)** for output.
- **Cost per arroba produced and margin per head per cycle** as headline metrics,
  not IOFC (§11).
- **Android-first**, cheap-handset reference device (§6) — ~81% Android in Brazil
  [INDUSTRY].
- **BRL/PYG pricing**, per-cycle or per-mixer rather than per-head-per-month (§7).
- **WhatsApp as an output channel** — the default business communication medium
  in both countries; daily closeout summaries and run-out alerts pushed there
  will be opened, an emailed PDF report will not. *Not sourced — I found no
  evidence on WhatsApp use in feed operations specifically; verify.*
- **Heat, dust, sun and humidity** as the environmental spec, not cold (§9).
- **LGPD** (Brazil, Lei 13.709) applies to personal data of employees and
  clients, including operator performance records. *Not researched; flagged for
  legal review.*

---

## 4. What to verify — ranked by how much rests on it

The blocked sources are not optional extras; several conclusions above are
resting on one or two utterances. In priority order:

1. **Reddit, entirely.** All five subreddits × all eleven search terms are
   unrun. This is the largest single hole. Run from an unrestricted network.
2. **Multi-operator/multi-mixer (§10).** Zero producer evidence, high a-priori
   importance for large Brazilian yards. The most likely place a real gap is
   hiding unmeasured.
3. **App-store reviews, both stores, all six competitors, full review lists.**
   The single TAP Feed crash review is doing more work in §1 than one review
   should. Verify whether it is representative or an outlier.
4. **INMETRO applicability to boitel billing (§3.7).** Legal opinion. This can
   invalidate a go-to-market sequence, and it is the intersection of two findings
   neither of which was researched with the other in mind.
5. **NewAgTalk/AgTalk thread bodies**, read in full — the summariser gave one
   passage per thread and dropped operation type and head count throughout,
   which is requested capture field #4 and is missing from nearly every item.
   Specific threads worth opening:
   - `tid=1146283` — replacing Digi-Star/TMR Tracker, Jan 2024 (§3)
   - `tid=767237` — Performance Beef, Mar 2018 (§5, §7)
   - `tid=461970` — scale head legibility from loader, Mar 2014 (§9)
   - `tid=531735` — "Who's keeping track of feed?", Jan 2015
   - `tid=645018` — "Scales on the TMR problem."
   - `tid=651508` — linking scale to EID, small feedlot
   - `tid=1024213`, `tid=1074154`, `tid=825294` — further Performance Beef threads
6. **The FeedWatch 26-dairy accuracy study.** Get the primary paper; the 78.7%/21.9%
   figures are unverified and §4's argument leans on the ingredient-variance shape.
7. **TGC's ~70% market share claim.** Vendor-adjacent; verify independently
   before building strategy on it.
8. **Paraguay: ARP** (https://www.arp.org.py/) for establishment counts and
   head-on-feed. Paraguay is currently sized on two sentences.
9. **Brazilian/Paraguayan producer voice.** Nothing in this document is a
   Brazilian or Paraguayan *producer complaining* — the BR/PY material is market
   structure, vendor claims and regulation. Reclame Aqui returned nothing for
   this category. Try: Engormix forums (https://www.engormix.com/), Facebook and
   WhatsApp confinamento groups, YouTube comments on Canal Rural / Giro do Boi
   feedlot content, and DBO's Top 20 Confinadores list as an interview frame.
10. **YouTube comments** on the identified demo videos: Libra TMR "Weighback
    (Feed Refusal)" (https://www.youtube.com/watch?v=XU8HCXJe5Us), Libra TMR
    "Loading and Feeding" (https://www.youtube.com/watch?v=YpCoaHk0OI8),
    Digi-Star TMR Tracker (https://www.youtube.com/watch?v=6QHpmMVywDw).

---

## 5. Bottom line

**Best-evidenced opportunities, in order of confidence:**

1. **Reliability as the product.** The loudest real complaint found is an app
   that crashes, plus Bluetooth that drops and occasionally invents weights.
   Crash-free rate, auto-reconnect with no pairing ritual, indicator-side
   buffering with replay, and crash-safe resume of a partial load. Owning the
   firmware makes this defensible in a way a pure app company cannot match. (§1, §2)
2. **Signed-bias loading feedback with per-ingredient tolerances.** The
   documented behavioural distortion — feeders systematically under-loading
   expensive ingredients because the report punishes overage — is a real,
   sourced, unaddressed failure of existing reporting design. (§4)
3. **Android-first.** Libra Feed is iOS-only against ~81% Android in Brazil.
   Verified fact, direct consequence. (§6)
4. **Leitura de cocho and weighback unified, with inter-reader bias
   calibration.** The structural workflow gap between the North American and
   Brazilian products, and the one place where "standardise the readers" is a
   known weakness nobody was found solving. (§3.5)
5. **Boitel per-lot cost attribution and billing.** Fastest-growing BR segment
   (+19%, 1.76M head), and billing is the customer's actual pain — subject to
   the INMETRO question in §3.7. (§3.1)

**Things the brief expected that this evidence does not support:**

- **Offline is not a gap** — it is parity in the US and table stakes in Brazil.
  The gap is sync *correctness* and HQ-hub visibility. (§3)
- **Pricing gripes are unevidenced.** Zero producers found complaining about
  feed-software pricing. The FX and per-head-vs-per-cycle concerns in §7 are my
  reasoning, not producer voice.
- **Lock-in is unevidenced for this category.** The John Deere data-ownership
  literature is adjacent-domain and may not transfer. (§12)
- **IOFC may be the wrong flagship metric for the stated target market.** (§11)

**And the correction to the competitive frame:** for Brazil, the named
competitor set is the wrong one. The incumbent to beat is **TGC**, alongside
iRancho, ArrobaPlus, FeedTratto and Leigado — none of which appeared in the
brief. (§3.4)
