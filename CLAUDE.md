# AutoLab (PRJ-069) – pokyny pre Claude Code

Tímový projekt predmetu **Systémové myslenie v IT a digitálna fabrikácia (SMVIT / STHDF)**, FIIT STU, 2026/2027. Tím: Branislav Bučko (ST021), Erik Dusík (ST022), Adrián Fáber (ST023), Samuel Roháč (ST032).

Dve autíčka s 3D tlačeným podvozkom a ESP32, ovládané z mobilu cez webovú stránku, ktorú podáva samotné auto. Auto zabrzdí pred prekážkou aj pred autom idúcim vpredu a zastaví pri strate spojenia.

## Cieľ tímu: prejsť (známka E/D)

- Drž **minimálny rozsah** z [docs/navrh-zadania.md](docs/navrh-zadania.md), kapitola 5. Najprv všetky *Must*, potom *Should* (sledovanie čiary len ak zostane čas).
- Nenavrhuj ani nepridávaj funkcie nad rámec dohodnutého rozsahu bez súhlasu tímu. Pri výbere riešenia uprednostni to jednoduchšie.

## Kde čo je

| Súbor | Obsah |
|---|---|
| [docs/navrh-zadania.md](docs/navrh-zadania.md) | čo predmet chce, rozsah a požiadavky, akceptačné testy, hardvér a zapojenie pinov, harmonogram, role, rozhodnutia tímu |
| [docs/specifikacia.md](docs/specifikacia.md) | **zdroj pravdy pre firmvér a stránku:** systémový pohľad, architektúra, režimy, bezpečnosť, JSON protokol, parametre, UI |
| [docs/README.md](docs/README.md) | mapa dokumentácie podľa SDLC fáz a kto ju má na starosti |
| [docs/testovaci-protokol.md](docs/testovaci-protokol.md) | akceptačné testy G1–G6 a tabuľka výsledkov |
| [firmware/](firmware/) | PlatformIO projekt pre ESP32 (Arduino C++), `data/index.html` je stránka |
| [hardware/](hardware/) | 3D model a STL podvozku, schéma zapojenia |

Pôvodné PDF od kolegu bol AI koncept s chybami. V repozitári nie je a nepoužíva sa. Platí `docs/specifikacia.md`.

## Pravidlá

- **Jazyk:** dokumentácia, komentáre aj commit správy po slovensky.
- **Commity:** nepridávaj žiadny podpis Claude ani AI (`Co-Authored-By`, „Generated with“). Autorom je člen tímu. Vypína to aj [.claude/settings.json](.claude/settings.json).
- **Git:** vetva `main` je vždy funkčná. Rozpracovaná práca patrí do vlastnej vetvy. Pred pushom `git pull`. Na `main` nikdy nerob force push, pracujú tu štyria ľudia.
- **Špecifikácia a kód spolu:** keď sa implementácia odchýli od `docs/specifikacia.md` (protokol, parametre, piny, správanie), uprav špecifikáciu v tom istom commite. Väčšiu zmenu oproti plánu zapíš aj do fázy 09 Change Management v `docs/README.md`.

### Firmvér

- Hlavná slučka nikdy neblokuje (žiadne `delay()`, `pulseIn` len s krátkym timeoutom), úlohy podľa `millis()`.
- Bezpečnostné správanie sa nesmie odstrániť ani obísť: po zapnutí STOP, STOP po 1 s bez správy zo stránky, brzdenie pred prekážkou pri jazde dopredu.
- Každý parameter zo stránky over voči rozsahu a pošli späť platné hodnoty.
- Piny ESP32 neznesú 5 V. Senzory napájaj z 3,3 V, zapojenie je v `docs/navrh-zadania.md`, kapitola 6.

## Čo sem nepatrí

Osobné výstupy každého člena (About Me, KNIFE, Project Summary, Pitch, Reflexia, denník aktivít) sú v jeho **osobnom repozitári** z triednej šablóny, nie tu. Diagramy v Enterprise Architect sú v triednom EA repozitári, sem patria len ich PNG exporty do `docs/`.
