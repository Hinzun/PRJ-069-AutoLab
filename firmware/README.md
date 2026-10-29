# Firmvér

Sem príde PlatformIO projekt pre ESP32 (Arduino C++). Návrh je v [návrhu zadania](../docs/navrh-zadania.md), kapitoly 4.2, 5 a 6.

Plánované súbory:

| Súbor | Čo robí | Zodpovedá |
|---|---|---|
| `src/main.cpp` | `setup()`, `loop()`, prepínanie režimov | Adrián Fáber |
| `src/motors.cpp` | rýchlosť a smer motorov cez DRV8833, brzdenie | Adrián Fáber |
| `src/sensors.cpp` | senzor vzdialenosti HC-SR04P (neblokujúco) | Adrián Fáber |
| `src/web.cpp` | Wi-Fi AP, webserver, WebSocket, JSON správy | Erik Dusík |
| `src/params.cpp` | parametre, rozsahy, uloženie | Erik Dusík |
| `data/index.html` | webová stránka v aute | Samuel Roháč |
