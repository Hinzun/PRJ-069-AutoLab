# PRJ-069 AutoLab

Tímový projekt predmetu **Systémové myslenie v IT a digitálna fabrikácia (SMVIT / STHDF)**, FIIT STU, 2026/2027.
ID projektu: `PRJ_069_ST21_ST22_ST23_ST32`.

Dve malé autíčka s 3D tlačeným podvozkom a ESP32. Každé auto vytvorí vlastnú Wi-Fi sieť a v mobile zobrazí webovú stránku. Cez ňu ho používateľ riadi joystickom a za jazdy mení jeho parametre. Auto samo zastaví pred prekážkou, pred autom idúcim pred ním aj pri strate spojenia.

## Tím

Rozdelenie rolí je predbežné.

| ST ID | Meno | Rola | Osobný repozitár |
|---|---|---|---|
| ST021 | Branislav Bučko | hardvér a podvozok | *(doplniť odkaz)* |
| ST022 | Erik Dusík | firmvér – komunikácia (Wi-Fi, WebSocket, parametre) | [ST-022-ErikDusik](https://github.com/Hinzun/ST-022-ErikDusik) |
| ST023 | Adrián Fáber | firmvér – riadenie (motory, senzor, zastavovanie) | *(doplniť odkaz)* |
| ST032 | Samuel Roháč | webová stránka a vedenie projektu | *(doplniť odkaz)* |

## Štruktúra

```
PRJ-069-AutoLab/
├── firmware/   # PlatformIO projekt pre ESP32: src/*.cpp, data/index.html
├── hardware/   # 3D model a STL podvozku, schéma zapojenia, zoznam dielov
└── docs/       # návrh zadania, SDLC dokumentácia, protokol testov, fotky
```

- [Návrh zadania](docs/navrh-zadania.md): rozsah, požiadavky, hardvér, harmonogram, rozdelenie práce
- [Dokumentácia podľa SDLC](docs/README.md)
- [Protokol testov](docs/testovaci-protokol.md)

## Ako pracujeme

- Vetva `main` je vždy funkčná. Rozpracované veci patria do vlastnej vetvy, napr. `firmware-web`.
- Malé commity s popisom, čo sa zmenilo.
- Raz týždenne krátke stretnutie: čo je hotové, čo ďalej, čo blokuje.
- Každý si zapisuje svoju prácu do **denníka aktivít v osobnom repozitári** (hodnotí sa).

## Osobné výstupy

Každý člen má vlastný repozitár so 7 povinnými sekciami (About Me, KNIFE, Project Summary, Project Outcomes, Pitch, Finálna prezentácia, Reflexia). Tento repozitár je spoločný zdroj, na ktorý sa z osobných repozitárov odkazuje.
