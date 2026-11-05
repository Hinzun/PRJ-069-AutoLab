# Dokumentácia AutoLab podľa SDLC

Poradie fáz zodpovedá štruktúre finálnej prezentácie a sekcie Project Outcomes. Pri každej fáze je, čo do nej patrí a kto ju má na starosti (podľa predbežného rozdelenia rolí).

| Fáza | Čo tam patrí | Zodpovedá | Stav |
|---|---|---|---|
| 01 Business | problém, používateľ, hodnota, stakeholderi | Samuel Roháč | návrh v [navrh-zadania.md](navrh-zadania.md), kap. 4.3 |
| 02 Top Level Architecture | systémový pohľad: dve spätné väzby, hranica systému | Erik Dusík | návrh v [specifikacia.md](specifikacia.md), kap. 2 |
| 03 Solution Architecture | vrstvy stránka / komunikácia / logika / hardvér, protokol správ | Erik Dusík | návrh v [specifikacia.md](specifikacia.md), kap. 3 a 6 |
| 04 Analysis | požiadavky, rozhodnutia, riziká, rozpočet | Samuel Roháč | návrh v [navrh-zadania.md](navrh-zadania.md), kap. 5–6 |
| 05 Design | zapojenie, podvozok, parametre, UI | Branislav Bučko | ☐ |
| 06 Implementation | firmvér, stránka, STL, fotky | všetci | [firmvér a stránka](../firmware/README.md) napísané, na hardvéri neoverené; STL ☐ |
| 07 Testing & Verification | [protokol testov](testovaci-protokol.md) | Adrián Fáber | ☐ |
| 08 Operation | návod na použitie, bezpečnosť | Branislav Bučko | ☐ |
| 09 Change Management | čo sme zmenili oproti plánu a prečo | Samuel Roháč | zoznam nižšie |

Diagramy kreslíme v Enterprise Architect, každý vo svojom balíku `ST0XX` v triednom EA modeli. Sem dávame ich exporty (PNG).

## Možnosti projektu

Zvažované alternatívy, zatiaľ neschválené:

- [Nerozlej](moznost-nerozlej.md): robot-čašník na mBot2 vezie loptičku po čiare
- [Brzdná výzva](moznost-brzdna-vyzva.md): na mBot2 sa súťaží, kto zastaví najbližšie pri prekážke bez dotyku

## Cesta projektu a prezentácia

- [Cesta projektu](cesta-projektu.md): čo sme skúšali, čo nevyšlo a prečo sme to zmenili
- [Čo zachytávať počas práce](zachytavanie-prace.md): pomôcka pre tím a prepis do denníka aktivít
- [Podklady k finálnej prezentácii](prezentacia.md): biznisový obrázok, aktuálny stav, plán vs. dodané
- [Vzory z minulých rokov](vzory-projektov.md): CarCharm, Dog-Fit a čo nám oproti nim chýba

## Zmeny oproti plánu

| Dátum | Zmena | Prečo |
|---|---|---|
| 5. 11. 2026 | `trim` pôsobí na veľkosť PWM, nie priamo na hodnotu so znamienkom | pôvodný vzorec by pri cúvaní zhoršoval odchýlku a mohol otočiť smer pomalého kolesa |
| 5. 11. 2026 | senzor sa meria cez prerušenie, nie cez `pulseIn` | slučka nečaká ani tie 4 ms |
| 5. 11. 2026 | motory sa napájajú z lišty poľa, nie cez pin 5 V na ESP32 | dióda na doske nemusí zvládnuť prúd motorov |
| 5. 11. 2026 | doplnené pripojenie `nSLEEP` na DRV8833 | pôvodný návrh mylne uvádzal, že driver takýto pin nemá; bez neho by sa motory netočili |
| 5. 11. 2026 | bežný HC-SR04 na 5 V s deličom namiesto HC-SR04P | HC-SR04P sme v overených obchodoch nenašli |
| 5. 11. 2026 | harmonogram posunutý, prezentácia v januári 2027 | termín prezentácie, diely ešte neboli objednané |
| 5. 11. 2026 | cvičiaci odporučil použiť požičané mBot2 namiesto kúpy dielov | netreba zbytočne míňať vlastné peniaze; výber projektu je zatiaľ otvorený |
| 5. 11. 2026 | nákup dielov pozastavený | kým sa tím nerozhodne, či ostane pri ESP32, alebo prejde na mBot2 |
