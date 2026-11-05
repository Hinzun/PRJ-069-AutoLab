# Možnosť projektu: Brzdná výzva

> **Stav:** návrh z 5. 11. 2026. Tím ani cvičiaci ho zatiaľ neschválili a na aute sa zatiaľ nič z neho neskúšalo. Je to alternatíva, doterajší [návrh zadania](navrh-zadania.md) a [špecifikácia](specifikacia.md) platia bez zmeny, kým sa tím nerozhodne inak.

## Myšlienka

Hráč na požičanom mBot2 nastaví rýchlosť a vzdialenosť zastavenia. Vyhráva auto, ktoré zastaví najbližšie pri prekážke bez dotyku. Pri vyššej rýchlosti auto brzdí dlhšie a senzor reaguje s oneskorením, takže príliš odvážne nastavenie skončí nárazom.

## Cieľová skupina a prínos

Toto je pracovná hypotéza, zatiaľ nie je overená so žiadnym učiteľom ani žiakom.

| Kto | Prínos |
|---|---|
| **Učiteľ** informatiky alebo vedúci krúžku, ktorý už má mBoty | hotová aktivita na hodinu bez nákupu nových robotov |
| **Stredoškoláci** približne od 15 do 18 rokov | spätnú väzbu si vyskúšajú na vlastných pokusoch, nemusia programovať |

## Nastavenia

Rozsahy sú začiatočné a doladia sa po prvých jazdách.

| Parameter | Čo znamená | Začiatočný rozsah |
|---|---|---|
| Rýchlosť | ako rýchlo auto ide k prekážke | 20 až 100 % |
| Vzdialenosť zastavenia | pri akej vzdialenosti začne brzdiť | 10 až 50 cm |
| Oneskorenie merania | ako často auto kontroluje senzor | 50 až 500 ms |

## Rozsah

### Must

| Režim alebo oblasť | Čo treba | Splnené, ak |
|---|---|---|
| Stena | auto ide k stene a samo zastaví | bez dotyku v 5 z 5 pokusov pri bezpečnom nastavení |
| Ladenie | zmena parametrov joystickom na aute | zmena sa prejaví pri ďalšej jazde a príliš odvážne nastavenie vedie k dotyku |
| Konvoj | predné auto zastaví, zadné ide za ním | zadné zastaví bez dotyku v 5 z 5 pokusov, bez komunikácie medzi autami |
| Výsledok | displej po zastavení ukáže vzdialenosť od prekážky | hodnota sa dá porovnať s meraním metrom |
| 3D tlač | nárazník a zadná doska na odraz ultrazvuku | diely držia na aute a nezakrývajú senzor ani displej |
| Pre učiteľa | krátky návod a pracovný list | človek mimo tímu podľa nich aktivitu spustí |

### Should

- rôzne povrchy, napríklad stôl, koberec a papier
- 3D tlačená nádoba so závažím, aby bolo vidieť vplyv hmotnosti na brzdenie

### Mimo základného rozsahu

Kamera, Wi-Fi a mobil. Rebríček výsledkov je len voliteľný.

## Prvý test

Kto ho spraví: TODO. Čo treba najprv skontrolovať na autách, je v [stave projektu](stav-projektu.md#čo-overiť-na-požičaných-autách).

1. Nahráme krátky program, v ktorom auto zastaví pred stenou.
2. Skúsime zmeniť vzdialenosť zastavenia priamo na aute.
3. Zapíšeme niekoľko jázd s rôznou rýchlosťou a zmeriame, kde auto zastavilo.

## Riziká

| Riziko | Čo s tým |
|---|---|
| ultrazvuk neposkytne spoľahlivé zastavenie | overiť v prvom teste, obmedziť rýchlosť |
| k dispozícii bude málo áut s ultrazvukom | bez dvoch áut vynechať režim Konvoj |
| požičané auto sa pri nárazoch poškodí | mäkký nárazník, nižšie rýchlosti, nárazy len do mäkkej prekážky |
| autá nebudú dostupné do prezentácie | dohodnúť výpožičku vopred |

## Otázky pre tím

1. Je toto možnosť, ktorú chceme robiť?
2. Koľko mBotov s ultrazvukom dostaneme?
3. Súhlasí cvičiaci, že 3D tlač bude len nárazník a zadná doska?

Porovnanie s ostatnými možnosťami je v [moznost-nerozlej.md](moznost-nerozlej.md).
