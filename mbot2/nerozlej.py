# Nerozlej: program pre mBot2 (CyberPi), MicroPython.
# Nahráva sa v mBlocku 5 v režime Upload, postup je v mbot2/README.md.
# Správanie opisuje docs/moznost-nerozlej.md, kapitola Program na aute.
#
# Ovládanie: joystick hore/dole vyberá riadok, doľava/doprava mení hodnotu,
# tlačidlo A spustí jazdu, tlačidlo B jazdu zastaví alebo vráti späť do menu.
# Na displeji je text bez diakritiky, lebo nevieme, či ju písmo CyberPi zvládne.

from time import sleep

import cyberpi
import mbot2
import mbuild

VERZIA = "0.1"

# ---------------------------------------------------------------------------
# Konštanty, ktoré sa dolaďujú na aute (pozri README, prvá návšteva v labe)
# ---------------------------------------------------------------------------
SMER_CIARY = 1        # ak auto pri sledovaní čiary uteká od čiary, zmeň na -1
STOP_CM = 8           # pri tejto vzdialenosti od prekážky auto stojí
MIN_VYKON = 15        # najnižší výkon v %, pri ktorom sa auto ešte pohne
CIARA_STRATENA_S = 0.5  # po takom čase bez čiary auto zastaví
MAX_JAZDA_S = 60      # bezpečnostný limit dĺžky jazdy
PERIODA_S = 0.02      # perióda riadiacej slučky
TEST_VYKON = 30       # výkon pri skúšobnej jazde v teste senzorov

TRASA_NAZVY = ("Ciara", "Rovno")

# Parametre, ktoré nastavuje hráč: kľúč, text na displeji, min, max, krok, predvolené, jednotka
PARAMETRE = (
    ("rychlost", "Rychlost", 20, 80, 5, 40, "%"),
    ("rozjazd", "Rozjazd", 0.0, 3.0, 0.5, 1.0, "s"),
    ("brzdenie", "Brzdenie", 0, 40, 5, 20, "cm"),
    ("zatacanie", "Zatacanie", 1, 10, 1, 4, ""),
    ("trasa", "Trasa", 0, 1, 1, 0, ""),
)
POLOZKY_MENU = len(PARAMETRE) + 2   # parametre, Test senzorov, Vysledky
POLOZKA_TEST = len(PARAMETRE)
POLOZKA_VYSLEDKY = len(PARAMETRE) + 1
MAX_HISTORIA = 6


# ---------------------------------------------------------------------------
# Čistá logika (bez hardvéru, testuje sa na PC v mbot2/test/)
# ---------------------------------------------------------------------------
def obmedz(hodnota, dole, hore):
    if hodnota < dole:
        return dole
    if hodnota > hore:
        return hore
    return hodnota


def predvolene_hodnoty():
    return {p[0]: p[5] for p in PARAMETRE}


def platne_hodnoty(hodnoty):
    """Vráti kópiu, v ktorej je každý parameter v povolenom rozsahu."""
    vysledok = {}
    for kluc, _text, dole, hore, _krok, predvolene, _jednotka in PARAMETRE:
        vysledok[kluc] = obmedz(hodnoty.get(kluc, predvolene), dole, hore)
    return vysledok


def zmen_parameter(hodnoty, index, smer):
    """Posunie parameter s indexom o jeden krok (smer +1 alebo -1)."""
    kluc, _text, dole, hore, krok, _predvolene, _jednotka = PARAMETRE[index]
    nova = obmedz(hodnoty[kluc] + smer * krok, dole, hore)
    if isinstance(krok, float):
        nova = round(nova, 1)
    hodnoty[kluc] = nova
    return nova


def text_parametra(index, hodnoty):
    kluc, text, _dole, _hore, _krok, _predvolene, jednotka = PARAMETRE[index]
    hodnota = hodnoty[kluc]
    if kluc == "trasa":
        return "{} {}".format(text, TRASA_NAZVY[int(hodnota)])
    if isinstance(hodnota, float):
        return "{} {:.1f}{}".format(text, hodnota, jednotka)
    return "{} {}{}".format(text, hodnota, jednotka)


def faktor_rozjazdu(t, rozjazd_s):
    """0 až 1: ako ďaleko je rozjazd po t sekundách."""
    if rozjazd_s <= 0:
        return 1.0
    return obmedz(t / rozjazd_s, 0.0, 1.0)


def faktor_brzdenia(vzdialenost_cm, brzdenie_cm):
    """0 až 1: plný výkon ďaleko od prekážky, lineárne spomalenie na brzdnej dráhe."""
    if vzdialenost_cm <= STOP_CM:
        return 0.0
    if brzdenie_cm <= 0:
        return 1.0
    return obmedz((vzdialenost_cm - STOP_CM) / brzdenie_cm, 0.0, 1.0)


def cielovy_vykon(rychlost, f_rozjazd, f_brzda):
    """Výkon v %, ktorý má auto mať. Pri pohybe nikdy menej než MIN_VYKON."""
    faktor = min(f_rozjazd, f_brzda)
    if faktor <= 0:
        return 0
    return max(MIN_VYKON, rychlost * faktor)


def vykon_kolies(zaklad, odchylka, zatacanie, smer=SMER_CIARY):
    """P regulátor sledovania čiary.

    odchylka je -100 až 100 zo senzora (záporná: auto je vľavo od čiary).
    Pri zatacanie 5 a odchylke 100 sa vnútorné koleso zastaví.
    """
    korekcia = smer * (odchylka / 100.0) * zaklad * (zatacanie / 5.0)
    lave = obmedz(zaklad - korekcia, -100, 100)
    prave = obmedz(zaklad + korekcia, -100, 100)
    return lave, prave


def odchylka_zrychlenia(vzorka, zaklad):
    """Veľkosť rozdielu medzi aktuálnym zrýchlením a zrýchlením v pokoji.

    Nezávisí od toho, ako je CyberPi na aute natočený.
    """
    return ((vzorka[0] - zaklad[0]) ** 2 + (vzorka[1] - zaklad[1]) ** 2
            + (vzorka[2] - zaklad[2]) ** 2) ** 0.5


class Otrasy:
    """Priemer a špička odchýlky zrýchlenia počas jazdy."""

    def __init__(self, zaklad):
        self.zaklad = zaklad
        self.sucet = 0.0
        self.pocet = 0
        self.spicka = 0.0

    def pridaj(self, vzorka):
        o = odchylka_zrychlenia(vzorka, self.zaklad)
        self.sucet += o
        self.pocet += 1
        if o > self.spicka:
            self.spicka = o

    def priemer(self):
        return self.sucet / self.pocet if self.pocet else 0.0


def text_vysledku(c, v):
    """Jeden riadok do zoznamu výsledkov, napr. '3 R40 B20 12.3s OK'."""
    stav = "OK" if v["uspech"] else "X"
    return "{} R{} B{} {:.1f}s {}".format(c, v["rychlost"], v["brzdenie"], v["cas"], stav)


def najlepsi_cas(historia):
    casy = [v["cas"] for v in historia if v["uspech"]]
    return min(casy) if casy else None


# ---------------------------------------------------------------------------
# Hardvér
# ---------------------------------------------------------------------------
def cas():
    return cyberpi.timer.get()


def jazdi(lave, prave):
    # Pravý motor je otočený, preto dopredu znamená (+, -).
    mbot2.drive_power(lave, -prave)


def zastav():
    mbot2.drive_power(0, 0)


def vzdialenost():
    return mbuild.ultrasonic2.get(1)


def odchylka_ciary():
    return mbuild.quad_rgb_sensor.get_offset_track(1)


def vidi_ciaru():
    return mbuild.quad_rgb_sensor.get_line_sta("all", 1) != 0


def zrychlenie():
    return (cyberpi.get_acc("x"), cyberpi.get_acc("y"), cyberpi.get_acc("z"))


def zobraz(text):
    cyberpi.display.show_label(text, 12, 0, 0, index=0)


def novy_displej(text):
    cyberpi.display.clear()
    zobraz(text)


def led(r, g, b):
    cyberpi.led.on(r, g, b, id="all")


_TLACIDLA = ("a", "b", "up", "down", "left", "right")
_predtym = {}


def stlacene(meno):
    """True len v okamihu stlačenia, nie počas držania."""
    teraz = cyberpi.controller.is_press(meno)
    bolo = _predtym.get(meno, False)
    _predtym[meno] = teraz
    return teraz and not bolo


def obnov_tlacidla():
    for meno in _TLACIDLA:
        _predtym[meno] = cyberpi.controller.is_press(meno)


# ---------------------------------------------------------------------------
# Obrazovky
# ---------------------------------------------------------------------------
def text_menu(vyber, hodnoty, historia):
    rekord = najlepsi_cas(historia)
    riadky = ["NEROZLEJ " + ("R:{:.1f}s".format(rekord) if rekord is not None else "v" + VERZIA)]
    for i in range(len(PARAMETRE)):
        riadky.append((">" if i == vyber else " ") + text_parametra(i, hodnoty))
    riadky.append((">" if vyber == POLOZKA_TEST else " ") + "Test senzorov")
    riadky.append((">" if vyber == POLOZKA_VYSLEDKY else " ") + "Vysledky")
    riadky.append("A=start </>=zmen")
    return "\n".join(riadky)


def odpocet():
    """Odpočet 3 s. Auto stojí, preto sa počas neho meria zrýchlenie v pokoji."""
    sucet = [0.0, 0.0, 0.0]
    pocet = 0
    for n in (3, 2, 1):
        novy_displej("NEROZLEJ\n\n   {}\n\nB = zrusit".format(n))
        cyberpi.audio.play_tone(600, 0.1)
        for _ in range(9):
            if cyberpi.controller.is_press("b"):
                return None
            z = zrychlenie()
            for i in range(3):
                sucet[i] += z[i]
            pocet += 1
            sleep(0.1)
    cyberpi.audio.play_tone(900, 0.2)
    return (sucet[0] / pocet, sucet[1] / pocet, sucet[2] / pocet)


def jazda(hodnoty):
    """Jedna jazda. Vráti (čas, otrasy, dôvod konca), alebo None pri zrušení."""
    zaklad = odpocet()
    if zaklad is None:
        return None
    otrasy = Otrasy(zaklad)
    novy_displej("JAZDA\n\nB = stop")
    led(0, 0, 255)
    ciara = int(hodnoty["trasa"]) == 0
    start = cas()
    bez_ciary_od = None
    blizko = 0
    dovod = "ciel"
    while True:
        t = cas() - start
        if cyberpi.controller.is_press("b"):
            dovod = "stop B"
            break
        if t > MAX_JAZDA_S:
            dovod = "cas"
            break
        d = vzdialenost()
        # zastavíme až pri dvoch meraniach za sebou, jedno chybné meranie nestačí
        blizko = blizko + 1 if d <= STOP_CM else 0
        if blizko >= 2:
            dovod = "ciel"
            break
        vykon = cielovy_vykon(hodnoty["rychlost"], faktor_rozjazdu(t, hodnoty["rozjazd"]),
                              faktor_brzdenia(d, hodnoty["brzdenie"]))
        if ciara:
            if vidi_ciaru():
                bez_ciary_od = None
            elif bez_ciary_od is None:
                bez_ciary_od = t
            elif t - bez_ciary_od > CIARA_STRATENA_S:
                dovod = "bez ciary"
                break
            lave, prave = vykon_kolies(vykon, odchylka_ciary(), hodnoty["zatacanie"])
        else:
            lave, prave = vykon, vykon
        jazdi(lave, prave)
        otrasy.pridaj(zrychlenie())
        sleep(PERIODA_S)
    zastav()
    led(0, 0, 0)
    return cas() - start, otrasy, dovod


def opytaj_loptu():
    novy_displej("Je loptica\nv nadobe?\n\nA = ano\nB = spadla")
    obnov_tlacidla()   # aby sa nerátalo B, ktoré ešte držíš po zastavení jazdy
    while True:
        if stlacene("a"):
            return True
        if stlacene("b"):
            return False
        sleep(PERIODA_S)


def ukaz_vysledok(v, historia):
    rekord = najlepsi_cas(historia)
    novy_displej("\n".join((
        "VYSLEDOK",
        "Cas: {:.1f} s".format(v["cas"]),
        "Otrasy: {:.1f}".format(v["otrasy"]),
        "Spicka: {:.1f}".format(v["spicka"]),
        "Koniec: " + v["dovod"],
        "Loptica: " + ("OK" if v["lopta"] else "SPADLA"),
        "Rekord: " + ("{:.1f} s".format(rekord) if rekord is not None else "-"),
        "B = spat",
    )))
    if v["uspech"]:
        led(0, 255, 0)
    else:
        led(255, 0, 0)
    obnov_tlacidla()
    while not stlacene("b"):
        sleep(PERIODA_S)
    led(0, 0, 0)


def ukaz_historiu(historia):
    riadky = ["VYSLEDKY"]
    zaciatok = max(0, len(historia) - MAX_HISTORIA)
    for i in range(zaciatok, len(historia)):
        riadky.append(text_vysledku(i + 1, historia[i]))
    if not historia:
        riadky.append("zatial ziadne")
    riadky.append("B = spat")
    novy_displej("\n".join(riadky))
    obnov_tlacidla()
    while not stlacene("b"):
        sleep(PERIODA_S)


def test_senzorov():
    """Ukazuje hodnoty senzorov. A = krátka jazda dopredu, B = späť."""
    obnov_tlacidla()
    cyberpi.display.clear()
    zaklad = zrychlenie()
    while True:
        d = vzdialenost()
        zobraz("\n".join((
            "TEST v" + VERZIA,
            "Ciara: {}".format(odchylka_ciary()),
            "Stav: {}".format(mbuild.quad_rgb_sensor.get_line_sta("all", 1)),
            "Vzdial: {} cm".format(d),
            "Otras: {:.1f}".format(odchylka_zrychlenia(zrychlenie(), zaklad)),
            "Bateria: {}%".format(cyberpi.get_extra_battery()),   # batéria v podvozku mBot2
            "A=1s dopredu",
            "B=spat",
        )))
        if stlacene("a") and d > STOP_CM + 10:
            jazdi(TEST_VYKON, TEST_VYKON)
            koniec = cas() + 1
            while cas() < koniec and vzdialenost() > STOP_CM:
                sleep(PERIODA_S)
            zastav()
        if stlacene("b"):
            return
        sleep(0.2)


# ---------------------------------------------------------------------------
# Hlavný program
# ---------------------------------------------------------------------------
def main():
    zastav()                    # po zapnutí auto vždy stojí
    cyberpi.timer.reset()
    hodnoty = platne_hodnoty(predvolene_hodnoty())
    historia = []
    vyber = 0
    obnov_tlacidla()
    novy_displej(text_menu(vyber, hodnoty, historia))
    while True:
        zmena = False
        if stlacene("up"):
            vyber = (vyber - 1) % POLOZKY_MENU
            zmena = True
        elif stlacene("down"):
            vyber = (vyber + 1) % POLOZKY_MENU
            zmena = True
        elif vyber < len(PARAMETRE) and stlacene("left"):
            zmen_parameter(hodnoty, vyber, -1)
            zmena = True
        elif vyber < len(PARAMETRE) and stlacene("right"):
            zmen_parameter(hodnoty, vyber, 1)
            zmena = True
        elif stlacene("a"):
            if vyber == POLOZKA_TEST:
                test_senzorov()
            elif vyber == POLOZKA_VYSLEDKY:
                ukaz_historiu(historia)
            else:
                vysledok = jazda(platne_hodnoty(hodnoty))
                if vysledok is not None:
                    trvanie, otrasy, dovod = vysledok
                    lopta = opytaj_loptu()
                    v = {
                        "cas": trvanie, "otrasy": otrasy.priemer(), "spicka": otrasy.spicka,
                        "dovod": dovod, "lopta": lopta, "uspech": lopta and dovod == "ciel",
                        "rychlost": hodnoty["rychlost"], "brzdenie": hodnoty["brzdenie"],
                    }
                    historia.append(v)
                    ukaz_vysledok(v, historia)
            obnov_tlacidla()
            zmena = True
        if zmena:
            novy_displej(text_menu(vyber, hodnoty, historia))
        sleep(PERIODA_S)


# Na PC v testoch sa namiesto CyberPi načíta náhrada s IS_STUB = True a main() sa nespustí.
if not getattr(cyberpi, "IS_STUB", False):
    main()
