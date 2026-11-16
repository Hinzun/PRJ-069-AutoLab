# Program Nerozlej pre mBot2

Program pre CyberPi v MicroPythone. Správanie opisuje [moznost-nerozlej.md](../docs/moznost-nerozlej.md#program-na-aute).

> **Stav (16. 11. 2026):** logika prešla testami na PC. Na skutočnom mBot2 sa **zatiaľ nespúšťal**. Názvy funkcií sme prevzali z príkladov kódu pre CyberPi (pozri Zdroje), nie z oficiálnej dokumentácie, lebo tá sa nám nenačítala.

| Súbor | Čo robí |
|---|---|
| `nerozlej.py` | celý program, nahráva sa do auta |
| `test/test_nerozlej.py` | testy logiky na PC so simuláciou auta |
| `tahak-lab.md` | postup na nahratie programu a prvý test v labe |

## Prečo MicroPython a nie bloky

- Program je textový súbor, takže v Gite je vidieť každú zmenu a dá sa testovať na PC.
- Nahrávanie MicroPythonu neprepíše firmvér CyberPi, auto sa dá potom ďalej používať s blokmi.
- Bloky v mBlocku by sa ťažko verzovali aj kontrolovali.

## Nahratie a prvý test v labe

Postup krok za krokom je v [ťaháku do labu](tahak-lab.md). Program sa do mBlocku 5 vkladá taký, aký je, nič sa nekonvertuje.

Nahratím sa nahradí program, ktorý v aute práve je. Pri autách zo SmartLabu to nevadí.

Ak test ukáže problém, najprv sa ladia konštanty na začiatku `nerozlej.py`:

| Konštanta | Kedy ju zmeniť |
|---|---|
| `SMER_CIARY` | auto pri sledovaní čiary uteká od čiary: zmeniť na -1 |
| `STOP_CM` | auto sa dotkne prekážky: zväčšiť |
| `MIN_VYKON` | auto sa pri malom výkone nepohne: nastaviť podľa testu 10 v ťaháku |
| funkcia `jazdi` | auto ide pri „dopredu“ dozadu alebo sa točí: otočiť znamienka |

## Testy na PC

Z koreňa repozitára, treba len Python 3:

```
python -m unittest discover -s mbot2/test -v
```

Testy nahradia CyberPi simuláciou, v ktorej auto ide rovno k stene. Overujú rozsahy parametrov, rozjazd, brzdenie, zastavenie pred stenou, zastavenie pri strate čiary a tlačidlom B. Či auto reálne drží čiaru, testy neoveria.

## Zdroje

- príklady MicroPythonu pre CyberPi a mBot2: [PerfecXX/mBot2](https://github.com/PerfecXX/mBot2) (`drive_power`, `ultrasonic2.get`, `quad_rgb_sensor`, `show_label`, `controller.is_press`, `get_acc`, `timer`)
- `get_offset_track` vracia -100 až 100, záporné číslo znamená, že senzor je vľavo od čiary: [Makeblock Education](https://education.makeblock.com/?p=63819)
