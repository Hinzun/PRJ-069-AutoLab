# AutoLab (PRJ-069) – pokyny pre Claude Code

Tímový projekt predmetu **Systémové myslenie v IT a digitálna fabrikácia (SMVIT / STHDF)**, FIIT STU, 2026/2027. Tím: Branislav Bučko (ST021), Erik Dusík (ST022), Adrián Fáber (ST023), Samuel Roháč (ST032).

**Pracovný výber je [Nerozlej](docs/moznost-nerozlej.md) (16. 11. 2026):** robot mBot2 vezie loptičku v 3D tlačenej nádobe po čiare a hráč nastavuje rýchlosť, rozjazd, brzdenie a zatáčanie. Tím ho formálne nepotvrdil, ale pracujeme podľa neho. Verzia s ESP32 a Brzdná výzva sú odložené v [archiv/](archiv/). Program je v [mbot2/](mbot2/) (MicroPython pre CyberPi), na aute sa zatiaľ nespúšťal. **Začni v [docs/stav-projektu.md](docs/stav-projektu.md)**, sú tam aktuálne rozhodnutia a ďalšie kroky.

## Cieľ tímu: prejsť (známka E/D)

- Drž **minimálny rozsah** z [docs/moznost-nerozlej.md](docs/moznost-nerozlej.md#rozsah). Najprv všetky *Must*, potom *Should*, voliteľné doplnky až nakoniec.
- Nenavrhuj ani nepridávaj funkcie nad rámec dohodnutého rozsahu bez súhlasu tímu. Pri výbere riešenia uprednostni to jednoduchšie.
- **Dôležitá je cesta:** predmet má princíp „The goal is the journey“ a 75 % známky ide za priebežnú prácu. Pokusy, zlyhania a rozhodnutia priebežne zapisuj do [docs/cesta-projektu.md](docs/cesta-projektu.md).

## Kde čo je

| Súbor | Obsah |
|---|---|
| [docs/stav-projektu.md](docs/stav-projektu.md) | **aktuálny stav:** čo platí, čo overiť, ďalšie kroky, rozhodnutia |
| [docs/moznost-nerozlej.md](docs/moznost-nerozlej.md) | **zdroj pravdy pre Nerozlej:** rozsah, nastavenia, správanie programu, akceptačné testy N1–N6 |
| [mbot2/](mbot2/) | program Nerozlej pre CyberPi (`nerozlej.py`), testy na PC, [ťahák do labu](mbot2/tahak-lab.md) |
| [docs/README.md](docs/README.md) | mapa dokumentácie podľa SDLC fáz a zoznam zmien oproti plánu |
| [docs/poziadavky-predmetu.md](docs/poziadavky-predmetu.md) | čo predmet chce (hodnotenie, výstupy, SDLC, 7Ds, EA) a projekty z minulých rokov |
| [docs/cesta-projektu.md](docs/cesta-projektu.md) | priebežný záznam pokusov, zlyhaní a rozhodnutí |
| [docs/zachytavanie-prace.md](docs/zachytavanie-prace.md) | čo má tím zachytávať počas práce a ako to prepísať do denníka |
| [docs/prezentacia.md](docs/prezentacia.md) | kostra finálnej prezentácie: biznisový obrázok, aktuálny stav, plán vs. dodané |
| [docs/vzory-projektov.md](docs/vzory-projektov.md) | CarCharm a Dog-Fit ako vzor formy; čo je overené a čo chýba |
| [archiv/](archiv/) | odložené možnosti: verzia s ESP32 (návrh zadania, špecifikácia, firmvér, hardvér, testy G1–G6) a Brzdná výzva; neupravuj ich, pokiaľ sa k nim tím nevráti |

## Pravidlá

- **Jazyk:** dokumentácia, komentáre aj commit správy po slovensky.
- **Commity:** nepridávaj žiadny podpis Claude ani AI (`Co-Authored-By`, „Generated with“). Autorom je člen tímu. Vypína to aj [.claude/settings.json](.claude/settings.json).
- **Git:** vetva `main` je vždy funkčná. Rozpracovaná práca patrí do vlastnej vetvy. Pred pushom `git pull`. Na `main` nikdy nerob force push, pracujú tu štyria ľudia.
- **Dokumentácia a kód spolu:** keď sa program odchýli od `docs/moznost-nerozlej.md` (parametre, rozsahy, správanie), uprav dokument v tom istom commite. Väčšiu zmenu oproti plánu zapíš aj do zoznamu zmien v `docs/README.md` (fáza 09 Change Management).

### Program Nerozlej (mBot2)

- Bezpečnostné správanie sa nesmie odstrániť: po zapnutí auto stojí, zastaví pred prekážkou, pri strate čiary, tlačidlom B a po 60 s.
- Každý parameter sa pred jazdou obmedzí na rozsah z `PARAMETRE`.
- Pri zmene správania uprav v tom istom commite kapitolu Program na aute v `docs/moznost-nerozlej.md` a spusti `python -m unittest discover -s mbot2/test`.
- Na displeji len text bez diakritiky, najviac 20 znakov na riadok.

Pravidlá pre odložený firmvér ESP32 sú v [archiv/esp32/firmware/README.md](archiv/esp32/firmware/README.md) a [archiv/esp32/specifikacia.md](archiv/esp32/specifikacia.md).

## Čo sem nepatrí

Osobné výstupy každého člena (About Me, KNIFE, Project Summary, Pitch, Reflexia, denník aktivít) sú v jeho **osobnom repozitári** z triednej šablóny, nie tu. Diagramy v Enterprise Architect sú v triednom EA repozitári, sem patria len ich PNG exporty do `docs/`.
