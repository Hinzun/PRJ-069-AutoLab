# Stav projektu

> **Posledná aktualizácia:** 16. 11. 2026. Tento dokument je prvé miesto, kde zistíš, čo platí a čo sa robí ďalej. Po každom rozhodnutí ho aktualizuj.

## Čo práve platí

- **Pracujeme na možnosti [Nerozlej](moznost-nerozlej.md).** Tím ju formálne nepotvrdil, ale pre posun projektu podľa nej pracujeme a cvičiaci proti tomu nič nemá. Brzdná výzva a verzia s ESP32 sú odložené.
- **Program pre auto je napísaný** v [mbot2/](../mbot2/) a prešiel testami na PC. Na aute sa zatiaľ nespúšťal.
- **Autá si domov nepožičiame.** Do SmartLabu chodíme občas a program skúšame tam, preto má každá návšteva pripravený postup.
- **Nákup dielov nie je potrebný.** Tlačiť v SmartLabe smieme, malá nádoba vyjde na pár centov.
- **Finálna prezentácia** bude v januári 2027, presný dátum zatiaľ nepoznáme. Podľa cvičiaceho zrejme nebude v PowerPointe, [podklady](prezentacia.md) sú pripravené ako kostra.

## Možnosti

| Možnosť | Auto | Stav |
|---|---|---|
| [Nerozlej](moznost-nerozlej.md) | požičaný mBot2 | **pracovný výber**, program napísaný, na aute neoverený |
| [AutoLab s ESP32](navrh-zadania.md) | vlastné, treba kúpiť diely | odložené; firmvér a stránka sú napísané, na hardvéri neoverené |
| [Brzdná výzva](moznost-brzdna-vyzva.md) | požičaný mBot2 | odložené |

### Prečo Nerozlej

- **Oproti ESP32:** použijeme požičané mBot2, takže netreba kupovať diely ani zapájať hardvér.
- **Oproti Brzdnej výzve:** výsledok je hneď vidieť, lebo loptička sa buď udrží, alebo spadne.
- **Pre systémové myslenie:** hráč hľadá kompromis medzi rýchlosťou a plynulosťou, čo sa dá ukázať na diagrame príčinných väzieb aj na nameraných jazdách.

## Čo overiť na autách

Zoznamy obsahu balenia sa v obchodoch líšia, preto to treba skontrolovať priamo na autách v SmartLabe.

| Čo | Stav |
|---|---|
| počet áut | v SmartLabe ich je približne 20 (Erik ich videl osobne) |
| požičanie domov | nie, chodíme do labu občas |
| smieme nahrať vlastný program do áut | TODO |
| notebook s mBlockom 5 a kábel USB-C | TODO |
| senzor čiary (Quad RGB) a ultrazvukový senzor na aute | TODO |
| akcelerometer, displej a joystick na CyberPi | TODO |
| dá sa na auto pripevniť vlastný diel bez nákupu skrutiek | TODO |
| tlač v SmartLabe | smieme, malý diel vyjde na pár centov |
| loptička a izolačná páska z domu alebo z laboratória | TODO |

## Ďalšie kroky

| # | Krok | Kto | Stav |
|---|---|---|---|
| 1 | napísať program pre auto a testy na PC | Erik s Claude | hotové 16. 11. 2026 |
| 2 | prvá návšteva v labe podľa [postupu](../mbot2/README.md#prvá-návšteva-v-labe-asi-30-minút), s kartónovým podnosom | Erik | TODO |
| 3 | opraviť program podľa výsledkov návštevy | Erik s Claude | čaká na krok 2 |
| 4 | navrhnúť a vytlačiť nádobu s držiakom | TODO | čaká na krok 2 (rozmery a miesto na aute) |
| 5 | akceptačné testy N1 až N6 z [Nerozlej](moznost-nerozlej.md#akceptačné-testy) | TODO | TODO |
| 6 | návod a pracovný list pre učiteľa | TODO | TODO |
| 7 | rozdeliť úlohy a témy KNIFE, upraviť Project Summary | tím | po kroku 3 |
| 8 | podklady k [prezentácii](prezentacia.md), fotky a video | tím | TODO |

## Rozhodnutia

Súvisiace zmeny zapíš aj do [cesty projektu](cesta-projektu.md).

| Dátum | Rozhodnutie | Kto | Prečo |
|---|---|---|---|
| 16. 11. 2026 | pracujeme na Nerozlej, ostatné možnosti sú odložené | Erik, cvičiaci nemá námietky | netreba kupovať diely a výsledok je hneď vidieť; formálne potvrdenie tímom ešte chýba |
| 16. 11. 2026 | program v MicroPythone, nie v blokoch | Erik | textový súbor sa dá verzovať a testovať na PC, nahratie neprepíše firmvér CyberPi |
| 16. 11. 2026 | jedna nádoba namiesto 2 až 3 hĺbok | Erik | jadrom projektu sú nastavenia jazdy, obtiažnosť dávajú parametre a trasa |
| 16. 11. 2026 | doplnky len po splnení Must | Erik | je 10. týždeň, prednosť má funkčná hlavná myšlienka |
