# Nákupný zoznam na 2 autá

> **Nákup je pozastavený, zatiaľ nič neobjednávajte.** Tento zoznam platí iba pre pôvodnú verziu s ESP32. Pozri [stav projektu](../docs/stav-projektu.md).

Ceny a sklad sme overili na stránkach obchodov 5. 11. 2026. Pred objednaním ich skontroluj, menia sa. Ceny sú s DPH.

**Spolu ≈ 40–45 €, teda ≈ 10–11 € na osobu.** Navyše treba len skrutky M3 a filament.

## Techfun.sk (osobný odber v Bratislave zadarmo, inak od 2,75 €)

| Diel | Ks | Cena za kus | Spolu | Poznámka |
|---|---|---|---|---|
| [DRV8833](https://techfun.sk/produkt/motor-driver-3v-10v-dual-h-bridge-drv8833/) | 2 | 1,60 € | 3,20 € | stránka neuvádza, či sú kolíky napájané, možno bude treba spájkovať |
| [DC motorček + pneumatika](https://techfun.sk/produkt/dc-motorcek-pneumatika/) | 4 | 2,10 € | 8,40 € | 3–6 V, koleso 66 mm |
| [Gulička W420](https://techfun.sk/produkt/gulicka-w420-pre-stavebnice-robotickych-auticok/) | 2 | 0,70 € | 1,40 € | výška 20 mm, otvory 3,1 mm; podľa nej navrhnúť podvozok |
| [HC-SR04](https://techfun.sk/produkt/hc-sr04-ultrazvukovy-senzor-vzdialenosti/) | 2 | 1,65 € | 3,30 € | napájať z 5 V, ECHO cez delič (nižšie) |
| [Nepájivé pole 170 bodov](https://techfun.sk/produkt/nepajive-pole-170-bodov/) | 2 | 0,40 € | 0,80 € | |
| [Káble M-F, 40 ks, 20 cm](https://techfun.sk/produkt/kabliky-40-kusov-20-cm/) | 1 | 2,20 € | 2,20 € | z pinov ESP32 do poľa; variant na sklade over v košíku |
| [Káble M-M, 40 ks, 10 cm](https://techfun.sk/produkt/kabliky-40-kusov-10-cm/) | 1 | 1,45 € | 1,45 € | prepojenia na poli; variant na sklade over v košíku |
| [Kondenzátor 1000 µF, 63 V](https://techfun.sk/produkt/elektrolyticky-kondenzator-63v-rozne-kapacity/) | 2 | do 1,10 € | do 2,20 € | presná cena sa ukáže až po výbere variantu |
| [Rezistory 1 kΩ, 20 ks](https://techfun.sk/produkt/rezistor-rozne-hodnoty-1-4w-10-kusov/) | 1 | 0,25 € | 0,25 € | v ponuke vyber 1 kΩ, treba 6 ks; ak nie je, spýtaj sa v SmartLabe |

**Spolu ≈ 23 €.**

## HWKitchen.cz (Zásilkovna na Slovensko 3,90 €)

| Diel | Ks | Cena za kus | Spolu | Poznámka |
|---|---|---|---|---|
| [ESP32 DevKitC 38 pin, WROOM-32E, microUSB](https://www.hwkitchen.cz/esp32-devkitc-38pin-esp32-wroom-32e-4-mb-wifi-bluetooth-microusb/) | 2 | 195 Kč | 390 Kč | |

**Spolu ≈ 20 € vrátane dopravy** (orientačný prepočet na eurá).

Techfun má na sklade len verziu [WROOM-32U](https://techfun.sk/produkt/esp32-wroom-32u-vyvojova-doska-so-socketom-pre-antenu/) (9,85 €), ktorá potrebuje externú anténu. Preto ESP32 kupujeme inde. Záloha, ak HWKitchen nebude mať sklad: [Drátek](https://dratek.cz/arduino-platforma/51547-esp32-devkitc-development-board-38pin.html) (227 Kč).

## Čo nekupovať

- **USB kábel a powerbanka:** vlastné. Na napájanie treba aj jeden starý USB kábel na odstrihnutie (pozri nižšie).
- **Senzory čiary:** až keď bude čas na LINE.
- **[Stavebnica auta 2WD](https://techfun.sk/produkt/stavebnica-auta-2wd/) (9,70 €):** netreba, je to záloha pre prípad, že by sa tlač podvozku oneskorila.

## Zapojenie, ktoré sa oproti pôvodnému návrhu zmenilo

Úplná tabuľka pinov je v [návrhu zadania, kap. 6](../docs/navrh-zadania.md#6-hardvér-zjednodušený-a-lacnejší).

**1. Pin spánku na DRV8833.** Čip má vstup `nSLEEP` (na moduloch označený napr. `EEP` alebo `SLP`) a bez úrovne HIGH sú výstupy vypnuté. Ak ho modul nemá natrvalo pripojený, spoj ho s 3,3 V.

**2. Motory nenapájať cez ESP32.** Na doskách DevKit vedie prúd z USB do pinu 5 V cez malú diódu. Na niektorých sa pri preťažení zničí. Preto:

```
powerbanka → odstrihnutý USB kábel: červený +5 V, čierny GND → napájacie lišty poľa
lišta +5 V → VM na DRV8833, 5V pin na ESP32, VCC na HC-SR04
lišta GND  → GND na DRV8833, GND na ESP32, GND na HC-SR04
kondenzátor 1000 µF medzi VM a GND (dlhá nožička na +, pásik na plášti na GND)
```

Farby vodičov over multimetrom, nie každý kábel ich dodržiava. Keď je ESP32 pripojené USB káblom k notebooku, powerbanku odpoj.

**3. Delič na ECHO.** Výstup ECHO z HC-SR04 má 5 V a pin ESP32 by to poškodilo:

```
ECHO — 1 kΩ — GPIO 18 — 1 kΩ — 1 kΩ — GND     (na GPIO 18 je ≈ 3,3 V)
```

Ak by sa našiel senzor HC-SR04P alebo [RCWL-9610](https://www.laskakit.cz/en/arduino-ultrazvukovy-meric-vzdalenosti-hc-sr04/) (LaskaKit, uvádza 3,3–5 V), dá sa napájať z 3,3 V bez deliča. Vyžadovalo by to objednávku z ďalšieho obchodu.
