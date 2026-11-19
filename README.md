# PRJ-069 AutoLab

Tímový projekt predmetu **Systémové myslenie v IT a digitálna fabrikácia (SMVIT / STHDF)**, FIIT STU, 2026/2027.
ID projektu: `PRJ_069_ST21_ST22_ST23_ST32`.

> **Pracovný výber: Nerozlej** (16. 11. 2026). Začni v [stave projektu](docs/stav-projektu.md).

**Nerozlej:** robot mBot2 ako čašník vezie loptičku v 3D tlačenej nádobe po čiare k „stolu“. Hráč na aute nastaví rýchlosť, rozjazd, brzdenie a zatáčanie a hľadá kompromis: rýchla jazda skracuje čas, ale loptička môže vyletieť. Auto samo zastaví pred cieľom, pri strate čiary aj na tlačidlo. Používame požičané mBoty zo SmartLabu, takže netreba nič kupovať.

## Tím

Úlohy si rozdelíme, keď bude program na aute odladený.

| ST ID | Meno | Osobný repozitár |
|---|---|---|
| ST021 | Branislav Bučko | *(doplniť odkaz)* |
| ST022 | Erik Dusík | [ST-022-ErikDusik](https://github.com/Hinzun/ST-022-ErikDusik) |
| ST023 | Adrián Fáber | *(doplniť odkaz)* |
| ST032 | Samuel Roháč | *(doplniť odkaz)* |

## Štruktúra

```
PRJ-069-AutoLab/
├── mbot2/    # program Nerozlej pre CyberPi (MicroPython), testy na PC, ťahák do labu
├── docs/     # stav, cesta projektu, SDLC dokumentácia, podklady k prezentácii
└── archiv/   # odložené možnosti: verzia s ESP32 a Brzdná výzva
```

- [Stav projektu](docs/stav-projektu.md): čo platí a čo sa robí ďalej
- [12-týždňová Roadmapa a Cesta projektu](docs/cesta-a-roadmapa-12-tyzdnov.md): naša 12-týždňová cesta, zlyhanie 3D tlače autodielov, pivot a scenár prezentácie
- [Nerozlej](docs/moznost-nerozlej.md): rozsah, nastavenia, priebeh jazdy, akceptačné testy
- [Program pre mBot2](mbot2/README.md) a [ťahák do labu](mbot2/tahak-lab.md)
- [Cesta projektu](docs/cesta-projektu.md): čo sme skúšali, čo nevyšlo a prečo sme to zmenili
- [Dokumentácia podľa SDLC](docs/README.md)
- [Požiadavky predmetu](docs/poziadavky-predmetu.md)
- [Archív](archiv/README.md)

## Ako pracujeme

- Vetva `main` je vždy funkčná. Rozpracované veci patria do vlastnej vetvy, napr. `nerozlej`.
- Malé commity s popisom, čo sa zmenilo.
- Raz týždenne krátke stretnutie: čo je hotové, čo ďalej, čo blokuje.
- Každý si zapisuje svoju prácu do **denníka aktivít v osobnom repozitári** (hodnotí sa).
- Kto používa Claude Code: pokyny pre neho sú v [CLAUDE.md](CLAUDE.md) a načíta ich sám. Podpis Claude v commitoch je vypnutý v `.claude/settings.json`.

## Osobné výstupy

Každý člen má vlastný repozitár so 7 povinnými sekciami (About Me, KNIFE, Project Summary, Project Outcomes, Pitch, Finálna prezentácia, Reflexia). Tento repozitár je spoločný zdroj, na ktorý sa z osobných repozitárov odkazuje.
