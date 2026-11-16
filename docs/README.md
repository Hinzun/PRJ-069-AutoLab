# Dokumentácia projektu Nerozlej podľa SDLC

Poradie fáz zodpovedá štruktúre finálnej prezentácie a sekcie Project Outcomes. Kto má ktorú fázu na starosti, rozdelíme, keď bude program na aute odladený.

| Fáza | Čo tam patrí | Stav |
|---|---|---|
| 01 Business | problém, používateľ, hodnota, stakeholderi | hypotéza v [Nerozlej](moznost-nerozlej.md#cieľová-skupina-a-prínos) |
| 02 Top Level Architecture | systémový pohľad: príčinné väzby, spätné väzby, hranica systému | [diagram príčinných väzieb](moznost-nerozlej.md#systémový-pohľad) |
| 03 Solution Architecture | CyberPi, senzory, motory a ich prepojenie, menu a jazda | ☐ |
| 04 Analysis | požiadavky, rozhodnutia, riziká, rozpočet | [rozsah a riziká](moznost-nerozlej.md#rozsah), [rozhodnutia](stav-projektu.md#rozhodnutia) |
| 05 Design | nastavenia a ich rozsahy, priebeh jazdy, nádoba | [program na aute](moznost-nerozlej.md#program-na-aute); nádoba ☐ |
| 06 Implementation | program, STL nádoby, fotky | [program](../mbot2/README.md) napísaný, na aute neoverený; STL ☐ |
| 07 Testing & Verification | testy na PC, akceptačné testy N1–N6 | testy na PC prechádzajú; [N1–N6](moznost-nerozlej.md#akceptačné-testy) ☐ |
| 08 Operation | návod pre učiteľa, pracovný list, bezpečnosť | [ťahák do labu](../mbot2/tahak-lab.md); návod a pracovný list ☐ |
| 09 Change Management | čo sme zmenili oproti plánu a prečo | zoznam nižšie |

Diagramy kreslíme v Enterprise Architect, každý vo svojom balíku `ST0XX` v triednom EA modeli. Sem dávame ich exporty (PNG).

## Možnosti projektu

- [Nerozlej](moznost-nerozlej.md): robot-čašník na mBot2 vezie loptičku po čiare; **pracovný výber od 16. 11. 2026**, program je v [mbot2/](../mbot2/)
- odložené možnosti (verzia s ESP32 a Brzdná výzva) sú v [archíve](../archiv/README.md)

## Cesta projektu a prezentácia

- [Stav projektu](stav-projektu.md): čo platí, aké sú možnosti a čo sa robí ďalej
- [Cesta projektu](cesta-projektu.md): čo sme skúšali, čo nevyšlo a prečo sme to zmenili
- [Čo zachytávať počas práce](zachytavanie-prace.md): pomôcka pre tím a prepis do denníka aktivít
- [Podklady k finálnej prezentácii](prezentacia.md): biznisový obrázok, aktuálny stav, plán vs. dodané
- [Vzory z minulých rokov](vzory-projektov.md): CarCharm, Dog-Fit a čo nám oproti nim chýba
- [Požiadavky predmetu](poziadavky-predmetu.md): hodnotenie, výstupy, SDLC, 7Ds a EA model

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
| 16. 11. 2026 | pracujeme na Nerozlej s požičaným mBot2 namiesto vlastného auta s ESP32 | netreba kupovať diely; cvičiaci nemá námietky, formálne potvrdenie tímom chýba |
| 16. 11. 2026 | Nerozlej má jednu nádobu namiesto 2 až 3 hĺbok | jadrom sú nastavenia jazdy, obtiažnosť dávajú parametre a trasa |
| 16. 11. 2026 | verzia s ESP32 a Brzdná výzva presunuté do [archívu](../archiv/README.md) | v hlavných priečinkoch ostáva len to, čo patrí k Nerozlej |
