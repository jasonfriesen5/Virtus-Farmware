# Feed Management Software — Producer Complaints and Unmet Needs

Research date: 2026-08-24 (round 1), 2026-08-26 (round 2, "go dig")
Purpose: competitive gap analysis for a feed management product competing with
Libra Feed (Bitstrata/Agrimatics), TAP FEED (Topcon/Digi-Star), FeedComp and
FeedWatch (VAS), Feed Supervisor (Supervisor Systems), and EZfeed (Amelicor),
with an explicit fit assessment for Brazil and Paraguay.

---

## 0. Sourcing integrity — read this first

The research plan asked for Reddit threads, farm forums, app-store reviews and
YouTube comments, fetched directly. **Most of that was not reachable.** What
follows is an exact account, because the difference between sourced and inferred
material changes how much weight each finding can carry.

### What was blocked

`WebFetch` returned `EGRESS_BLOCKED` for **every domain attempted**, including
control tests (Wikipedia, BusinessWire). Direct page fetches were impossible in
both rounds.

| Target | Method | Result |
|---|---|---|
| `old.reddit.com` (all 5 subreddit searches) | WebFetch | "unable to fetch from old.reddit.com" |
| `old.reddit.com` (all 5 subreddit searches) | `curl` via egress proxy | `CONNECT tunnel failed, 403` — policy denial logged proxy-side |
| `www.reddit.com` | WebFetch | "unable to fetch from www.reddit.com" |
| `reddit.com` | WebSearch `allowed_domains` | API error: domain not accessible to the search user agent |
| `site:reddit.com` and subreddit-targeted queries | WebSearch | Re-tested round 2. Zero Reddit results returned, both times |
| `thecombineforum.com`, `talk.newagtalk.com`, `thefarmingforum.co.uk` | WebFetch | `EGRESS_BLOCKED` |
| `play.google.com`, `apps.apple.com` (all competitor apps) | WebFetch | `EGRESS_BLOCKED` |
| `youtube.com` (comment sections) | WebFetch | `EGRESS_BLOCKED` |

**Zero Reddit content was obtained, confirmed twice.** Not "the searches
returned nothing" — the platform is unreachable by every available route. All
eleven requested search terms remain unrun against r/dairyfarming, r/cattle,
r/farming, r/Agriculture and r/Feedlot. **No claim in this document is supported
by Reddit.**

**Zero YouTube comments.** Relevant videos were identified by URL (Libra TMR
"Weighback (Feed Refusal)" and "Loading and Feeding"; Digi-Star TMR Tracker;
Prodap's bunk-score reader demo; Canal Rural's feedlot feed-control segment) but
no comment section could be read.

**Zero app-store pages read directly** — though see below.

### What did work

`WebSearch` remained available, and **its result summariser can read into pages
`WebFetch` cannot** — including AgTalk/NewAgTalk thread bodies and Apple App
Store review text. That is the source of essentially all primary producer voice
below, and round 2 exploited it much harder than round 1.

It is still a weaker instrument than reading the thread: it returns one or two
extracted passages, usually without a full date, poster identity or operation
size. **Operation type and head count — requested capture field #4 — are absent
from all but one primary item** (an AgTalk user on 900 head, §10).

### Evidence labels

- **[PRODUCER]** — a farmer/operator speaking, retrieved via search summariser
  from a forum thread or app-store review. Strongest available evidence.
- **[SUPPORT]** — existence and title of a vendor support/KB article. Weak
  individually; vendors write troubleshooting articles because issues recur.
- **[INDUSTRY]** — extension service, peer-reviewed/trade research, trade press,
  or a named expert quoted in trade press.
- **[VENDOR]** — vendor marketing. Evidence of what vendors think buyers want,
  and of feature parity. **Includes paid placements** — flagged where known.
- **[INFERRED]** — my reasoning. No source. Flagged every time.

### Honest assessment of ranking validity

**A frequency count is still not possible.** Round 2 roughly doubled the primary
producer evidence — from ~8 utterances to ~14 — but with Reddit, four forums and
YouTube unreadable, that is nowhere near what a frequency ranking needs. The
ranking below is **evidence strength × strategic weight**, and is labelled as
such. Treat it as a prioritised hypothesis list, not a measured demand signal.

### A finding that emerged from the failure itself

Searching the review-aggregator layer (SoftwareWorld, Solevant, SourceForge,
SoftwareSuggest, G2, Capterra) for these six products returned **no genuine user
reviews for any of them** — only vendor feature copy rewritten as "pros and
cons." Agriculture-Xprt showed zero reviews for FeedComp. This category has no
public review surface. [INDUSTRY/observed]

**A competitor cannot be out-reviewed here, because nobody is reviewing.** Word
of mouth through nutritionists and scale dealers is the actual channel. See §6
and §14.

---

## 1. Themes, ranked

Ranking basis: evidence strength × strategic weight. **⚙️ = a manual workaround
is documented** — the brief's highest-value marker.

| # | Theme | Primary evidence | Workaround? |
|---|---|---|---|
| 1 | Scale-link reliability: BLE drops, bad weights, crashes | [PRODUCER] ×4 + [SUPPORT] ×4 | ⚙️ |
| 2 | Bunk reading — score capture, reader bias, night work | [INDUSTRY] ×6, [VENDOR] ×5 | ⚙️ |
| 3 | Loading accuracy and operator behaviour | [INDUSTRY] ×4 | ⚙️ |
| 4 | Delivery route and drop ordering | [PRODUCER] ×1, [VENDOR] ×2 | ⚙️ |
| 5 | Offline / connectivity behaviour | [PRODUCER] ×1, [VENDOR] ×6, [INDUSTRY] ×2 | — |
| 6 | Nutritionist and advisor collaboration | [PRODUCER] ×1, [VENDOR] ×4 | — |
| 7 | Hardware and platform lock-in | [PRODUCER-adj] + [VENDOR] ×3 | ⚙️ |
| 8 | Paper and spreadsheet displacement | [VENDOR] ×3, [INDUSTRY] ×1 | ⚙️ |
| 9 | Inventory, shrink, run-out forecasting | [INDUSTRY] ×3, [VENDOR] ×3 | ⚙️ |
| 10 | Glove / heat / dust / darkness / legibility | [PRODUCER] ×1, [INDUSTRY] ×2, [VENDOR] ×3 | ⚙️ |
| 11 | Pricing model | [PRODUCER] ×1 (a number), [VENDOR] ×3 | — |
| 12 | Multi-operator and multi-mixer workflows | [VENDOR] ×4 only | — |
| 13 | Reporting: IOFC, conversion, cost per pen/arroba | [INDUSTRY] ×4, [VENDOR] ×4 | — |
| 14 | Data export, integration, lock-in | [INDUSTRY] adjacent-domain only | — |

Themes 12, 13 and 14 are **not evidenced as producer complaints** in anything
reachable. They are listed because the brief named them and vendors compete on
them — not because a producer was found asking. Do not read their position as a
demand measurement.

---

## 2. Theme detail

### 1. Scale-link reliability — BLE drops, bad weights, crash loops

**Signal: strongest direct evidence in the corpus, and it got stronger in round
2. ⚙️ Workarounds documented.**

Four independent producer-voice items now converge on one failure surface: the
link between the app and the scale, and the app's stability on top of it.

**TAP Feed (Apple App Store).** The loudest single complaint found: the user
loves it when it works, which isn't often; it crashes frequently; they have
**deleted and reinstalled at least fifteen times in two months.** [PRODUCER]
(https://apps.apple.com/us/app/tap-feed/id1505326585)

**Performance Beef (Apple App Store), 4.32/5 from 63 ratings.** Positive overall
— users say it simplifies rations, loads, costs, cattle moves and billing — but
the named defects are all in the same place: **communication with scales being
interrupted**; **the scale not reading accurately from time to time**; and the
system **not reporting back to the computer**. [PRODUCER]
(https://apps.apple.com/us/app/performance-beef/id1199645104?see-all=reviews)

That is three distinct failure modes on one product: link drop, **bad weight
accepted as good**, and sync failure to the back end.

**Libra Cart (Google Play)** — Bitstrata/Agrimatics' sibling on the same BLE
stack: **intermittent Bluetooth connectivity**, and an Android build that lagged
the Apple build and **would not connect to equipment**. [PRODUCER-adjacent —
grain-cart product, not Libra Feed; included for shared hardware/BLE lineage,
and *not* proof against Libra Feed]

**Libra Feed itself has too few App Store ratings to display an overview.**
[PRODUCER/observed] — a fact about install base, not quality.

**Vendor support articles corroborate.** Agrimatics maintains dedicated articles
for **app crashing**, **calibration**, **Cart Bluetooth pairing**, **Serial Link
pairing**, and — most tellingly — **"Phantom Loads"** on the Harvest product.
[SUPPORT]
(https://support.agrimatics.com/article/191-app-crashing,
https://support.agrimatics.com/article/67-trouble-pairing,
https://support.agrimatics.com/article/568-serial-link-not-pairing,
https://support.agrimatics.com/article/423-phantom-loads)

**⚙️ Two documented workarounds.** (a) Delete and reinstall the app — fifteen
times in eight weeks. (b) The pairing ritual: Bluetooth off/on, airplane mode
on/off, restart the phone. Plus a permanent trap: **Location permission must be
enabled** for BLE to work at all, a platform requirement that reads as nonsense
to an operator and generates support calls on its own. [SUPPORT]

**Why this matters more than it looks.** "Phantom loads" and "the scale not
reading accurately from time to time" are the same class of defect and it is the
dangerous one: **link instability that produces bad data rather than no data.**
No-connection is visible and the operator reacts. A phantom load silently
corrupts a pen's record, the inventory, and the closeout — and nobody finds out.

**Workflow this breaks.** Feeding is a fixed-clock, twice-or-thrice-daily,
non-deferrable task. There is no "try again tomorrow." An app that fails 1% of
sessions fails ~5 times a year per mixer per shift, each time with a loaded
mixer and an idle crew.

**Product implication — the core of the product.** Crash-free session rate above
every feature. Concretely: (a) resume a **partially loaded batch** after a crash
or force-quit by reading current weight back from the indicator, never restart
the load; (b) the indicator **buffers weights during a dropout and replays on
reconnect**, so a link failure mid-load never loses the load; (c) persistent
auto-reconnect with no user-visible pairing step after first setup; (d) a
permanent, glanceable link-state indicator; (e) **phantom-load rejection in
firmware** — plausibility gating on weight deltas — not in the app; (f) crash
telemetry that survives having no connectivity at crash time.

This repository is the scale firmware. Items (b) and (e) are only available to a
team that owns both sides of the link. **That is the moat.**

---

### 2. Bunk reading — score capture, reader bias, and night work

**Signal: the richest seam found in round 2, and the one the North American
products structurally do not serve. ⚙️ Paper is the workaround.**

This theme did not exist in round 1. It is now arguably the most important
section in the document for the stated target market.

**The practice.** Brazilian and Paraguayan feeding is organised around **leitura
de cocho / escore de cocho** — a trained reader scores bunk residue and the score
sets the next delivery. It is described as reading herd behaviour, the
consumption curve and the physiological moment of the lot, not just looking at
leftovers. [INDUSTRY]
(https://girodoboi.canalrural.com.br/pecuaria/leitura-de-cocho-confira-dicas-infaliveis-para-garantir-lucro-no-confinamento/,
https://pecuariadealtaperformance.com.br/confinamento/leitura-de-cocho/)

**The schedule — and this is the finding that changes the hardware spec.**
Recommended practice is **three readings per day**: [INDUSTRY]
(https://agrobatto.com.br/leitura-de-cocho/,
https://www.agroceresmultimix.com.br/blog/wp-content/uploads/2018/08/Manual-de-leitura-de-cocho-_-Matheus.pdf)

| Reading | Timing | Purpose |
|---|---|---|
| Matinal | Before the 1st trato — one source says **one hour before first feeding** | Sets the day's quantity |
| Vespertina | Before the last trato | Catch and correct problems |
| **Noturna** | **Typically 21:00–22:00** | Informs the next morning's interpretation |

Two of three readings happen **in the dark or near-dark.** The Giro do Boi piece
on execution failures specifically blames **"avaliações erradas ou negligenciadas
na madrugada"** — wrong or neglected pre-dawn assessments — for producing either
underfeeding or excess residue that sours fast in sun and rain. [INDUSTRY]

**The scoring scale is not standard, and that is a hard product requirement.**
Scores commonly run **-2 to +3**, but the traditional scale is **0 to 5**, and
sources state plainly that **each property can establish its own scale** as long
as the team understands it and applies it consistently. [INDUSTRY]
(https://www.educapoint.com.br/v2/blog/pecuaria-corte/leitura-escore-cocho-confinamentos-bovinos/,
https://zootecniabrasil.com/2021/02/13/leitura-de-cocho-para-bovinos-em-confinamento/)

**The adjustment rules are not standard either.** Documented actions span a wide
range: increase ~0.5–1% of total offered for a mild consistent reading; 5% or
1 kg DM in the traditional 0–5 concept when feed ran short; **15% at a -2.0
score**, treated as an emergency; general guidance of 1–2 kg DM/head/day.
[INDUSTRY] (https://www.milkpoint.com.br/colunas/cowtech/novos-conceitos-abordando-o-monitoramento-da-sobra-de-dietas-escore-de-cocho-parte-2-18602/,
https://rehagro.com.br/blog/leitura-de-cocho-como-avaliar-e-ajustar-a-sobra-de-trato-em-vacas-em-lactacao/)

**⚙️ The workaround is paper**, and vendors say so directly: Prodap sells its
bunk-score app on **"eliminating paper notation."** [VENDOR] In the US the
equivalent is the **bunk sheet** — date, bunk call, feed call, total feed, and
**the feeder's initials**, per pen, on paper. [INDUSTRY]
(https://sweetbran.com/storage/AncT5fwhzwwBXavDk0bCUXh3qIhdlTbgS7bb7qhh.pdf)

**Reader bias is the acknowledged weak point.** Guidance is that the reading be
done **at the same time and preferably by the same person**, with standardisation
requiring "rotina diária, critérios rígidos e treinamento contínuo." [INDUSTRY]
Which is to say: the method's accuracy depends on a human being consistent, and
everyone knows it.

**⚠️ CORRECTION TO ROUND 1.** The first draft concluded that quantifying and
correcting inter-reader bias was "a defensible feature nobody was found
shipping." **That is wrong, and round 2 found the counter-evidence.**

**Prodap ships a camera-based automatic bunk-score reader.** It processes **how
many kilograms of the total diet were left, per line, per pen, per feeding**,
automatically. The camera mounts on a **bicycle, motorcycle or car**, and as it
reads the bunk **the software already proposes the feed adjustment**. Their app
"Prodap Views Prime" also allows **multiple employees to record readings in loco
simultaneously**. [VENDOR]
(https://blog.prodap.com.br/leitura-status-de-escore-de-cocho-com-software-de-gestao/,
https://apecuariadeprecisao.com.br/blog/leitor-digital-escore-de-cocho/)

**SmartBov** likewise advertises "leitura inteligente de cocho" plus camera-based
animal weighing (SmartBov Vision, AI trained on Brazilian data). [VENDOR]
(https://smartbov.com/solucoes/feedlot/, https://smartbov.com/solucoes/vision/)

The subjective-score problem is **already being automated away in Brazil**. Do
not enter pitching "we'll standardise your readers" as a novel idea.

**Product implication, revised.** The remaining defensible position is **not**
inventing bunk-score digitisation — that ground is taken. It is:
1. **Configurable score scale and configurable score→adjustment mapping**, per
   farm. Every source says farms run their own scales and their own rules. A
   hardcoded 0–5 or -2..+3 is an immediate disqualification in Brazil.
2. **Closing the loop against the mixer.** Prodap's reader proposes an
   adjustment; the value is only realised if that adjustment lands in the next
   load automatically. Owning the scale link is what makes score→load→delivered
   a closed loop rather than a suggestion someone re-types.
3. **Night-usable capture** (see §10) — two of three readings are in the dark.
4. **Reader-vs-measurement calibration** as a *report*, not a claim of novelty:
   periodically weigh back a sample of pens and show each reader their drift.

---

### 3. Loading accuracy and operator behaviour

**Signal: strong industry evidence, no direct producer voice. ⚙️ The workaround
is behavioural, which makes it more interesting, not less.**

A study of **26 California dairies using FeedWatch 7** found per-ingredient
deviation from target spanning a very wide band (reported as 78.7% to 21.9%; the
summariser never surfaced the metric's definition, so **treat the exact figures
as unverified** — the directional finding is that accuracy varies enormously by
ingredient). **Alfalfa hay, corn silage and canola** loaded worst; **rolled corn
and almond hulls** best. [INDUSTRY]
(https://www.agproud.com/articles/31582-6-tips-to-improve-feeding-accuracy)

**⚙️ The behavioural workaround, and it is a real finding:** feeders reprimanded
for over-loading expensive ingredients conclude they should **always err under
target** on expensive items. [INDUSTRY, same source] The reporting layer, used as
a disciplinary instrument, systematically biases the ration — a management-visible
metric producing a management-invisible nutritional error.

Dosing accuracy is driven by loading technique, operator expertise, and each
ingredient's physical properties — size, shape, density. **A single global
tolerance band is wrong by construction.** [INDUSTRY]
(https://www.researchgate.net/publication/333718801_Deviations_of_feedstuffs_loading_in_TMR_preparation)

**Round 2 adds the metric set the category already tracks.** Electronic feed
monitoring systems are described as monitoring feeder performance on three
figures: **dry matter intake by pen/group, pen feeding times, and load
accuracy** — with per-feeder evaluation used to recognise good feeders and
identify training needs. [INDUSTRY]
(https://www.agproud.com/articles/27467-electronic-feed-monitoring-systems-measure-and-monitor)
Vendors claim the same ground: FeedWatch monitors what feeders put in the boxes
with errors-and-exceptions reports; EZfeed "tracks who did what, and what time";
Feed Supervisor reports operator efficiency; systems track **drop times,
delivered amounts, load deviation, and what those deviations cost in money.**
[VENDOR]

The Brazilian framing is blunter and quantified. Zootecnista **Maurício Scoton**,
via Giro do Boi: **chronic management failures in the feed mill and bunk line
remove up to R$ 400 from final revenue per animal**, turning a perfect nutrition
spreadsheet into a loss masked by poor operational management. Many feedlots run
dangerously tight margins and lose money **not from formulation errors but from
being blind to daily execution failures in the trato.** [INDUSTRY]
(https://girodoboi.canalrural.com.br/pecuaria/falhas-de-manejo-podem-retirar-ate-r-400-do-faturamento-por-animal-aponta-especialista)

A second Brazilian source enumerates the deviation points: more or less of an
ingredient than the batch requires; scale problems; poor distribution in the
bunk; mixing problems; animal selection; feed overlap. It also names a failure
that is directly this repo's business: **the feed wagon scale not being
calibrated before the confinement operation starts.** [VENDOR/INDUSTRY]
(https://www.irancho.com.br/gestao-de-confinamento-como-aumentar-a-margem-e-eliminar-perdas-invisiveis/)

**Product implication — the best pure-software differentiator found.**
(a) **Per-ingredient tolerance bands**, defaulted by ingredient class and
tightened for high-cost items, instead of one number.
(b) Report **signed bias** per operator per ingredient, not absolute error, so
chronic under-loading is as visible as over-loading — directly countering the
documented distortion.
(c) A **real-time target-approach cue** on the loading screen, rate-aware ("ease
off now"), which changes the load while it is happening and is worth more than
any after-the-fact report.
(d) **Calibration as a tracked, enforced event** — last-calibrated date per
mixer, a pre-season prompt, and a refusal to certify loads from an uncalibrated
scale. Sourced as a real Brazilian failure mode, and it is firmware-side.
[INFERRED, built on sourced findings]

---

### 4. Delivery route and drop ordering

**Signal: new in round 2. One sharp producer complaint. ⚙️**

From Performance Beef App Store reviews: users report **difficulty changing the
order of drops, which "seemingly go to random places."** [PRODUCER]
(https://apps.apple.com/us/app/performance-beef/id1199645104?see-all=reviews)

This is small in wording and large in workflow. A feed truck delivers one mixed
load across several pens in a physical sequence determined by yard geometry,
gate positions, mud, and which pens are being handled that morning. If the
software's drop order does not match the truck's actual route, the operator is
either driving extra passes or reordering in the app while wearing gloves in a
moving truck — **and the workaround is to fight the UI mid-route.**

Vendors know the shape of it. Performance Beef markets auto-adjusting targets
"based on previous drops" [VENDOR]; TAP FEED Lite markets scheduling deliveries
"to one or multiple pens per load" [VENDOR]; ITS Livestock's **DeliverIT** is
pitched as getting "the load right and the right cattle fed every time," with
in-truck display, real-time capture, feed-call adjustment by head or by pen, and
driver analysis for accountability. [VENDOR] (https://itslivestock.com/software/)

**Product implication.** Drop order must be **reorderable in one gesture at the
truck**, with the route persisted per mixer and per shift, and remaining-in-mixer
weight shown against remaining drops so an operator can see a shortfall coming
before the last pen. [INFERRED]

---

### 5. Offline / connectivity behaviour

**Signal: high strategic weight, but this is table stakes, not a gap.**

This theme inverts the brief's assumption. Offline is not an unmet need — **every
serious competitor already claims it**, and in Brazil it is a headline feature on
every local product:

- Libra Feed: works entirely offline over Bluetooth; load and feed out without
  cellular or internet. [VENDOR] (https://agrimatics.com/libra-feed)
- iRancho (BR): capture is native and **100% offline**, auto-sync on reconnect.
- ArrobaPlus (BR): feed, bunk reading, movement, weighing offline, synced later;
  explicitly pitched at low-connectivity farms.
- TGC / Ponta Agro (BR): offline with online sync.
- iRancho "BOS": on-device NLP so operators log by **voice** with no connection.
- Generic feedlot software: offline capture then sync, marketed as reducing
  duplicates versus human error. [all VENDOR]

The one primary datapoint runs the other way — toward *wanting* connectivity. In
a January 2024 NewAgTalk thread, a dairy explicitly seeking to replace
Digi-Star/TMR Tracker was answered by a user running **MILC Feed for about a
year**, with **Android tablets in the loader and the feed truck on sub-$15/month
data plans**, valued for **remote monitoring**. [PRODUCER]
(https://talk.newagtalk.com/forums/thread-view.asp?tid=1146283&mid=10595267)

That producer paid for two cellular plans to *escape* offline operation. Offline
is the floor; **live visibility from the house is what gets paid for.**

Market context for Brazil: **73% of rural producers lack connectivity**;
~**195 million hectares** remain offline. [INDUSTRY]
(https://campoenegocios.com/falta-de-conectividade-na-area-rural-atinge-73-dos-produtores/)

**Product implication.** Shipping "works offline" wins nothing. The differentiator
is the **sync layer**: deterministic conflict resolution when two devices fed the
same pen while both were offline, a visible per-device sync queue, and no silent
data loss. Nobody found in this research markets against sync *correctness* —
they all market against sync *existence*. [INFERRED]

---

### 6. Nutritionist and advisor collaboration

**Signal: moderate; one clear producer-stated purchase driver.**

In a March 2018 AgTalk thread on Performance Beef, the stated main advantage was
that **everything is stored in the cloud so records and inventories update
instantly and consultants can check records at any time.** [PRODUCER]
(https://talk.newagtalk.com/forums/thread-view.asp?tid=767237&mid=6616988)

That is the clearest articulation found of *why* a producer chose one of these
products — and it is not about the mixer. It is about the advisor.

Everyone competes here: Topcon ships **TAP FEED Advisor** for feed advisors and
nutritionists; FeedComp advertises **export files for consultants**; Zoetis
Connect is positioned on shared producer/nutritionist ration decisions; and
Dinamica Generale's **DTM ADV** — sold in Brazil through **Weightech**, in
Portuguese — is explicitly marketed on **nutritionists checking data and
providing remote consultation.** [VENDOR]
(https://www.weightech.com.br/dtm-adv, https://web.vas.com/feedcomp/)

**Product implication.** The nutritionist is the **distribution channel**, not
just a user — in a category with no public review surface (§0), the consultant is
who producers actually ask. An advisor-side console managing *many* client
operations, with ration push and closeout pull, is a growth mechanism rather than
a feature. In Brazil this is doubly true: Prodap and Ponta are consultancies that
sell software, so the incumbent relationship is already advisor-mediated.
[INFERRED]

---

### 7. Hardware and platform lock-in

**Signal: verified competitive facts with direct strategic consequences. ⚙️**

Three separate locks, all verified in round 2.

**(a) Libra Feed is iOS-only.** Agrimatics' own compatibility article states
iOS 10+ and **not available for Android**; there is no Google Play listing for
Libra Feed, though there is for Libra Cart and Libra Harvest. [VENDOR/SUPPORT]
(https://support.agrimatics.com/article/146-compatible-mobile-devices)

Against that: **Android holds ~81.45% of the Brazilian smartphone market**,
driven by sub-$100 handsets versus iPhones from ~$799. [INDUSTRY]
(https://www.statista.com/statistics/262167/market-share-held-by-mobile-operating-systems-in-brazil)
**Paraguay's split was not found** — do not assume it, though the economics are
the same or stronger.

**⚙️ The workaround this forces is a purchase**: to run Libra Feed a Brazilian
operation must buy iPads for the loader and the feed truck — the most expensive,
most theft-attractive, least rugged option — purely as a software dependency.
And where Android does exist in that family, the Libra Cart complaint shows the
other failure: the build **lags Apple and stops connecting.**

**(b) TAP Feed is locked to Digi-Star hardware.** The app "must be paired with a
Topcon Digi-Star line Bluetooth indicator like the **EZ 2810BT or EZ 3410BT**."
The free app is the indicator client; the management layer is a paid TAP FEED
Lite / Pro / Feedlot subscription. [VENDOR]
(https://www.topconpositioning.com/us/en/campaigns/tap-feed-app)

So the "free app" is a hardware funnel. A producer who buys Digi-Star indicators
has bought into Topcon's software ladder, and vice versa.

**(c) Feed Supervisor requires custom hardware and installation**, with no
published pricing. [VENDOR/INDUSTRY]
(https://www.supervisorsystems.com/feed-supervisor/)

**Product implication.** Two moves, and they compound.
- **Android-first with genuine build parity.** Reference device: a BRL ~800
  handset with a cracked screen and 2 GB of RAM, not the exception.
- **Be the un-locked option.** Support third-party indicators — including the
  Brazilian ones (Leigado LG4040, Weightech, Balanzas Vesta regionally) — so the
  software can be adopted without replacing the scale. This is also the
  regulatory de-risking path in §12.7. [INFERRED]

*Naming note:* "Libra" in Brazil is already **Libra Nutrição Animal**, a cattle
supplement manufacturer operating across PA, MT, MA, TO, GO, SP and PR
(https://libra.ind.br/). A brand collision in-market, and a small point in your
favour if Libra Feed ever tries to enter.

---

### 8. Paper and spreadsheet displacement

**Signal: consistent across many vendors and both hemispheres; ⚙️ the workaround
*is* the incumbent.**

What these products actually compete against, in most operations, is paper and
Excel — not each other.

- US: the **bunk sheet** — date, bunk call, feed call, total feed, feeder's
  initials, per pen, on paper. [INDUSTRY]
- Brazil: Prodap sells its score app on **"eliminating paper notation."**
  [VENDOR]
- Brazil: iRancho's positioning is spreadsheet-versus-app directly. Named
  spreadsheet failure modes: imprecise weighings; **ingredient substitutions
  without registration**; divergence between the calculated formulation and what
  was actually distributed to the bunk; **delayed bunk reading producing
  nutritional decisions on stale data**; late or incorrect recording preventing
  exact adjustment of the next feeding. [VENDOR]
  (https://www.irancho.com.br/planilha-no-confinamento-bovino-ou-aplicativo-offline/)

**Product implication.** The migration path from paper matters more than feature
parity with TGC. An operation on paper has a working system; the switch has to be
faster on day one, not better on day ninety. Import from spreadsheet, and a
first-week mode that mirrors the paper form the crew already knows, are worth
more than any report. [INFERRED]

---

### 9. Inventory, shrink, and run-out forecasting

**Signal: large documented economic magnitude; no producer complaint found. ⚙️**

Typical shrink on **commodities in open bays runs 10–15%.** [INDUSTRY]
(https://standarddairyconsultants.com/dont-stop-the-count-inventory-tracking-and-management/,
https://www.supervisorsystems.com/managing-your-feed-shrink/)

With feed at 50–60% of dairy production cost, that is roughly 5–9% of total cost
of production leaking through an inventory gap. In Brazilian feedlots the feed
share is higher still — see §13.

Forecasting exists but is described weakly: feed software "may be a helpful tool"
that "will project inventory usage based on current rations." [INDUSTRY]
BinMaster's FeedView sells bin sensors plus weighing to forecast consumption and
prevent outages — notable because **it is a separate product**, implying the feed
software's own forecasting is not trusted to prevent run-outs. [VENDOR]
(https://binmaster.com/feedview/)

Brazilian framing names the same gap as **"buracos no estoque"** — holes in
inventory that silently erode profit alongside wagon scale errors and bad bunk
readings. [VENDOR] SmartBov pitches full traceability **"do silo ao cocho"**,
integrating silos and truck scales. [VENDOR]

**⚙️ Inferred workaround:** the persistence of bin sensors and manual counts
alongside feed software is itself the workaround — but **no producer was found
describing it**, so this is reasoning, not a sourced complaint.

**Product implication.** Forecasting must be a **dated, actionable alert** —
"corn silage runs out Thursday at current call, order by Tuesday" — not a report
someone must open. Shrink should be continuous book-versus-actual per commodity,
computable from data already captured at the mixer. [INFERRED]

---

### 10. Glove, heat, dust, darkness, and legibility

**Signal: one excellent producer datapoint, plus a round-2 correction that
changes the spec. ⚙️**

The genuine article, from March 2014 on AgTalk: **"Helping a guy read his scale
head on feed wagon from inside payloader?"** — the operator cannot read the
mixer's scale head from the loader cab. Recommended fix: a Central City Scale
wireless remote readout (Digi-Star Cab Control 400) with **~1.5-inch digits**,
used for years and called well worth having. [PRODUCER]
(https://talk.newagtalk.com/forums/thread-view.asp?tid=461970&DisplayType=nested)

That is the workflow in one line: **the person loading is in the loader cab, the
scale is on the wagon, and the number must be legible across that gap through two
windows.** A 2014 thread describing a structural problem, not a dated one — it is
exactly the gap a phone-based system claims to close, so **phone legibility at
loader-cab distance is a hard requirement.** Topcon has since productised this
as a "Cab Control" remote-display mode in the free TAP Feed app [VENDOR] — so
this specific need is now *contested ground*, not open.

**⚠️ CORRECTION TO ROUND 1 — the environmental spec was wrong.** The first draft
said the Brazil/Paraguay condition set is "heat, dust, sun glare and humidity,"
and that cold is the wrong variable. Heat and dust stand. **But sun glare is at
most one third of the problem**, because §2 establishes that **two of the three
daily bunk readings happen in the dark**: a pre-dawn reading an hour before first
feeding, and a night reading at 21:00–22:00. The dominant legibility condition
for the highest-frequency data-entry task in a Brazilian feedlot is **darkness,
one-handed, probably on a motorcycle or from a vehicle, possibly in rain.**

Supporting material is display-industry marketing and should be discounted
accordingly: consumer tablets reportedly fail on screen visibility within 30 days
in dust, thermally shut down in season, and drop connectivity from moisture
ingress; 500 cd/m² is near-invisible in direct sun with 1000+ nits needed;
gloves need appropriate touch layers; IP65+ is the stated bar. [VENDOR — sold by
people selling rugged tablets]
(https://farmonaut.com/precision-farming/agricultural-touchscreen-revolution-7-innovations-for-2026)

One [VENDOR] item worth keeping because it names the right failure set: farmers
stop using agritech apps when the interface fails in real field conditions, and
the must-haves listed are offline function, sunlight-readable high contrast,
**large touch targets for gloved hands**, and **voice input**.

Voice is not hypothetical here: iRancho's BOS runs on-device NLP for voice
logging with no connection [VENDOR], and Drovers has covered voice-to-record
cattle apps as a category. [INDUSTRY]
(https://www.drovers.com/news/beef-production/voice-record-app-reinvents-cattle-management)

**Product implication.**
- A **"loading mode"**: full-screen, very-high-contrast, few elements, readable
  at cab distance.
- A **true night mode** for bunk reading — dark ground, red/amber accent,
  brightness that does not destroy the reader's dark adaptation, and controls
  usable one-handed with a headlamp on.
- Every loading action reachable with a gloved thumb; **voice or hardware-button
  confirmation** removes the glove problem entirely for the highest-frequency
  action.
- Thermal reality: a cheap Android handset in a loader cab at 40 °C throttles.
  Design for it. [INFERRED]

---

### 11. Pricing model

**Signal: one hard producer-sourced number; otherwise thin, and still no
complaint.**

From AgTalk: **Performance Beef at $3,600 plus $300/year tech support.**
[PRODUCER] (https://talk.newagtalk.com/forums/thread-view.asp?tid=767237)

Feed Supervisor and FeedComp **do not publish pricing**; Feed Supervisor requires
custom hardware and installation. Topcon runs a tiered ladder — free app, paid
Lite/Pro/Feedlot — with the free tier as hardware funnel (§7). [VENDOR]

Adjacent-category anchors, reference only: AgriWebb from ~$34/month with per-head
scaling, cited elsewhere at $2,000–$5,000+/year for 1,000+ head feedlots;
Cattlytics from ~$6.79–7.99/month priced on active cattle rather than users.
[VENDOR]

Brazilian pricing for **TGC, iRancho, Prodap and SmartBov could not be found —
all are quote-only.** Round 2 searched specifically for it and returned nothing.

**I still found no producer complaining about feed-software pricing.** The brief
listed "pricing model gripes" as a theme of interest; on this evidence base it is
**unevidenced.**

**⚠️ Structural warning [INFERRED]:** per-head SaaS fits feedlot economics badly
in Brazil and Paraguay. A *boitel* or a seasonal confinement runs cattle in
cycles; per-head-per-month punishes exactly the high-throughput operator you most
want. **Per-head-per-cycle, or per-mixer,** tracks delivered value. And FX:
USD-denominated subscriptions against BRL/PYG revenue are a live objection in
both countries — Paraguay, the smaller market, will feel a USD price list worst.

---

### 12. Multi-operator and multi-mixer workflows

**Signal: still no producer evidence after two rounds of targeted searching.
Vendor-claimed only. This remains the largest unverified gap.**

Round 2 searched this specifically — shift handoff, double-fed pens, missed pens,
two trucks on one pen — and produced **only vendor copy**:

- Prodap: multiple employees record bunk readings **in loco simultaneously**.
- ITS Livestock **DeliverIT**: "the right cattle fed every time," in-truck
  display, driver analysis for accountability.
- Cattlytics: eliminates duplicate entry across platforms, auto-sync.
- Generic feedlot copy: "mobile/desktop parity and multi-user conflict
  resolution." [all VENDOR]

That last phrase is the tell — **vendors advertise conflict resolution, which
means conflicts happen.** But no producer was found describing a double-fed pen,
a lost handoff, or two operators colliding.

**Do not fund work here on the strength of this section.** It is the top
re-verification priority (§15): a large Brazilian feedlot runs multiple mixers,
multiple *tratoristas* and multiple shifts, so the theme is *a priori* important
for the target market and simply lacks evidence. [INFERRED]

---

### 13. Reporting: IOFC, feed conversion, cost per pen — and cost per arroba

**Signal: well-documented practice; zero producer complaint. But round 2 found
the metric that actually matters in-market.**

**North America.** IOFC is standard and well-defined: milk income remaining after
purchased and raised feed, from milk yield, milk price and feed cost per cow per
day, with feed at 30–70% of milk income. Companions: feed cost per cwt, per cow,
IOFC. Dairy Margin Tracker consumes **daily feed cost from on-farm feed
software** — the integration pattern already exists. [INDUSTRY]
(https://www.pubs.ext.vt.edu/DASC/DASC-51/DASC-51.html,
https://extension.psu.edu/managing-income-over-feed-costs)

Vendors claim the reports: TAP FEED exports DMI/head, operator accuracy,
ingredient usage; Feed Supervisor claims ECM/components, bunk management, weather
impact; FeedComp claims consultant exports, graphing, custom reports, forecast
inventories. [VENDOR]

**Searches for feedlot closeout and cost-per-pen producer discussion returned
nothing usable** in either round.

**Brazil — the right metric set, now sourced.** The authoritative benchmark is
the **ICBC (Índice de Custos do Boi Confinado), USP/Esalq**, published monthly
and reported by Canal Rural / Giro do Boi. Its structure tells you what to build:

- Feed is **the dominant cost component**: in 2025 it ran **72.9% (CSPm — medium
  SP), 71.2% (CSPg — large SP), 75.5% (CGO — Goiás)** of the daily cattle cost;
  more recent reporting puts it at **~80% of operational cost.** [INDUSTRY]
- The headline outputs are **custo da diária** (cost per head per day, e.g.
  R$ 13.27 CGO to R$ 16.50 CSPg in July 2025) and **custo da arroba produzida**
  (cost per produced arroba). [INDUSTRY]
  (https://girodoboi.canalrural.com.br/pecuaria/gestao-na-propriedade/usp-registra-queda-nos-custos-da-diaria-do-boi-no-cocho-e-na-arroba-produzida/,
  https://girodoboi.canalrural.com.br/pecuaria/custo-da-arroba-produzida-no-confinamento-segue-em-baixa-em-sp-aponta-indice-da-usp)

*Discrepancy flagged:* one Canal Rural piece cites feed at "up to 85% of total
expenses, per ICBC/USP"; the ICBC monthly figures cited above are 71–80%. Use
**71–80%**, and treat 85% as an upper-bound trade-press rounding.

**A reporting-design critique, sourced.** The same Canal Rural piece names as
"the most common error in modern confinement" the practice of **managing on
average overall consumption**, when consumption depends on bunk time and animal
category — recommending dispersion analysis to find problem pens before they
generate losses. [INDUSTRY]
(https://girodoboi.canalrural.com.br/pecuaria/gestao-na-propriedade/confinamento-exige-controle-diario-da-alimentacao-para-evitar-perdas)

**Product implication.** Shipping IOFC as the flagship report speaks the wrong
language to a Brazilian feedlot. The flagship should be **custo da arroba
produzida** and **margin per head per cycle**, benchmarked against boi gordo, with
**ICBC as the external comparison** — "your daily cost vs. the CGO index" is a
report no US competitor can produce and every Brazilian manager already reads.
Secondary: **per-pen dispersion**, not averages. For a *boitel*, the flagship is
per-client, per-lot billing reconciliation. [INFERRED, on sourced findings]

---

### 14. Data export, integration, and lock-in

**Signal: weakest in the document. Adjacent-domain evidence only. Unchanged
after round 2.**

Nothing found about lock-in **in feed software specifically**. The material is
general agricultural data governance centred on John Deere Operations Center:
farmers cannot easily export yield or soil data to independent apps; historical
data is trapped in proprietary formats with switching costs described as ruinous;
ownership is signed away through unread EULAs. [INDUSTRY]
(https://www.vice.com/en/article/john-deere-tractor-hacking-big-data-surveillance/,
https://farmtario.com/machinery/the-legal-mess-of-farm-data-ownership/)

**Transferring machinery-data grievances onto feed software is an assumption.**
Plausible — same structure, proprietary format, high switching cost — but
unsourced for this category.

The nearest feed-specific items point the other way: FeedComp advertises **export
files for consultants**; TAP FEED advertises shareable reports. [VENDOR] Export
exists. Whether it is sufficient or resented is unknown from here.

Note that §7's *hardware* lock (TAP Feed ↔ Digi-Star indicators) is much better
evidenced than any *data* lock, and is the more actionable of the two.

**Product implication [INFERRED]:** a published, documented export (CSV plus a
stable API) is cheap and easy to market, and the John Deere backdrop means the
*language* of data ownership will land even where the specific grievance is
unproven. Build it; don't lead with it.

---

## 3. Brazil and Paraguay market fit

Several US-derived conclusions above **change or invert** in these markets.

### 3.1 Market size and structure — Brazil [INDUSTRY, well sourced]

- **9.25 million head** on feed in 2025, **+16% year over year**.
- Across **2,445 properties** in **1,095 municipalities**.
- **Mato Grosso leads with 2.2M head (+29.6%)**; São Paulo 1.4M (+7.7%); Goiás
  1.4M (+13.6%).
- **The 100 largest properties hold 48% of all confined cattle.**
- **Boitel (third-party custom feeding) hit a record 1.76M head, +19%.**
- 2026 projected at **9.78M head (+5.7%)**.

(https://girodoboi.canalrural.com.br/pecuaria/confinamento-cresce-16-e-supera-9-milhoes-de-cabecas-em-2025,
https://www.brasilagro.com.br/conteudo/confinamento-de-gado-cresceu-16-em-2025-no-brasil.html,
https://portaldbo.com.br/top-20-confinadores-2025/)

**What this dictates.** 48% of the market sits in ~100 accounts — an enterprise
sales motion into a concentrated, nameable list, not app-store self-serve. The
**boitel segment is the sharpest wedge**: a custom yard feeds cattle it does not
own, so per-lot, per-owner cost attribution *is the invoice*. No competitor found
in either round is positioned on boitel billing.

### 3.2 Market size and structure — Paraguay [INDUSTRY, thin — and it stayed thin]

- Roughly **5% of Paraguayan cattle production is intensive/feedlot**; feedlots
  are ~**5.6% of establishments by type**.
- Dominant model: grass to **300–350 kg**, then **~90 days** on feed to
  **480–500 kg**.
- Pasture finishing still dominates; confinement gaining, pushed by cropland
  competition.

(https://www.valoragro.com.py/ganaderia/la-escala-define-el-negocio-del-feedlot/,
https://www.abc.com.py/negocios/abc-campo/2025/03/11/el-ganadero-debe-apostar-al-confinamiento/)

**Round 2 searched Senacsa and ARP specifically and found nothing.** Queries
returned **Argentine** SENASA data instead (1,809,319 head on feed as of 1 April
2025, +5.7% y/y — useful regional context, not Paraguay).
**Paraguay head-on-feed and establishment counts remain unsourced. Do not size
the Paraguayan opportunity from this document.** ARP (https://www.arp.org.py/)
and Senacsa are the primary sources; neither was reachable.

**What this dictates.** Paraguay is a secondary market — smaller, less
concentrated, ~90-day cycles. Treat it as a Spanish-language extension of the
Brazilian product, not a separate build. A 90-day cycle makes **fast onboarding**
disproportionately important: three weeks to configure burns a third of a cycle.

### 3.3 Connectivity — the assumption to re-examine

Two facts in tension:

1. **73% of Brazilian rural producers lack connectivity; ~195M ha offline.**
   [INDUSTRY]
2. **Starlink is live and changing this fast** in both countries. In Paraguay,
   Chaco fibre is described as economically unviable on distance and terrain, and
   Starlink as breaking that constraint — installable in under 20 minutes, low
   power, already supporting cloud ERP and electronic invoicing from ranch
   offices, with 1,600 government kits and 500 school/community sites.
   [INDUSTRY] (https://www.forbes.com.py/innovacion/starlink-desarrollada-spacex-lleva-internet-alta-velocidad-comunidades-aisladas-chaco-n92290,
   https://mitic.gov.py/paraguay-llevara-internet-de-alta-velocidad-y-fiabilidad-de-starlink-a-500-escuelas-y-comunidades-rurales/)

**Synthesis [INFERRED]:** the *farm office* is getting connected; the *pen alley
and loader cab* are not. Starlink lands at headquarters, not at a bunk line 4 km
away. The architecture that follows: **field devices assume no connectivity and
sync opportunistically to a hub at HQ; the hub talks to the cloud.** Building
cloud-first because "Starlink solved it" is the mistake this data warns against.

### 3.4 The real competitive set — and it is not the one in the brief

**TGC (Ponta Agro) is the incumbent to beat.** Round 2 verified the share claim
as far as it can be verified — the figures are **Ponta Agro's own marketing plus
a Portal DBO placement branded "Espaço Ponta," which is paid content** — but they
are numerous and mutually consistent: [VENDOR, paid placement flagged]

- **>62% of Brazilian feedlots** use TGC; elsewhere "almost 70%."
- TGC **manages 68% of animals confined and slaughtered annually** in Brazil.
- **60% of the feedlots at the top of the national ranking** use Ponta tech.
- **12 of the 20 largest feedlots** in Brazil use TGC.

(https://pontaagro.com/ponta-esta-presente-em-60-dos-maiores-confinamentos/,
https://portaldbo.com.br/os-maiores-confinamentos-do-pais-tem-uma-estrategia-em-comum-o-uso-de-tecnologia-de-ponta-espaco-ponta-2/)

Treat the exact number as unverified; treat "TGC is the dominant incumbent,
especially at the top of the market" as established.

The Brazilian field, as now mapped:

| Product | Position |
|---|---|
| **TGC / Ponta Agro** | Dominant. Manejo, feeding, per-lot performance, stock, contracts, individual financial closeout. Offline + sync. Dedicated **leitura de cocho** app. |
| **Prodap** | Consultancy + software. **Camera-based automatic bunk-score reader** (bike/moto/car mounted) computing kg residue per line/pen/feeding and proposing the adjustment. Views Prime app, simultaneous multi-operator capture. Feed automation module covering mixer loading and distribution. |
| **SmartBov** | Feedlot automation: wagon weighing, smart bunk reading, truck-scale and silo integration, "do silo ao cocho" traceability. **Works with existing scales and mixers.** Plus SmartBov **Vision**, camera weighing with AI trained on Brazilian data. |
| **iRancho** | Web + iOS/Android. **100% offline** native capture. **BOS** with on-device NLP voice logging, no connection required. |
| **ArrobaPlus** | Offline mobile: feeding, bunk reading, movement, weighing. Low-connectivity positioning. |
| **FeedTratto** | Equipment-integrated: plans, manufactures and delivers to plan, real-time reporting, corral scale integration. |
| **Dinamica Generale (DTM / DTM ADV)** | Italian mixer-electronics giant. Cloud DTM + app; **DTM ADV sold in Brazil via Weightech, in Portuguese**, with nutritionist remote access. Also EVONIR NIR analysers. |
| **Leigado** | **LG4040 TMR wagon scale panel** — direct hardware competitor — plus beef software. |
| **Weightech** | Brazilian weighing manufacturer; DTM ADV channel; road-scale automation with remote displays. |
| **Bovitrato (SEYS)**, **Gestão Exacta**, **MultBovinos (Multsoft)**, **Farmin**, **Perfarm** | Broader herd/farm management with feedlot modules. |
| Mixer OEMs: **Nogueira**, **KUHN Brasil** | Wagon supply; scale-head bundling relationships. |

Southern Cone: Control Ganadero, BovControl, VacApp in use though not Paraguayan;
**Balanzas Vesta** manufactures mixer scales regionally; local feedlot software
advertised on Clasipar.

**No evidence was found that Libra Feed or TAP FEED have any Brazilian or
Paraguayan livestock distribution.** Topcon's exclusive Brazilian distributor is
**Embratop**, a geo-technology/surveying distributor
(https://www.facebook.com/embratop.geo/videos/980237152538540/); Portuguese
support portals exist (https://topconagstore.com/portuguese/support/) but the
channel is not livestock-native.

**Strategic consequence, sharpened since round 1.** Against the US incumbents,
"offline-capable Bluetooth mixer app" is a differentiator. **Against TGC,
Prodap, SmartBov, iRancho and ArrobaPlus it is parity or behind** — they shipped
offline years ago, and Prodap and SmartBov have moved on to computer vision.
Entering Brazil on an offline story means arriving late to a finished fight.

### 3.5 Where the opening actually is in Brazil

Given §3.4, the honest read [INFERRED, on sourced findings]:

- **Not** offline. **Not** bunk-score digitisation. **Not** "standardise your
  readers." All taken.
- **The scale link itself.** The Brazilian software layer is crowded and strong;
  the *hardware* layer is Leigado, Weightech, Balanzas Vesta and imported
  Digi-Star/Dinamica Generale. A reliable, INMETRO-approved, open indicator that
  any of the incumbent software can talk to — and that a lightweight app of your
  own can drive end-to-end — is a position none of the software companies hold.
- **Calibration discipline and phantom-weight rejection** (§1, §3) — sourced
  Brazilian failure modes, firmware-side, nobody marketing against them.
- **Boitel billing** (§3.1) — fastest-growing segment, unserved.
- **ICBC benchmarking** (§13) — externally credible, trivially computable from
  data you capture, and no competitor was found doing it.

### 3.6 Regulatory: legal metrology — the hardest gate, and it is on *your* hardware

This repository is scale firmware, which makes the following a **blocking
commercial issue**, not a compliance footnote.

**Brazil — INMETRO.** Non-automatic weighing instruments are governed by
**Portaria INMETRO nº 157/2022**. A manufacturer intending to commercialise a
weighing instrument must submit it for testing; passing yields a **Portaria de
Aprovação de Modelo**, which is what permits national sale. Instruments used in
**commercial buy/sell transactions must be approved and verified.** ABRAPEM
presses specifically for buying only **cattle scales with INMETRO model
approval.** [INDUSTRY]
(https://www.toledobrasil.com/blog/aprovacoes-e-verificacoes-que-uma-balanca-deve-ser-submetida,
https://balmak.com.br/novo/wp-content/uploads/2024/02/Portaria-157-2022.pdf,
https://folhaagricola.com.br/2026/07/10/alerta-para-riscos-economicos-e-juridicos-no-uso-de-balancas-sem-homologacao-do-inmetro/)

**Paraguay — INTN.** The Organismo Nacional de Metrología runs a Department of
Technical Regulation and Model Approval (homologación) and a Department for
Verification of Regulated Instruments covering weighing instruments.
**Manufacturers, importers and representatives must submit regulated instruments
for model approval and initial verification**, and such instruments may not be
held or transferred without initial verification. [INDUSTRY]
(https://intn.gov.py/onm-departamentos/)

**Three consequences [INFERRED, from sourced regulation]:**

1. **The boitel is the worst case and your best segment.** Custom feeding bills a
   third party for delivered feed — a commercial transaction measured by your
   scale. INMETRO approval is likely mandatory precisely in the segment §3.1
   identifies as the sharpest wedge. **Get a legal opinion before committing.**
2. **Model approval is long and expensive and gates hardware, not software.**
   Start it in parallel with development. It is also a moat once cleared.
3. **A software-only, bring-your-own-indicator path de-risks entry** — and §3.5
   says the opposite is the long-term position, so this is a sequencing decision:
   ship software against approved third-party indicators (Leigado LG4040,
   Weightech, Vesta, Digi-Star) while your own firmware clears approval.

### 3.7 Localisation checklist

- **Portuguese (pt-BR) and Spanish (es-PY), written not translated.** Vocabulary:
  *trato*, *leitura/escore de cocho*, *cocho lambido*, *lote*, *curral*,
  *arroba*, *boitel*, *tratorista*, *confinamento*, *GMD*, *conversão alimentar*,
  *matéria seca*, *custo da diária*, *custo da arroba produzida*.
- **Configurable bunk-score scale and score→adjustment rules** (§2). Non-optional.
- **Three-readings-a-day workflow with a true night mode** (§2, §10).
- **Metric throughout**, with **arroba (15 kg carcass)** for output.
- **Custo da arroba produzida and margin/head/cycle** as headline metrics, with
  **ICBC/USP benchmarking**, not IOFC (§13).
- **Android-first**, cheap-handset reference device (§7) — ~81% Android in Brazil.
- **BRL/PYG pricing**, per-cycle or per-mixer, not per-head-per-month (§11).
- **INMETRO / INTN model approval** on the roadmap from day one (§3.6).
- **WhatsApp as an output channel** for closeout summaries and run-out alerts.
  *Not sourced — no evidence found on WhatsApp use in feed operations
  specifically. Verify.*
- **LGPD** (Lei 13.709) applies to employee and client personal data, including
  operator performance records. *Not researched; flagged for legal review.*
- Environmental spec: **heat, dust, humidity, and darkness** — not cold, and not
  primarily sun glare (§10).

---

## 4. Corrections to round 1

Stated plainly, because they change conclusions:

1. **"Nobody is solving inter-reader bunk-score bias" — wrong.** Prodap ships a
   camera-based automatic bunk reader that computes residue in kg and proposes
   the adjustment; SmartBov advertises smart bunk reading and camera weighing.
   That ground is taken in Brazil. (§2)
2. **"Sun glare is the legibility problem" — incomplete to the point of being
   misleading.** Two of the three daily bunk readings happen in the dark
   (pre-dawn, and 21:00–22:00). Darkness is the dominant condition for the
   highest-frequency data-entry task. (§10)
3. **"Feed is 50–60% of production cost" holds for US dairy but understates
   Brazilian feedlots**, where ICBC/USP puts feed at **71–80% of daily cost.**
   A trade-press "85%" figure is an upper-bound rounding, not the index. (§13)
4. **The Brazilian competitive set was under-mapped.** Prodap, SmartBov,
   Dinamica Generale/Weightech and the mixer OEMs were missing from round 1. The
   TGC share claim is now traced to Ponta Agro's own marketing and a **paid** DBO
   placement — still credible directionally, but it is not independent. (§3.4)
5. **Multi-operator remains unevidenced** after a second targeted round. Round 1
   flagged it; round 2 confirms the absence rather than filling it. (§12)

---

## 5. What to verify — ranked by how much rests on it

1. **Reddit, entirely.** All five subreddits × eleven terms, unrun, twice
   confirmed unreachable. Largest single hole.
2. **Multi-operator / multi-mixer (§12).** Two rounds, zero producer evidence,
   high a-priori importance. Most likely place a real gap is hiding unmeasured.
3. **Paraguay, at all (§3.2).** Head-on-feed and establishment counts unsourced.
   Go to **ARP** (https://www.arp.org.py/) and **Senacsa** directly. Paraguay is
   currently sized on two sentences.
4. **Brazilian and Paraguayan producer voice.** Nothing here is a Brazilian or
   Paraguayan *producer complaining* — the BR/PY material is market structure,
   vendor claims, named consultants and regulation. Reclame Aqui returned nothing
   for this category. Try: Engormix forums, Facebook/WhatsApp confinamento
   groups, YouTube comments on Canal Rural / Giro do Boi feedlot segments and on
   the Prodap bunk-reader demo, and the DBO Top 20 Confinadores list as an
   interview frame.
5. **INMETRO applicability to boitel billing (§3.6).** Legal opinion. Can
   invalidate a go-to-market sequence.
6. **App-store reviews in full, both stores, all competitors.** Round 2 got
   headline numbers for Performance Beef (4.32/5, 63 ratings) and quotes from two
   apps. The full review lists would convert §1 from four utterances into a real
   defect distribution.
7. **Prodap's and SmartBov's camera readers.** How good are they actually, what
   do they cost, and do they need connectivity? §3.5's strategic conclusion
   depends on their being genuinely deployed rather than demo-stage.
8. **AgTalk/NewAgTalk thread bodies, read in full.** The summariser gives one
   passage per thread and drops operation type and head count. Threads worth
   opening: `tid=1146283` (replacing TMR Tracker, Jan 2024) · `tid=767237`
   (Performance Beef, Mar 2018) · `tid=461970` (scale-head legibility, Mar 2014)
   · `tid=531735` ("Who's keeping track of feed?", Jan 2015) · `tid=645018`
   ("Scales on the TMR problem.") · `tid=651508` (scale↔EID, small feedlot) ·
   `tid=725580` ("New Feed Management for Beef", Aug 2017) · `tid=1154746`
   ("Cattle management software recommendations???") · `tid=1024213`,
   `tid=1074154`, `tid=825294` (Performance Beef).
9. **The FeedWatch 26-dairy accuracy study.** Get the primary paper; the
   78.7%/21.9% figures are unverified and §3 leans on the variance shape.
10. **TGC's market share**, independently of Ponta Agro's own marketing (§3.4).
11. **YouTube comments** on: Libra TMR "Weighback (Feed Refusal)"
    (https://www.youtube.com/watch?v=XU8HCXJe5Us) · Libra TMR "Loading and
    Feeding" (https://www.youtube.com/watch?v=YpCoaHk0OI8) · Digi-Star TMR
    Tracker (https://www.youtube.com/watch?v=6QHpmMVywDw) · Prodap escore de
    cocho (https://www.youtube.com/watch?v=4dJI3DL7OpI) · Canal Rural feed
    control (https://www.youtube.com/watch?v=rAavomMBN8Y).

---

## 6. Bottom line

**Best-evidenced opportunities, in order of confidence:**

1. **Reliability of the scale link, as the product.** Four producer-voice items
   converge on it: crashes, dropped BLE, sync failures, and — worst — **weights
   that are wrong but accepted as right** ("phantom loads," "the scale not
   reading accurately from time to time"). Indicator-side buffering with replay,
   crash-safe partial-load resume, and firmware plausibility gating are available
   only to a team that owns both ends of the link. **This repo is that team.**
   (§2.1)
2. **Signed-bias loading feedback with per-ingredient tolerances**, plus
   **calibration as an enforced, tracked event.** The documented behavioural
   distortion — feeders systematically under-loading expensive ingredients
   because the report punishes overage — is a real, sourced, unaddressed failure
   of existing reporting design; uncalibrated wagon scales are a named Brazilian
   loss source. (§2.3)
3. **Android-first.** Libra Feed is iOS-only against ~81% Android in Brazil;
   TAP Feed is locked to Digi-Star indicators. Verified facts, direct
   consequences. (§2.7)
4. **The Brazilian bunk-reading workflow, done properly**: configurable score
   scales and adjustment rules, three readings a day, a true night mode, and the
   score→next-load loop actually closed at the mixer. Not the *idea* — that is
   taken — but the execution and the closed loop. (§2.2, §2.10)
5. **Boitel per-lot cost attribution and billing**, with **ICBC/USP
   benchmarking** as the reporting hook. Fastest-growing BR segment (+19%,
   1.76M head), unserved by any competitor found — subject to the INMETRO
   question. (§3.1, §2.13, §3.6)

**Things the brief expected that this evidence does not support:**

- **Offline is not a gap.** Parity in the US, table stakes in Brazil, and behind
  in Brazil if that is the pitch. The gap is sync *correctness* and HQ-hub
  visibility. (§2.5)
- **Pricing gripes are unevidenced.** Two rounds, zero producers complaining
  about feed-software pricing. The FX and per-cycle arguments in §2.11 are my
  reasoning, not producer voice.
- **Lock-in is unevidenced for this category.** The John Deere data-ownership
  literature is adjacent-domain. The better-evidenced lock is *hardware*
  (TAP Feed ↔ Digi-Star), not data. (§2.14, §2.7)
- **IOFC is likely the wrong flagship metric** for the stated target market.
  (§2.13)
- **Multi-operator remains a hypothesis**, not a finding. (§2.12)

**And the correction to the competitive frame:** for Brazil, the named competitor
set is the wrong one. The incumbent is **TGC/Ponta Agro**, with **Prodap** and
**SmartBov** already ahead on computer vision, **Dinamica Generale/Weightech** on
mixer electronics, and **Leigado** selling a competing wagon scale head. None of
them appeared in the brief. (§3.4)
