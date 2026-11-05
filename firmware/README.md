# Firmvér

PlatformIO projekt pre ESP32 (Arduino C++). Správanie opisuje [špecifikácia](../docs/specifikacia.md).

> **Stav:** kód sa skompiluje pre obe autá a logika aj stránka prešli testami na PC. Na skutočnom ESP32, motoroch a senzore zatiaľ **neboli vyskúšané**.

| Súbor | Čo robí |
|---|---|
| `src/main.cpp` | `setup()`, `loop()`, úlohy podľa `millis()` |
| `src/config.h` | piny a periódy |
| `src/control.cpp` | režimy, bezpečnosť, prepočet joysticku na motory |
| `src/params.cpp` | parametre a ich rozsahy |
| `src/protocol.cpp` | JSON správy so stránkou |
| `src/motors.cpp` | motory cez DRV8833, brzdenie |
| `src/sensors.cpp` | senzor vzdialenosti (neblokujúco, cez prerušenie) |
| `src/web.cpp` | Wi-Fi AP, webserver, WebSocket |
| `data/index.html` | webová stránka v aute |
| `test/test_logic/` | testy logiky na PC |

`control`, `params` a `protocol` nezávisia od Arduina, preto sa dajú testovať bez dosky.

## Nahratie do auta

Treba [PlatformIO](https://platformio.org/install) (rozšírenie do VS Code alebo `pip install platformio`). V priečinku `firmware/`:

```
pio run -e auto1 -t upload      # firmvér, pre druhé auto -e auto2
pio run -e auto1 -t uploadfs    # webová stránka
pio device monitor              # výpisy z auta
```

Pri nahrávaní nech je powerbanka odpojená. Ak sa doska nenájde, na Windows môže chýbať ovládač USB prevodníka (CP210x alebo CH340 podľa dosky).

## Prvé spustenie

1. Pripoj mobil na Wi-Fi `AutoLab-1` (alebo `AutoLab-2`), sieť je bez hesla. Ak mobil hlási „bez internetu“, zvoľ, že chceš ostať pripojený, a **vypni mobilné dáta**.
2. Otvor `http://192.168.4.1`.
3. Zapni režim MANUAL. Auto po zapnutí a po každom výpadku spojenia stojí v STOP.
4. Ak sa koleso točí opačne, prehoď jeho dva vodiče na DRV8833.

Bez pripojeného senzora stránka hlási, že senzor neodpovedá, a jazda dopredu nie je blokovaná.

## Testy na PC

```
pio test -e native
```

Treba g++ v systémovej ceste. Nie je to potrebné na nahratie do auta.
