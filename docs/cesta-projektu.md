# Cesta projektu

Predmet má medzi základnými princípmi **„The goal is the journey“** a 75 % známky ide za priebežnú prácu. Sem preto priebežne zapisujeme, čo sme skúšali, čo nevyšlo, čo sme zmenili a prečo.

Kompletná 12-týždňová syntéza a scenár finálnej prezentácie sa nachádza v samostatnom dokumente:  
👉 **[12-týždňová Roadmapa a Cesta projektu](cesta-a-roadmapa-12-tyzdnov.md)**

## Pravidlá

- Zapisuj hneď, ideálne v ten istý deň. Pár viet stačí.
- Zapíš aj to, čo nevyšlo (zlyhania majú pre hodnotenie rovnakú váhu ako úspechy).
- Ku každému záznamu pridaj dôkaz: commit, fotku, video alebo dokument.
- Nové záznamy pridávaj na koniec tabuľky alebo chronologicky podľa týždňov.
- Čo robíš ty osobne, zapíš aj do svojho denníka aktivít v osobnom repozitári. Pomôcka je v [zachytavanie-prace.md](zachytavanie-prace.md).

## Šablóna záznamu

| Dátum / Týždeň | Autor | Čo sme skúšali | Výsledok | Rozhodnutie a prečo | Dôkaz |
|---|---|---|---|---|---|
| | | | | | |

## Záznamy chronologicky (Týždne 1 – 12)

| Dátum / Týždeň | Autor | Čo sme skúšali | Výsledok | Rozhodnutie a prečo | Dôkaz |
|---|---|---|---|---|---|
| **T1** (koniec sept.) | tím | zoznámenie tímu 4 študentov FIIT | zmapované osobné zručnosti (silný softvér, slabší hardvér/CAD) | tím je zostavený, začíname hľadať tému | záznam zo stretnutia, repozitár |
| **T2** (zač. okt.) | tím | hľadanie spoločného prieniku záujmov | zistený silný spoločný záujem všetkých 4 členov o autá a motorizmus | projekt sa bude venovať autám/automotive doméne | [roadmapa](cesta-a-roadmapa-12-tyzdnov.md#týždeň-2-hľadanie-spoločného-prieniku--automotive-vášeň) |
| **T3** (október) | tím | nápad zákazkovej 3D tlače dielov na reálne autá | návrh tlačiť chýbajúce plastové diely, klipy a doplnky do interiéru | spojenie automotive témy s požiadavkou na digitálnu fabrikáciu | [roadmapa](cesta-a-roadmapa-12-tyzdnov.md#týždeň-3-pôvodný-nápad--zákazková-3d-tlač-dielov-na-autá) |
| **T4** (október) | tím | technický a materiálový prieskum 3D tlače autodielov | bežné PLA sa v aute topí (70 °C+); nutnosť ASA/PETG a extrémne presných tolerancií | vysoká technologická náročnosť, nutnosť testovať na reálnych autách | poznámky k materiálom |
| **T5** (október) | tím | **biznisová a logistická analýza 3D tlače autodielov** | **Kritické zlyhanie konceptu:**<br/>1. Pri 1 modeli auta je okruh zákazníkov miniatúrny.<br/>2. Pri viacerých autách je nezvládnuteľné množstvo unikátnych dielov.<br/>3. On-demand tlač trvá pridlho (zákazník nechce čakať dni).<br/>4. Vysoké náklady a nulová rentabilita – *„neboli by z toho love“*. | **OKAMŽITÝ STOP NÁPADU.** Zákazková 3D tlač autodielov nedáva zmysel, nemali by sme zákazníkov ani udržateľnú logistiku. | [analýza zlyhania v roadmapy](cesta-a-roadmapa-12-tyzdnov.md#týždeň-5-hĺbková-biznisová-a-logistická-analýza--bod-zlyhania) |
| **T6** (29. 10. 2026) | tím | **strategický pivot na softvérové riešenie** | uvedomenie: sme informatici, naša sila je v algoritmoch, riadení a softvéri, nie v mechanickej výrobe plastov | prechod na softvérové riadenie malého autíčka (AutoLab); 3D tlač bude podporný funkčný prvok | [rozhodnutia tímu 29. 10.](../archiv/esp32/navrh-zadania.md#10-rozhodnutia-tímu-29-10-2026) |
| **T6** (29. 10. 2026) | tím | ujasnenie rozsahu projektu AutoLab | dohodnuté rozhodnutia tímu: 2 autá, autonómne brzdenie pred prekážkou | autá do seba nenarazia bez vzájomnej komunikácie, sledovanie čiary voliteľne | [návrh zadania, kap. 10](../archiv/esp32/navrh-zadania.md#10-rozhodnutia-tímu-29-10-2026) |
| **T6** (29. 10. 2026) | Erik Dusík | posúdenie AI špecifikácie od kolegu | nájdené hardvérové aj softvérové chyby a nereálny harmonogram | vychádzame z opravenej špecifikácie, nie z pôvodného PDF | [návrh zadania](../archiv/esp32/navrh-zadania.md#4-posúdenie-ai-špecifikácie) |
| **T7** (5. 11. 2026) | Erik Dusík | zníženie ceny a rizika vlastného hardvéru (ESP32) | návrh na powerbanku a DRV8833, odhad ≈ 20–23 € na auto | zjednodušiť napájanie, lebo odpadá nabíjačka a riziko Li-ion článkov | [nákupný zoznam](../archiv/esp32/hardware/nakupny-zoznam.md) |
| **T7** (5. 11. 2026) | Erik Dusík | firmvér a stránka pre ESP32 | napísané a otestované na PC, na ESP32 ešte nebežali | pokračovanie závisí od výberu projektu | [firmvér](../archiv/esp32/firmware/README.md), commit `1668629` |
| **T8** (5. 11. 2026) | Erik Dusík | otázka, či treba kupovať vlastné diely na autá | cvičiaci odporučil použiť požičané mBot2 zo SmartLabu a zbytočne neminúť peniaze | nákup dielov je pozastavený, zvažujeme prechod na mBot2 | ústne od cvičiaceho; [návrh zadania](../archiv/esp32/navrh-zadania.md#7-harmonogram-od-teraz) |
| **T8** (5. 11. 2026) | Erik Dusík | hľadanie nápadov pre platformu mBot2 | vznikli možnosti Brzdná výzva a Nerozlej, na aute zatiaľ neskúšané | tím posúdi možnosti s cieľom minimalizovať hardvérové riziko | [Brzdná výzva](../archiv/brzdna-vyzva.md), [Nerozlej](moznost-nerozlej.md) |
| **T9** (16. 11. 2026) | Erik Dusík | výber konceptu Nerozlej (kuriér s loptičkou) | tím sa zhodol na Nerozlej; cvičiaci nemá námietky | pracujeme na Nerozlej; Brzdná výzva a ESP32 sú presunuté do archívu | [stav projektu](stav-projektu.md#rozhodnutia), [Nerozlej](moznost-nerozlej.md) |
| **T9** (16. 11. 2026) | Erik Dusík | zjednodušenie rozsahu Nerozlej | jedna 3D nádoba namiesto viacerých hĺbok, jadrom sú parametre jazdy | menej zbytočnej tlače, obtiažnosť dávajú softvérové parametre (rýchlosť, akcelerácia) | [Nerozlej, Rozsah](moznost-nerozlej.md#rozsah) |
| **T10** (16. 11. 2026) | Erik Dusík | program pre mBot2 v MicroPythone a testy na PC so simuláciou auta | 20 testov prešlo; MicroPython overený mockovacím skriptom | MicroPython namiesto blokov, lebo sa dá verzovať a testovať bez prítomnosti v labe | [mbot2/](../mbot2/README.md) |
| **T10** (16. 11. 2026) | Erik Dusík | upratanie repozitára | verzia s ESP32 a Brzdná výzva sú v priečinku `archiv/`, požiadavky predmetu osamostatnené | hlavný repozitár je čistý a pripravený na verifikáciu | [archív](../archiv/README.md) |
| **T11** (koniec nov.) | tím | fyzické testy v SmartLabe a 3D tlač nádoby | overené správanie CyberPi na čiare, úspešná tlač ergonomického podnosu na loptičku | prechod akceptačných testov N1–N6, doladenie prahov zákrut | [tahak-lab](../mbot2/tahak-lab.md) |
| **T12** (zač. dec.) | tím | systémová syntéza, SDLC kompletizácia a príprava prezentácie | uzavretá kompletná dokumentácia podľa SDLC, pripravená prezentácia a pitch | tím je pripravený na obhajobu a odovzdanie osobných repozitárov | [roadmapa](cesta-a-roadmapa-12-tyzdnov.md#scenár-finálnej-prezentácie-storytelling-pre-obhajobu), [prezentacia](prezentacia.md) |
