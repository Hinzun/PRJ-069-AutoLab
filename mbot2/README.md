# Program Nerozlej pre mBot2

Program pre CyberPi v MicroPythone. Správanie opisuje [moznost-nerozlej.md](../docs/moznost-nerozlej.md#program-na-aute).

> **Stav (16. 11. 2026):** logika prešla testami na PC. Na skutočnom mBot2 sa **zatiaľ nespúšťal**. Názvy funkcií sme prevzali z príkladov kódu pre CyberPi (pozri Zdroje), nie z oficiálnej dokumentácie, lebo tá sa nám nenačítala.

| Súbor | Čo robí |
|---|---|
| `nerozlej.py` | celý program, nahráva sa do auta |
| `test/test_nerozlej.py` | testy logiky na PC so simuláciou auta |

## Prečo MicroPython a nie bloky

- Program je textový súbor, takže v Gite je vidieť každú zmenu a dá sa testovať na PC.
- Nahrávanie MicroPythonu neprepíše firmvér CyberPi, auto sa dá potom ďalej používať s blokmi.
- Bloky v mBlocku by sa ťažko verzovali aj kontrolovali.

## Nahratie do auta

Treba notebook s [mBlockom 5](https://mblock.cc/pages/downloads) a kábel USB-C.

1. Zapni auto a pripoj CyberPi káblom k notebooku.
2. V mBlocku pridaj zariadenie **CyberPi** a pripoj ho (Connect).
3. Prepni na režim **Upload** a v editore kódu prepni z blokov na **Python**.
4. Vlož celý obsah `nerozlej.py` a klikni na **Upload**.
5. Ak hlási chybu pri `import mbot2`, pridaj v rozšíreniach zariadenia **mBot2 Shield** a nahraj znova.

Ako presne sa v mBlocku volajú tieto tlačidlá, overíme pri prvej návšteve a návod opravíme.

**Pozor:** nahratím nahradíš program, ktorý v aute práve je. Pri požičaných autách sa najprv spýtaj v SmartLabe.

## Ovládanie

| Ovládač | Čo robí |
|---|---|
| joystick hore a dole | výber riadku v menu |
| joystick doľava a doprava | zmena hodnoty |
| A | spustí jazdu, otvorí Test senzorov alebo Vysledky |
| B | zastaví jazdu, vráti sa do menu, po jazde znamená „loptička spadla“ |

## Prvá návšteva v labe (asi 30 minút)

Cieľ je overiť, čo sme na PC overiť nevedeli. Výsledky zapíš do [cesty projektu](../docs/cesta-projektu.md) a odfoť to.

| # | Čo spraviť | Čo má vyjsť | Keď nie |
|---|---|---|---|
| 1 | nahrať program | na displeji je menu NEROZLEJ | odfotiť chybu a poslať ju Erikovi |
| 2 | joystick hore, dole, doľava a doprava | kurzor a hodnoty sa menia o jeden krok | zapísať, ktoré tlačidlo nereaguje |
| 3 | Test senzorov: posúvať auto ponad čiaru z izolačky | „Ciara“ je zhruba 0 nad čiarou, vľavo a vpravo má opačné znamienko, „Stav“ je mimo čiary 0 | zapísať hodnoty |
| 4 | Test senzorov: ruka pred autom vo vzdialenosti 10, 20 a 50 cm | „Vzdial“ sedí s metrom | zapísať hodnoty |
| 5 | Test senzorov: A, auto ide 1 s dopredu | ide **dopredu** a rovno | ak ide dozadu alebo sa točí, upraviť funkciu `jazdi` |
| 6 | jazda Trasa Rovno k stene, rýchlosť 30 % | zastaví pred stenou bez dotyku | zväčšiť `STOP_CM` |
| 7 | jazda Trasa Ciara po rovnej čiare | drží sa čiary | ak uteká od čiary, nastaviť `SMER_CIARY = -1` |
| 8 | dve jazdy s loptičkou na kartónovom podnose: pokojná (rýchlosť 30, rozjazd 2, brzdenie 30) a trhaná (80, 0, 0) | trhaná má vyššie „Otrasy“ a „Spicka“ | ak sa nelíšia, skóre bude len z času a pádu loptičky |
| 9 | najnižšia rýchlosť, pri ktorej sa auto ešte pohne | okolo 15 % | upraviť `MIN_VYKON` |

Konštanty `SMER_CIARY`, `STOP_CM` a `MIN_VYKON` sú na začiatku `nerozlej.py`.

## Testy na PC

Z koreňa repozitára, treba len Python 3:

```
python -m unittest discover -s mbot2/test -v
```

Testy nahradia CyberPi simuláciou, v ktorej auto ide rovno k stene. Overujú rozsahy parametrov, rozjazd, brzdenie, zastavenie pred stenou, zastavenie pri strate čiary a tlačidlom B. Či auto reálne drží čiaru, testy neoveria.

## Zdroje

- príklady MicroPythonu pre CyberPi a mBot2: [PerfecXX/mBot2](https://github.com/PerfecXX/mBot2) (`drive_power`, `ultrasonic2.get`, `quad_rgb_sensor`, `show_label`, `controller.is_press`, `get_acc`, `timer`)
- `get_offset_track` vracia -100 až 100, záporné číslo znamená, že senzor je vľavo od čiary: [Makeblock Education](https://education.makeblock.com/?p=63819)
