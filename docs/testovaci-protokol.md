# Protokol testov AutoLab

Akceptačné kritériá sú z [návrhu zadania](navrh-zadania.md), kapitola 5. Každý test zapíšeme ako nový riadok v tabuľke výsledkov.

## Testy

| Cieľ | Test | Splnené, ak |
|---|---|---|
| G1 | jazda z mobilu po miestnosti, obe autá naraz z dvoch mobilov | obe autá jazdia, odozva do 200 ms |
| G2 | zmena `max_pwm` a `trim` za jazdy | správanie sa zmení do 0,5 s |
| G3 | krabica v ceste pri jazde | auto zastaví pred ňou v 5 z 5 pokusov |
| G4 | vypnúť Wi-Fi v mobile počas jazdy | auto zastaví do 1 s |
| G6 | autá za sebou: predné prudko zastaví, zadné ide na `max_pwm` | zadné auto zastaví bez dotyku v 5 z 5 pokusov |
| G5 (Should) | režim LINE na ováli z izolačnej pásky | 3 kolá za sebou bez vybočenia |

## Výsledky

| Dátum | Test | Auto | Verzia firmvéru (commit) | Parametre | Výsledok | Kto testoval | Poznámka |
|---|---|---|---|---|---|---|---|
| | | | | | | | |
