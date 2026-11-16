# Cesta projektu

Predmet má medzi základnými princípmi „The goal is the journey“ a 75 % známky ide za priebežnú prácu. Sem preto priebežne zapisujeme, čo sme skúšali, čo nevyšlo, čo sme zmenili a prečo.

## Pravidlá

- Zapisuj hneď, ideálne v ten istý deň. Pár viet stačí.
- Zapíš aj to, čo nevyšlo.
- Ku každému záznamu pridaj dôkaz: commit, fotku, video alebo dokument.
- Nové záznamy pridávaj na koniec tabuľky.
- Čo robíš ty osobne, zapíš aj do svojho denníka aktivít. Pomôcka je v [zachytavanie-prace.md](zachytavanie-prace.md).

## Šablóna záznamu

| Dátum | Autor | Čo sme skúšali | Výsledok | Rozhodnutie a prečo | Dôkaz |
|---|---|---|---|---|---|
| | | | | | |

## Záznamy

| Dátum | Autor | Čo sme skúšali | Výsledok | Rozhodnutie a prečo | Dôkaz |
|---|---|---|---|---|---|
| 29. 10. 2026 | tím | ujasnenie rozsahu projektu | dohodnuté rozhodnutia tímu | sledovanie čiary len ak zostane čas; autá za sebou do seba nenarazia, a to bez komunikácie; názov AutoLab | [návrh zadania, kap. 10](navrh-zadania.md#10-rozhodnutia-tímu-29-10-2026) |
| 29. 10. 2026 | Erik Dusík | posúdenie AI špecifikácie od kolegu | našli sme hardvérové aj softvérové chyby a nereálny harmonogram | vychádzame z opravenej špecifikácie, nie z pôvodného PDF | [návrh zadania, kap. 4](navrh-zadania.md#4-posúdenie-ai-špecifikácie), [špecifikácia](specifikacia.md) |
| 5. 11. 2026 | Erik Dusík | zníženie ceny a rizika hardvéru | návrh na powerbanku a DRV8833, odhad ≈ 20–23 € na auto | zjednodušiť napájanie, lebo odpadá nabíjačka a riziko Li-ion článkov | [návrh zadania, kap. 6](navrh-zadania.md#6-hardvér-zjednodušený-a-lacnejší), [nákupný zoznam](../hardware/nakupny-zoznam.md) |
| 5. 11. 2026 | Erik Dusík | firmvér a stránka pre ESP32 | napísané a otestované na PC, na ESP32 ešte nebežali | pokračovanie závisí od výberu projektu | [firmvér](../firmware/README.md), commit `1668629` |
| 5. 11. 2026 | Erik Dusík | otázka, či treba kupovať vlastné diely | cvičiaci odporučil použiť požičané mBot2 a zbytočne neminúť peniaze | nákup dielov je pozastavený, kým sa tím nerozhodne | ústne od cvičiaceho; [návrh zadania, kap. 7](navrh-zadania.md#7-harmonogram-od-teraz) |
| 5. 11. 2026 | Erik Dusík | hľadanie nápadu pre mBot2 | vznikli možnosti Brzdná výzva a Nerozlej, na aute zatiaľ neskúšané | tím ani cvičiaci ich zatiaľ neschválili | [Brzdná výzva](moznost-brzdna-vyzva.md), [Nerozlej](moznost-nerozlej.md) |
| 5. 11. 2026 | Erik Dusík | iné nápady: jedno auto s režimom „nasleduj“, komunikácia medzi autami cez ESP-NOW, parkovací asistent, sledovanie zvuku, Kreslič, Sumo liga, sprievodca s kamerou | zvážené, nikto ich neskúšal | zatiaľ odložené: sledovanie zvuku je zložité a na demo nespoľahlivé, ostatné ostali mimo užšieho výberu | záznam z diskusie o nápadoch |
| 16. 11. 2026 | Erik Dusík | výber, na čom pracovať ďalej | tím sa formálne nerozhodol, cvičiaci proti Nerozlej nič nemá | pracujeme na Nerozlej, aby sa projekt pohol; Brzdná výzva a ESP32 sú odložené | [stav projektu](stav-projektu.md#rozhodnutia), [Nerozlej](moznost-nerozlej.md) |
| 16. 11. 2026 | Erik Dusík | zjednodušenie rozsahu Nerozlej | jedna nádoba namiesto 2 až 3 hĺbok, jadrom sú nastavenia jazdy (rýchlosť, rozjazd, brzdenie, zatáčanie) | menej tlače a menej pokusov, obtiažnosť dávajú parametre a trasa | [Nerozlej, Rozsah](moznost-nerozlej.md#rozsah) |
| 16. 11. 2026 | Erik Dusík | program pre mBot2 v MicroPythone a jeho testy na PC so simuláciou auta | 20 testov prešlo; oficiálna dokumentácia API sa nenačítala, názvy funkcií sú z príkladov kódu | MicroPython namiesto blokov, lebo sa dá verzovať a testovať bez auta; v programe je test senzorov na rýchle overenie v labe | [mbot2/](../mbot2/README.md) |
