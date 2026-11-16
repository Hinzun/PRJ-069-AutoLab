# AutoLab (PRJ-069) – pokyny pre Claude Code

Tímový projekt predmetu **Systémové myslenie v IT a digitálna fabrikácia (SMVIT / STHDF)**, FIIT STU, 2026/2027. Tím: Branislav Bučko (ST021), Erik Dusík (ST022), Adrián Fáber (ST023), Samuel Roháč (ST032).

**Pôvodný návrh:** dve autíčka s 3D tlačeným podvozkom a ESP32, ovládané z mobilu cez webovú stránku, ktorú podáva samotné auto. Auto zabrzdí pred prekážkou aj pred autom idúcim vpredu a zastaví pri strate spojenia.

**Pracovný výber je [Nerozlej](docs/moznost-nerozlej.md) (16. 11. 2026):** robot mBot2 vezie loptičku v 3D tlačenej nádobe po čiare a hráč nastavuje rýchlosť, rozjazd, brzdenie a zatáčanie. Tím ho formálne nepotvrdil, ale pracujeme podľa neho. Verzia s ESP32 a Brzdná výzva sú odložené. Program je v [mbot2/](mbot2/) (MicroPython pre CyberPi), na aute sa zatiaľ nespúšťal. **Začni v [docs/stav-projektu.md](docs/stav-projektu.md)**, sú tam aktuálne rozhodnutia a ďalšie kroky.

## Cieľ tímu: prejsť (známka E/D)

- Drž **minimálny rozsah** z [docs/moznost-nerozlej.md](docs/moznost-nerozlej.md#rozsah). Najprv všetky *Must*, potom *Should*, voliteľné doplnky až nakoniec.
- Nenavrhuj ani nepridávaj funkcie nad rámec dohodnutého rozsahu bez súhlasu tímu. Pri výbere riešenia uprednostni to jednoduchšie.
- **Dôležitá je cesta:** predmet má princíp „The goal is the journey“ a 75 % známky ide za priebežnú prácu. Pokusy, zlyhania a rozhodnutia priebežne zapisuj do [docs/cesta-projektu.md](docs/cesta-projektu.md).

## Kde čo je

| Súbor | Obsah |
|---|---|
| [docs/navrh-zadania.md](docs/navrh-zadania.md) | čo predmet chce, rozsah a požiadavky, akceptačné testy, hardvér a zapojenie pinov, harmonogram, role, rozhodnutia tímu |
| [docs/specifikacia.md](docs/specifikacia.md) | **zdroj pravdy pre firmvér ESP32 a stránku (odložená verzia):** systémový pohľad, architektúra, režimy, bezpečnosť, JSON protokol, parametre, UI |
| [docs/README.md](docs/README.md) | mapa dokumentácie podľa SDLC fáz a kto ju má na starosti |
| [docs/testovaci-protokol.md](docs/testovaci-protokol.md) | akceptačné testy G1–G6 a tabuľka výsledkov |
| [docs/stav-projektu.md](docs/stav-projektu.md) | **aktuálny stav:** čo platí, možnosti, čo overiť, ďalšie kroky, rozhodnutia |
| [docs/cesta-projektu.md](docs/cesta-projektu.md) | priebežný záznam pokusov, zlyhaní a rozhodnutí |
| [docs/zachytavanie-prace.md](docs/zachytavanie-prace.md) | čo má tím zachytávať počas práce a ako to prepísať do denníka |
| [docs/prezentacia.md](docs/prezentacia.md) | kostra finálnej prezentácie: biznisový obrázok, aktuálny stav, plán vs. dodané |
| [docs/vzory-projektov.md](docs/vzory-projektov.md) | CarCharm a Dog-Fit ako vzor formy; čo je overené a čo chýba |
| [docs/moznost-nerozlej.md](docs/moznost-nerozlej.md) | **zdroj pravdy pre Nerozlej:** rozsah, nastavenia, správanie programu, akceptačné testy N1–N6 |
| [docs/moznost-brzdna-vyzva.md](docs/moznost-brzdna-vyzva.md) | odložená možnosť na mBot2 |
| [mbot2/](mbot2/) | program Nerozlej pre CyberPi (`nerozlej.py`), testy na PC, postup nahratia a prvej návštevy v labe |
| [firmware/](firmware/) | PlatformIO projekt pre ESP32 (Arduino C++), `data/index.html` je stránka |
| [hardware/](hardware/) | 3D model a STL podvozku, schéma zapojenia |

Pôvodné PDF od kolegu bol AI koncept s chybami. V repozitári nie je a nepoužíva sa. Platí `docs/specifikacia.md`.

## Pravidlá

- **Jazyk:** dokumentácia, komentáre aj commit správy po slovensky.
- **Commity:** nepridávaj žiadny podpis Claude ani AI (`Co-Authored-By`, „Generated with“). Autorom je člen tímu. Vypína to aj [.claude/settings.json](.claude/settings.json).
- **Git:** vetva `main` je vždy funkčná. Rozpracovaná práca patrí do vlastnej vetvy. Pred pushom `git pull`. Na `main` nikdy nerob force push, pracujú tu štyria ľudia.
- **Špecifikácia a kód spolu:** keď sa implementácia odchýli od `docs/specifikacia.md` (protokol, parametre, piny, správanie), uprav špecifikáciu v tom istom commite. Väčšiu zmenu oproti plánu zapíš aj do fázy 09 Change Management v `docs/README.md`.

### Program Nerozlej (mBot2)

- Bezpečnostné správanie sa nesmie odstrániť: po zapnutí auto stojí, zastaví pred prekážkou, pri strate čiary, tlačidlom B a po 60 s.
- Každý parameter sa pred jazdou obmedzí na rozsah z `PARAMETRE`.
- Pri zmene správania uprav v tom istom commite kapitolu Program na aute v `docs/moznost-nerozlej.md` a spusti `python -m unittest discover -s mbot2/test`.
- Na displeji len text bez diakritiky, najviac 20 znakov na riadok.

### Firmvér ESP32 (odložená verzia)

- Hlavná slučka nikdy neblokuje (žiadne `delay()`, `pulseIn` len s krátkym timeoutom), úlohy podľa `millis()`.
- Bezpečnostné správanie sa nesmie odstrániť ani obísť: po zapnutí STOP, STOP po 1 s bez správy zo stránky, brzdenie pred prekážkou pri jazde dopredu.
- Každý parameter zo stránky over voči rozsahu a pošli späť platné hodnoty.
- Piny ESP32 neznesú 5 V. ECHO senzora HC-SR04 ide cez delič, senzory čiary sa napájajú z 3,3 V. Zapojenie je v `docs/navrh-zadania.md`, kapitola 6.

## Čo sem nepatrí

Osobné výstupy každého člena (About Me, KNIFE, Project Summary, Pitch, Reflexia, denník aktivít) sú v jeho **osobnom repozitári** z triednej šablóny, nie tu. Diagramy v Enterprise Architect sú v triednom EA repozitári, sem patria len ich PNG exporty do `docs/`.
