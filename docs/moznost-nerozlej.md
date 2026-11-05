# Možnosť projektu: Nerozlej

> **Stav:** návrh z 5. 11. 2026. Tím ani cvičiaci ho zatiaľ neschválili a na aute sa zatiaľ nič z neho neskúšalo. Je to alternatíva, doterajší [návrh zadania](navrh-zadania.md) a [špecifikácia](specifikacia.md) platia bez zmeny, kým sa tím nerozhodne inak.

## Myšlienka

Robot mBot2 ide po čiare ako čašník a na 3D tlačenom podnose alebo v nádobe vezie loptičku. Hráč nastaví parametre jazdy, auto s nimi odjazdí celú trasu a cieľom je dôjsť čo najplynulejšie bez straty loptičky.

Rýchlejšia jazda skracuje čas, ale zvyšuje riziko pádu. Hráč preto hľadá najlepší kompromis, a práve na tom je vidieť systémové myslenie.

Autá by sme si požičali z laboratória. Cvičiaci nám ich odporučil použiť namiesto kúpy dielov.

## Cieľová skupina a prínos

Toto je pracovná hypotéza, zatiaľ nie je overená so žiadnym učiteľom ani žiakom.

| Kto | Prínos |
|---|---|
| **Učiteľ**, ktorý už má mBoty | hotová aktivita na hodinu bez nákupu nových robotov |
| **Stredoškoláci** | skúšajú si kompromis medzi rýchlosťou a plynulosťou na vlastných pokusoch, nemusia programovať |

## Rozsah

### Must

| Oblasť | Čo treba |
|---|---|
| Jazda | sledovanie čiary s nastaviteľnými parametrami, plynulý rozjazd a brzdenie, zastavenie v cieli |
| Nastavenia | rýchlosť, plynulosť rozjazdu a brzdenia, citlivosť sledovania čiary; ladenie priamo na aute cez displej a joystick |
| Skóre | čas, otrasy z gyroskopu a pád loptičky |
| Obtiažnosť | 2 až 3 hĺbky nádoby |
| 3D tlač | nádoba a držiak, ktoré nezakrývajú displej, joystick ani senzory |
| Bezpečnosť | zastavenie pred prekážkou cez ultrazvuk; v nádobe žiadna voda |
| Pre učiteľa | krátky návod a pracovný list |

### Should

- ľahšia a ťažšia trasa
- aplikácia na ladenie, ak test potvrdí spoľahlivé spojenie s autom
- automatické spomalenie podľa otrasov, ktorého výsledok sa dá porovnať s nastavením od hráča

### Čo auto nevie

- **Nevidí pohyb loptičky.** Gyroskop meria otrasy auta, nie loptičky, a samostatný senzor na loptičku nemáme.
- **Pád loptičky zapisuje človek.**
- **Nastavenie platí pre celú jazdu.** Dobré nastavenie hľadá hráč.

### Čo treba naprogramovať

Senzor čiary a gyroskop sú súčasťou auta. Treba však napísať riadenie po čiare s nastaviteľnými parametrami, plynulý rozjazd a brzdenie, zastavenie v cieli, výpočet skóre a nastavovanie parametrov.

## Prvý test

Spravíme ho pred tlačou nádoby.

1. Vyrobíme kartónový podnos, položíme naň loptičku a z izolačnej pásky nalepíme krátku čiaru.
2. Pustíme pokojnú a trhanú jazdu a zapíšeme čas, hodnoty z gyroskopu a to, či loptička spadla.
3. Vyhodnotíme, či robot spoľahlivo drží čiaru a či sa obe jazdy dajú v dátach rozlíšiť.

Ak sa v dátach rozlíšiť nedajú, skóre postavíme len na čase a páde loptičky.

## Riziká

| Riziko | Čo s tým |
|---|---|
| sledovanie čiary nie je dosť presné | overiť v prvom teste, zjednodušiť trasu |
| vibrácie motorov prekryjú otrasy z jazdy | skóre len z času a pádu loptičky |
| nádoba zmení ťažisko alebo zakryje ovládanie | najprv kartónový model, potom tlač po jednej hĺbke |
| aplikácia nebude mať spoľahlivé spojenie | ladiť na aute; režim Live vyžaduje stále pripojenie k počítaču a Wi-Fi treba overiť |
| autá nebudú dostupné do prezentácie | dohodnúť výpožičku vopred |

## Porovnanie možností

[Brzdná výzva](moznost-brzdna-vyzva.md) je tiež len nápad: na mBot2 žiaci nastavujú rýchlosť a vzdialenosť zastavenia a vyhráva auto, ktoré zastaví najbližšie pri prekážke bez dotyku.

| | AutoLab s ESP32 | Brzdná výzva | Nerozlej |
|---|---|---|---|
| **Auto** | vlastné, treba kúpiť diely | požičaný mBot2 | požičaný mBot2 |
| **3D tlač** | celý podvozok | nárazník a zadná doska | nádoba a držiak |
| **Ovládanie** | mobil cez stránku v aute | displej a joystick na aute | displej a joystick na aute |
| **Stav softvéru** | napísaný, na hardvéri neoverený | nezačatý | nezačatý |
| **Hlavné riziko** | nákup, zapojenie a zloženie áut | spoľahlivosť zastavenia | presnosť čiary a dáta z gyroskopu |
| **Stav** | v [návrhu zadania](navrh-zadania.md) | [nápad](moznost-brzdna-vyzva.md) | nápad, tento dokument |

## Otázky pre tím

1. Ktorú možnosť chceme robiť?
2. Koľko mBotov dostaneme a môžeme ich mať až do januárovej prezentácie?
3. Súhlasí cvičiaci, že 3D tlač bude len nádoba a držiak?
4. Chceme aplikáciu už v základe, alebo až ako rozšírenie?
5. Ak prejdeme na mBot2, ako si nanovo rozdelíme role a témy KNIFE?

Zdroj k režimom Live a Upload: [Makeblock Education](https://education.makeblock.com/?p=78174).
