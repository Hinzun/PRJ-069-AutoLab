# PRJ069 AutoLab – návrh zadania

> **Stav:** zapracované rozhodnutia tímu (kapitola 10), 29. 10. 2026. Nie je to odovzdávaný výstup.
> Project Summary je z neho vyplnené v osobných repozitároch členov.

## 1. Zhrnutie

- **Téma AutoLab je dobrá a technicky zväčša správna.** Sedí aj na predmet: auto je uzavretá spätná väzba (snímanie → rozhodnutie → akcia) a 3D tlačený podvozok pokrýva digitálnu fabrikáciu.
- **AI špecifikácia je technický návrh, nie dokumentácia pre predmet.** Chýba v nej to, za čo dostaneme body: KNIFE, priebežná evidencia práce, SDLC / 7Ds dokumentácia a EA model. Je to dobrý vstup, z ktorého tieto výstupy poskladáme.
- **Harmonogram v špecifikácii je nereálny.** Počíta s 13 týždňami, ale sme v 7. týždni semestra. Do decembrovej prezentácie zostáva asi 6 týždňov.
- **Dohodnutý rozsah:** 2 autá, jazda z mobilu, nastaviteľné parametre, zastavenie pred prekážkou a pri strate spojenia. **Autá idúce za sebou do seba nenarazia**, a to bez vzájomnej komunikácie, len vďaka prednému senzoru. Sledovanie čiary len ak zostane čas.
- **Hardvér zjednodušený a zlacnený** (kapitola 6): napájanie z vlastnej powerbanky namiesto Li-ion článkov, lacnejší driver motorov. Cena klesne z ≈ 35–40 € na **≈ 15–20 € na auto** a odpadne riziko požiaru. Zároveň sú opravené hardvérové chyby špecifikácie (kapitola 4.2).

## 2. Čo od nás predmet reálne chce

Zdroje: stránka triedy [sthdf-2026.systemthinking.sk](https://sthdf-2026.systemthinking.sk/), [EA model](https://sthdf-2026.systemthinking.sk/en/sthdf/ea-model/), [K000119](https://knifes.systemthinking.sk/sk/knifes/K000119-klon-triedneho-repozitara/) a šablóny v našich repozitároch.

### Hodnotenie (podľa titulnej stránky triedy)

| Časť | Váha | Čo sa hodnotí |
|---|---|---|
| Priebežná práca | 75 % | príspevky KNIFE, systematická práca (priebežná evidencia aktivít a nápadov), zámer a kvalita projektu naprieč SDLC, zodpovednosť za spoločný výsledok, tímová spolupráca |
| Finálna prezentácia | 25 % | individuálny prínos, tímová spolupráca, dodané KNIFE |

**KNIFE sa hodnotí v oboch častiach. Každý z nás musí mať aspoň jeden vlastný.**

### Výstupy každého člena (vlastný repozitár, 7 sekcií)

1. About Me
2. Knowledge Contribution = **vlastný KNIFE článok**
3. Project Summary (schvaľuje cvičiaci)
4. Project Outcomes
5. Pitch (5–7 min)
6. Finálna prezentácia (10–12 min)
7. Reflexia

Repozitár sa odovzdáva ako odkaz, cvičiaci ho sám prenesie na stránku triedy.

### KNIFE nie je projektová dokumentácia

KNIFE je krátky znalostný článok typu „ako na to“ so štruktúrou:

- Rýchly návod
- Čo rieši
- Ako to rieši
- Ako to použiť
- Detailný článok
- Tipy
- Hodnota
- Zdroje

Projektová dokumentácia patrí inam: do sekcií 7Ds a SDLC v repozitári a do EA modelu. KNIFE môže z projektu čerpať, napr. „ako sme rozbehli WebSocket na ESP32“.

### Projektová dokumentácia

- **SDLC / V-model:** šablóny Project Outcomes, finálnej prezentácie aj minuloročných slajdov majú rovnaké poradie fáz:
  1. Business
  2. Top Level Architecture
  3. Solution Architecture
  4. Analysis
  5. Design
  6. Implementation
  7. Testing & Verification
  8. Operation
  9. Change Management
- **7Ds:**
  - D1 Management: ciele, plán, rozhodnutia, riziká, **evidencia práce**
  - D2 Motivation: stakeholderi
  - D3 Analysis
  - D4 Design
  - D5 Implementation
  - D6 Testing
  - D7 Lessons Learned
- **EA model:** spoločný model `sthdf_parent.qea` v Gite. Každý študent má vlastný balík `ST0XX`, zmeny posiela cez Pull Request a konflikty sa riešia v LemonTree. Zadanie a termíny ešte oznámi cvičiaci.

### Pre cieľ E/D z toho vyplýva

Funkčné demo nestačí. Body prinesú:

- KNIFE každého člena
- priebežne vyplnený denník aktivít
- rozumne vyplnené kľúčové sekcie SDLC
- pár diagramov v EA

## 3. Čo robili tímy v minulých rokoch

Archív ([sthdf-archiv](https://agnicoli.org/_sub/prod/images/STHDF-Dashboarh/sthdf-archiv.html)) ukazuje, že typický projekt býval **jedno malé zariadenie s Arduinom a 3D tlačou** pre 2–3 ľudí, s EA modelom, 7Ds, prezentáciou a videom. Príklady:

- **Meteostanica:** 2019
- **Detektor pádu:** 2019
- **Robotická korytnačka so senzormi:** 2020. Najbližšie k nám: robot so senzormi, EA model 7Ds a video na YouTube.
- **Lampa reagujúca na pohyb:** 2020
- **Arduino mini konzola:** 2020
- **Motorizácia montáže teleskopu:** 2021
- **Miešač kariet:** 2022
- **Model volejbalového trenažéra:** 2022
- **Dávkovač nápojov:** 2022

Minuloročné stránky projektov (2025/26) sú zväčša nevyplnené šablóny, inšpiráciu z nich nevytiahneme.

**Záver:** AutoLab (4 ľudia, 2 autá) je rozsahom primeraný, skôr na vyššej strane priemeru. Netreba ho zväčšovať, skôr osekať.

## 4. Posúdenie AI špecifikácie

### 4.1 Čo je dobré (ponechať)

- Systémový pohľad (Obr. 1): dve vnorené slučky, hranica systému, okolie, oneskorenie a kompromisy. Presne to chce predmet.
- Architektúra bez servera a aplikácie: ESP32 ako Wi-Fi AP a stránka priamo v aute. Jednoduchšie to už nejde.
- Rozdelenie požiadaviek podľa MoSCoW, merateľné ciele G1–G4 a testy naviazané na ciele.
- Bezpečnostné pravidlá: po zapnutí STOP, watchdog na spojenie, STOP pri prekážke.
- Protokol: krátke JSON správy a pravidlo „platí hodnota potvrdená autom“.
- Režimy STOP / MANUAL / LINE. Do EA z nich priamo vznikne stavový diagram.
- Riziká a rozšírenia mimo rozsahu.

### 4.2 Chyby, ktoré treba opraviť

| # | Problém | Prečo vadí | Oprava |
|---|---|---|---|
| H1 | Senzory čiary TCRT5000 sú napájané z 5 V a ich výstup ide priamo do GPIO 34/35/39 | ESP32 piny nezvládajú 5 V, hrozí poškodenie | moduly napájať z **3,3 V** (LM393 moduly na 3,3 V fungujú) |
| H2 | HC-SR04 na 5 V s deličom na ECHO | funguje, ale delič je zbytočná práca a zdroj chýb | kúpiť **HC-SR04P / RCWL-1601** (3–5,5 V), napájať z 3,3 V, bez deliča |
| H3 | STBY drivera natvrdo na 3,3 V; GPIO 14 pri štarte ESP32 krátko generuje PWM | motor môže pri zapnutí cuknúť a „po zapnutí je auto v STOP“ neplatí na úrovni hardvéru | STBY pripojiť na voľný GPIO (napr. 32) a zapnúť ho až po inicializácii |
| H4 | Chýba nabíjačka 18650 a ochrana článkov | bez nabíjačky autá nepojedú; nechránené články sú riziko požiaru | chránené články alebo 2S BMS, nabíjačka (≈ 10–15 €, ak nie je v labe), kondenzátor 470 µF na VM |
| H5 | Moduly (TB6612, MP1584) sa často predávajú s nepripájanými kolíkmi a ESP32 DevKit sa nezmestí na jedno nepájivé pole | máme málo skúseností so spájkovaním | kúpiť verzie s napájanými kolíkmi alebo spájkovať v SmartLabe; zvážiť **rozširujúcu dosku pre ESP32 so skrutkovými svorkami** (pozor, 30 vs. 38 pinov) |
| F1 | Meranie HC-SR04 cez `pulseIn` blokuje slučku až ~38 ms | v rozpore s „loop nikdy neblokuje“, 50 Hz slučka by sa rozpadla | `pulseIn` s krátkym timeoutom (pri `stop_cm ≤ 50` stačí ~4 ms) alebo meranie cez prerušenie |
| F2 | Parameter `trim` nie je vo vzorci PD | nastavenie by nič nerobilo | `PWM_L = base + korekcia + trim`, `PWM_R = base − korekcia − trim` |
| F3 | Chyba čiary má len 3 hodnoty (−1, 0, +1) | regulátor je hrubý a kmitá | pridať medzistavy: ľavý+stred = −0,5, stred+pravý = +0,5, stratená čiara = ±2 |
| F4 | STOP pri batérii pod 6,6 V zo surového merania | pri rozjazde napätie krátko klesne, auto by falošne zastavovalo | priemerovať merania a zastaviť až po niekoľkých sekundách pod hranicou |
| F5 | Knižnica ESPAsyncWebServer | pôvodná verzia (me-no-dev) sa už neudržiava | použiť udržiavaný fork `ESP32Async/ESPAsyncWebServer` |
| P1 | Harmonogram T1–T13 | sme v 7. týždni, presunulo by to demo do januára | nový plán v kapitole 7 |
| P2 | Objednávka z Číny (AliExpress) | dodanie 2–4 týždne, to si už nemôžeme dovoliť | kupovať lokálne (LaskaKit, Botland, techfun.sk, GME), dodanie za 2–5 dní |

> Po zjednodušení hardvéru (kapitola 6) odpadajú H3, H4 a F4: driver DRV8833 nemá STBY, powerbanka nahrádza Li-ion články a batériu nemeriame.

Menšie výhrady:

- **G3 nie je merateľný.** „Bez viditeľného oneskorenia“ nahradiť „odozva do 200 ms“.
- **G1 je zbytočne prísny.** Cieľ 9 z 10 kôl pri cieli E/D stačí znížiť na „3 kolá za sebou“.
- **Kanály Wi-Fi:** obe autá dať na rôzne kanály (1 a 6), menej sa budú rušiť.

### 4.3 Čo v špecifikácii chýba

1. **Prečo to robíme (Business):** problém, používateľ, hodnota. Pitch aj Project Summary to vyžadujú.
   - Lacný príbeh: *AutoLab ako lacná učebná pomôcka (≈ 35 € na auto), na ktorej si stredoškoláci „ohmatajú“ spätnú väzbu a ladenie parametrov.*
   - Nadväzuje na KNIFE K000059 (STEM a Makerspace).
2. **Mapovanie na výstupy predmetu:** SDLC fázy, 7Ds, EA diagramy a KNIFE každého člena (kapitola 9).
3. **Evidencia práce:** kto, kedy, čo urobil. Hodnotí sa priamo a nikde v špecifikácii nie je.
4. **Mená a ID členov, ID projektu a názov repozitára.** Tímová dokumentácia pôjde do spoločného repozitára, podľa K000119 pomenovaného `PRJ-069-AutoLab`. Tím je zatiaľ len v Exceli cvičiaceho. Na stránku triedy ho doplní cvičiaci, rovnako ako minulý rok.
5. **Pôvodný nápad zmizol.** Ochrana proti nárazu áut idúcich za sebou je v špecifikácii len ako voliteľný „režim konvoj“. Vraciame ju ako *Must*, ale **bez komunikácie medzi autami**: zadné auto vidí predné ultrazvukom a zastaví samo. Stačí na to požiadavka FR-03 a rovná zadná stena podvozku, od ktorej sa ultrazvuk dobre odrazí (FR-09).

## 5. Navrhované zadanie (minimum pre E/D)

**ID projektu:** `PRJ_069_ST21_ST22_ST23_ST32` · **Názov:** AutoLab

**Zadanie v jednej vete:** Navrhnúť a postaviť 2 autíčka s 3D tlačeným podvozkom a ESP32, ktoré sa dajú riadiť z mobilu cez webovú stránku v aute a umožňujú za jazdy meniť parametre. Samy zastavia pred prekážkou, pred autom idúcim pred nimi alebo pri strate spojenia. Na nich ukážeme princípy spätnej väzby zo systémového myslenia.

### Požiadavky (upravené)

| ID | Požiadavka | Priorita |
|---|---|---|
| FR-01 | Režim MANUAL: jazda joystickom na stránke | **Must** |
| FR-03 | Kým je prekážka bližšie ako `stop_cm`, auto nejde dopredu (zabrzdí); cúvať a otáčať sa dá. Keď prekážka zmizne, jazda pokračuje. | **Must** |
| FR-09 | Autá za sebou do seba nenarazia: zadné auto zastaví pred predným aj pri `max_pwm`. Bez komunikácie, len cez FR-03; podvozok má vzadu rovnú stenu na odraz ultrazvuku. | **Must** |
| FR-04 | Zastavenie do 1 s po strate spojenia | **Must** |
| FR-05 | Zmena parametrov za jazdy (`max_pwm`, `trim`, `stop_cm`) | **Must** |
| NFR-01 | Stránka v mobile aj notebooku bez inštalácie | **Must** |
| NFR-02 | Hodnota mimo rozsahu sa odmietne | **Must** |
| FR-02 | Režim LINE: sledovanie čiary (+ parametre `base`, `kp`, `kd`) | Should (len ak zostane čas) |
| FR-06 | Živé hodnoty senzorov na stránke (vzdialenosť, PWM) | Should |
| FR-07 | Uloženie parametrov do auta | Could |
| FR-08 | Graf chyby čiary | Won't (vypustiť) |
| NFR-03 | Výdrž 30 min, meranie batérie | Won't (powerbanka má vlastný ukazovateľ) |

### Akceptačné kritériá (demo)

| Cieľ | Test | Splnené, ak |
|---|---|---|
| G1 | jazda z mobilu po miestnosti, obe autá naraz z dvoch mobilov | obe autá jazdia, odozva do 200 ms |
| G2 | zmena `max_pwm` a `trim` za jazdy | správanie sa zmení do 0,5 s |
| G3 | krabica v ceste pri jazde | auto zastaví pred ňou v 5 z 5 pokusov |
| G4 | vypnúť Wi-Fi v mobile počas jazdy | auto zastaví do 1 s |
| G6 | autá za sebou: predné prudko zastaví, zadné ide na `max_pwm` | zadné auto zastaví bez dotyku v 5 z 5 pokusov |
| G5 (Should) | režim LINE na ováli z izolačnej pásky | 3 kolá za sebou bez vybočenia |

G6 je zároveň pekná ukážka systémového myslenia: brzdná dráha závisí od rýchlosti a oneskorenia merania. Pri vysokom `max_pwm` a malom `stop_cm` auto narazí. Na deme to ukážeme dvoma slidermi.

**Mimo rozsahu:** server, databáza, mobilná aplikácia, kamera, enkodéry, sandbox so súťažnými úlohami (ten môže byť námet do „ďalších krokov“ v prezentácii).

## 6. Hardvér (zjednodušený a lacnejší)

### Čo meníme oproti špecifikácii

| Zmena | Úspora | Prečo |
|---|---|---|
| **Napájanie z powerbanky (5 V USB)** namiesto 2× 18650 + držiak + menič + nabíjačka + delič | ≈ 12–15 € na auto + nabíjačka | powerbanku má každý; TT motory sú na 3–6 V, takže 5 V im sedí; odpadá Li-ion riziko a meranie batérie |
| **Driver DRV8833** namiesto TB6612FNG | ≈ 1–2 € na auto | stačí na TT motory, má len 4 riadiace piny a vie brzdiť; odpadá aj problém so STBY (H3) |
| **HC-SR04P / RCWL-1601** (3–5,5 V) namiesto HC-SR04 | 0 € (rovnaká cena) | funguje na 3,3 V bez deliča (H2) |
| **Senzory čiary kúpiť až neskôr**, ak bude čas na LINE | ≈ 3 € na auto | sú len *Should* |
| **Malé nepájivé pole** namiesto pájanej dosky alebo svorkovnice | ≈ 2–3 € na auto | stačí na demo |
| **Spýtať sa v SmartLabe**, či nepožičajú ESP32, motory alebo senzory | potenciálne väčšina ceny | laboratórium dronov a AI pravdepodobne má zásobu súčiastok |

### Diely na jedno auto (orientačné ceny, overiť pri objednávke)

| Diel | Ks | ≈ € |
|---|---|---|
| ESP32 DevKit V1 (WROOM-32) | 1 | 5–7 |
| TT motor s prevodovkou + koleso 65 mm | 2 | 3–5 |
| DRV8833 modul | 1 | 1–2 |
| HC-SR04P / RCWL-1601 | 1 | 1,5–2 |
| guľové koliesko, skrutky M3 | 1 | 1 |
| mini nepájivé pole, dupont káble, kondenzátor 1000 µF | 1 | 2 |
| 3D tlačený podvozok (PETG, SmartLab) | 1 | ≈ 1 |
| USB kábel + powerbanka (vlastná) | 1 | 0 |
| **Spolu** | | **≈ 15–20** |

**Dve autá ≈ 30–40 €, teda ≈ 8–10 € na osobu** (predtým ≈ 20–25 €). Ak SmartLab niečo požičia, bude to ešte menej. Senzory čiary pridajú ≈ 3 € na auto, ak budeme robiť LINE.

### Zapojenie (upravené)

| Signál | Pin ESP32 | Poznámka |
|---|---|---|
| DRV8833 AIN1 / AIN2 (motor L) | GPIO 25 / 26 | PWM na oboch pinoch |
| DRV8833 BIN1 / BIN2 (motor R) | GPIO 32 / 33 | piny bez zákmitov pri štarte, motory pri zapnutí necuknú |
| HC-SR04P TRIG / ECHO | GPIO 5 / 18 | napájanie 3,3 V, bez deliča |
| (Should) senzory čiary L / S / P | GPIO 34 / 35 / 39 | napájanie **3,3 V** (H1) |
| Napájanie | USB z powerbanky do ESP32; 5 V pin ESP32 (VIN) → VM na DRV8833 | 1000 µF kondenzátor pri VM |

### Riziká powerbanky a opatrenia

- **Powerbanka sa sama vypne pri malom odbere.** Pred nákupom otestovať tú, ktorú použijeme (ESP32 s Wi-Fi odoberá ≈ 100 mA, väčšinou stačí). Ak sa vypína, náhradou je držiak 4× AA.
- **ESP32 sa reštartuje pri rozjazde motorov.** Opatrenia: kondenzátor 1000 µF, plynulý rozjazd v firmvéri (PWM rampa) a powerbanka s výstupom aspoň 2 A.
- **Hmotnosť a rozmer.** Podvozok navrhnúť podľa konkrétnej powerbanky (držiak na ňu je súčasť 3D modelu).

## 7. Harmonogram od teraz

Predpoklad: finálna prezentácia v decembri, možno až v januári. Termín zatiaľ nie je určený, v notebooku sú len minuloročné dátumy (8.–15. 12.) s poznámkou, že sa určia neskôr. Plánujeme na najskorší termín (týždeň od 7. 12.). Ak bude v januári, máme rezervu.

| Týždeň | Termín | Hlavná úloha | Míľnik |
|---|---|---|---|
| 8 | 2.–8. 11. | rozhodnúť zadanie, Project Summary cvičiacemu, **objednať diely**, model podvozku v Onshape, kostra stránky na holom ESP32 | Project Summary odovzdané, diely objednané |
| 9 | 9.–15. 11. | prvá tlač podvozku v SmartLabe, motory + driver na stole, stránka s joystickom na ESP32 | motory sa točia podľa joysticku |
| 10 | 16.–22. 11. | auto 1 zložené: MANUAL, STOP pri prekážke, STOP pri strate spojenia; začať EA model | **auto 1 spĺňa G1, G3, G4** |
| 11 | 23.–29. 11. | slidery s parametrami, zložiť auto 2; ak je čas, LINE | obe autá jazdia (G2) |
| 12 | 30. 11.–6. 12. | testy podľa protokolu, video, dokumentácia SDLC/7Ds, dokončiť KNIFE, slajdy | testy zapísané, prezentácia hotová |
| 13 | 7.–13. 12. | finálna prezentácia a demo | ✅ |

Pitch už bol. Do sekcie Pitch Presentation v repozitári stačí doplniť, čo sme odprezentovali.

**Poistka:** softvér (stránka, protokol, parametre) sa dá vyvíjať a ukázať aj na holom ESP32 bez auta. Ak hardvér mešká, demo nezlyhá úplne.

## 8. Rozdelenie práce (4 členovia)

Každý má jednu technickú časť **a** svoj podiel na dokumentácii a vlastný KNIFE. Tie sa hodnotia individuálne.

Rozdelenie je predbežné (na rolách tímu nezáleží), členovia si ho môžu kedykoľvek vymeniť.

| Rola | Kto | Technická časť | Dokumentácia | EA diagramy (vlastný balík `ST0XX`) | Návrh témy KNIFE |
|---|---|---|---|---|---|
| A – hardvér | Branislav Bučko (ST021) | podvozok (Onshape, tlač v SmartLabe), zapojenie, napájanie | D4 Design, zoznam dielov, Operation (návod, bezpečnosť) | blokový diagram hardvéru, deployment | „Od 3D modelu po vytlačený podvozok v SmartLabe“ |
| B – riadenie | Adrián Fáber (ST023) | firmvér: motory, senzor vzdialenosti, režimy, brzdenie pred prekážkou | D5 Implementation, protokol testov | stavový diagram STOP / MANUAL / (LINE) | „Spätná väzba na stole: prečo auto narazí, keď ide príliš rýchlo“ (systémové myslenie) |
| C – komunikácia | Erik Dusík (ST022) | firmvér: Wi-Fi AP, WebSocket, parametre a ich rozsahy | Solution Architecture, protokol správ | sekvenčný diagram (zmena parametra → potvrdenie) | „Ovládanie ESP32 z mobilu bez aplikácie (Wi-Fi AP + WebSocket)“ |
| D – stránka a vedenie | Samuel Roháč (ST032) | webová stránka (joystick, slidery, stav) | Business, Project Summary, D1 Management (plán, riziká, rozhodnutia), Change Management | požiadavkový diagram, use case | „Zdieľaný EA model cez Git a LemonTree – naša skúsenosť“ |

Spoločne: denník aktivít (každý si zapisuje vlastný), testy, video a prezentácia.

## 9. Mapovanie na výstupy predmetu

| SDLC fáza (poradie z prezentácie) | Čo tam dáme | Zdroj |
|---|---|---|
| 01 Business | problém, používateľ (učiteľ/študent STEM), hodnota, stakeholderi | kapitola 4.3 tohto návrhu |
| 02 Top Level Architecture | systémový pohľad, dve slučky, hranica systému | špecifikácia, kap. 3 (Obr. 1) |
| 03 Solution Architecture | vrstvy stránka / komunikácia / logika / hardvér | špecifikácia, kap. 5 |
| 04 Analysis | požiadavky MoSCoW, rozhodnutia, riziká, rozpočet | kap. 5 tohto návrhu, špecifikácia, kap. 6, 11 |
| 05 Design | zapojenie, podvozok, protokol, parametre, UI | špecifikácia, kap. 6, 8, 9 (s opravami) |
| 06 Implementation | firmvér, stránka, STL, fotky | repozitár `PRJ-069-AutoLab` |
| 07 Testing & Verification | protokol testov G1–G5 | kap. 5 tohto návrhu |
| 08 Operation | návod na použitie, nabíjanie, bezpečnosť | nové |
| 09 Change Management | čo sme zmenili oproti plánu a prečo | nové, priebežne |

## 10. Rozhodnutia tímu (29. 10. 2026)

| # | Otázka | Rozhodnutie |
|---|---|---|
| 1 | Sledovanie čiary | len ak zostane čas (*Should*) |
| 2 | Pôvodný nápad | autá za sebou do seba nenarazia, **bez komunikácie** medzi nimi (FR-09, G6) |
| 3 | Role | na rolách nezáleží; predbežné rozdelenie v kapitole 8 |
| 4 | Nákup a náklady | objedná ktokoľvek, delíme sa rovným dielom; cenu znižujeme (kapitola 6) |
| 5 | Názov | **AutoLab** |

### Ešte otvorené

1. Či predbežné rozdelenie rolí v kapitole 8 všetkým vyhovuje.
2. Čo vie SmartLab požičať (súčiastky, spájkovačka) a kedy môžeme tlačiť.
3. Či máme powerbanky, ktoré sa pri malom odbere nevypínajú (otestovať s ESP32).
