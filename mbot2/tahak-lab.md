# Ťahák do labu: prvý test programu Nerozlej

Na jednu návštevu SmartLabu, asi 45 minút. Netreba nič programovať, len nahrať hotový program, vyskúšať ho a zapísať, čo vyšlo.

## Čo si vziať

- notebook s **mBlockom 5** (zadarmo, [stiahnuť](https://mblock.cc/pages/downloads)), nainštaluj si ho už doma
- kábel USB-C
- izolačnú pásku (čierna na svetlej podlahe alebo stole), krabicu, loptičku, kus kartónu a meter
- mobil na fotky a video

## 1. Nahratie programu (10 minút)

Program sa nekonvertuje, súbor `nerozlej.py` sa vloží do mBlocku taký, aký je.

1. Zapni auto vypínačom na podvozku a pripoj CyberPi káblom k notebooku.
2. V mBlocku vľavo dole v časti **Zariadenia** klikni na **Pridať**, vyber **CyberPi** a potvrď.
3. Klikni na **Pripojiť**, zvoľ **USB** a port, ktorý ponúkne. Ak si mBlock vypýta aktualizáciu firmvéru, potvrď ju.
4. Prepínač **Live / Upload** daj na **Upload**.
5. Nad plochou s blokmi prepni z **Bloky** na **Python**.
6. Otvor [nerozlej.py na GitHube](https://github.com/Hinzun/PRJ-069-AutoLab/blob/nerozlej/mbot2/nerozlej.py) a vpravo hore nad kódom klikni na **Copy raw file**.
7. V mBlocku označ všetko v editore (Ctrl+A), vlož kód (Ctrl+V) a klikni na **Nahrať** (Upload).
8. Na displeji auta má byť menu **NEROZLEJ**. Ak sa neobjaví, vypni a zapni auto.

**Keď sa niečo zasekne:** odfoť obrazovku notebooku aj displej auta a pošli to Erikovi. Ak sa tlačidlá v mBlocku volajú inak, zapíš si ako, nech opravíme ťahák.

Ak mBlock nemá prepnutie na Python, skús webový [mBlock Python Editor](https://python.mblock.cc), postup je rovnaký.

## Ovládanie auta

| Ovládač | Čo robí |
|---|---|
| joystick hore a dole | výber riadku |
| joystick doľava a doprava | zmena hodnoty |
| A | štart jazdy alebo otvorenie Test senzorov a Vysledky |
| B | stop, späť do menu, po jazde „loptička spadla“ |

## 2. Príprava trasy (5 minút)

Nalep z pásky rovnú čiaru dlhú asi 1,5 m. Na jej koniec postav krabicu tak, aby čiara končila tesne pred ňou.

## 3. Testy (30 minút)

Pri každom teste zapíš do stĺpca „Čo vyšlo“ hodnoty alebo len áno či nie. Displej pri testoch 3 a 4 odfoť.

| # | Čo spraviť | Čo má vyjsť | Čo vyšlo |
|---|---|---|---|
| 1 | nahrať program | na displeji je menu NEROZLEJ | |
| 2 | v menu skúsiť joystick hore, dole, doľava a doprava | kurzor sa hýbe, hodnoty sa menia o jeden krok | |
| 3 | **Test senzorov** (A): pomaly posúvať auto rukou naprieč čiarou | „Ciara“ je nad čiarou okolo 0, na jednej strane záporná a na druhej kladná; „Stav“ je mimo čiary 0 | |
| 4 | **Test senzorov**: ruka pred autom na 10, 20 a 50 cm | „Vzdial“ približne sedí s metrom | |
| 5 | **Test senzorov**: stlačiť A, auto ide 1 s | ide **dopredu** a rovno (nie dozadu, netočí sa) | |
| 6 | späť (B), nastaviť Trasa **Rovno**, Rychlost 30, jazda (A) ku krabici | zastaví pred krabicou bez dotyku | |
| 7 | Trasa **Ciara**, Rychlost 30, jazda po čiare | drží sa čiary až ku krabici | |
| 8 | loptička na kartóne položenom na aute: jazda **pokojná** (Rychlost 30, Rozjazd 2.0, Brzdenie 30) | zapíš Cas, Otrasy, Spicka a či loptička spadla | |
| 9 | to isté, jazda **trhaná** (Rychlost 80, Rozjazd 0.0, Brzdenie 0) | Otrasy a Spicka sú vyššie ako v teste 8 | |
| 10 | Rychlost postupne znižovať od 30 | pri akej najnižšej rýchlosti sa auto ešte pohne | |

Pri teste 9 drž ruku pri krabici, keby auto nezastavilo.

## 4. Čo poslať Erikovi

- vyplnenú tabuľku, stačí aj fotka papiera
- fotky displeja z testov 3 a 4
- krátke video jazdy z testov 7 a 9
- fotku auta zboku a zhora, podľa nej navrhneme nádobu

Fotky a videá sa nám zídu aj do dokumentácie, takže ich nemaž.
