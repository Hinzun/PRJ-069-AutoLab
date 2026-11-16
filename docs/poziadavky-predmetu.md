# Požiadavky predmetu

Čo predmet SMVIT (STHDF) od nás chce a ako vyzerali projekty z minulých rokov. Prevzaté z pôvodného [návrhu zadania](../archiv/esp32/navrh-zadania.md), kapitoly 2 a 3, stav z 29. 10. a 5. 11. 2026. Vzory formy dokumentácie sú vo [vzoroch projektov](vzory-projektov.md).

## Čo od nás predmet chce

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

Projektová dokumentácia patrí inam: do sekcií 7Ds a SDLC v repozitári a do EA modelu. KNIFE môže z projektu čerpať, napr. „ako naprogramovať mBot2 v MicroPythone“.

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

## Čo robili tímy v minulých rokoch

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

Zo stránok projektov ročníka 2025/26 je približne 19 z 30 vyplnených a 11 sú prázdne šablóny (stav 5. 11. 2026). Inšpiráciou môžu byť napríklad LED Piano Trainer, SmartClock alebo PixelPet.
