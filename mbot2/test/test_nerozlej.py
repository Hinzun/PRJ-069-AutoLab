# Testy logiky programu Nerozlej na PC, bez auta.
# Spustenie z koreňa repozitára:  python -m unittest discover -s mbot2/test -v
#
# Moduly cyberpi, mbot2 a mbuild existujú len na CyberPi, preto ich tu nahradíme
# jednoduchou simuláciou: auto ide rovno k stene a pohyb závisí od výkonu motorov.

import importlib.util
import os
import sys
import types
import unittest

CESTA = os.path.join(os.path.dirname(__file__), "..", "nerozlej.py")


class Simulacia:
    def __init__(self, stena_cm=100.0, ciara=True):
        self.cas = 0.0
        self.poloha = 0.0
        self.stena = stena_cm
        self.ciara = ciara
        self.vykony = []
        self.stlacene = set()

    def drive_power(self, lave, prave):
        self.vykony.append((lave, prave))

    def krok(self, dt):
        self.cas += dt
        if self.vykony:
            lave, prave = self.vykony[-1]
            # pri výkone 100 % ide auto 50 cm/s; prave má otočené znamienko
            self.poloha += (lave - prave) / 2 / 100 * 50 * dt


def nacitaj_program(sim):
    cyberpi = types.ModuleType("cyberpi")
    cyberpi.IS_STUB = True
    cyberpi.timer = types.SimpleNamespace(get=lambda: sim.cas, reset=lambda: None)
    cyberpi.controller = types.SimpleNamespace(is_press=lambda m: m in sim.stlacene)
    cyberpi.display = types.SimpleNamespace(show_label=lambda *a, **k: None, clear=lambda: None)
    cyberpi.led = types.SimpleNamespace(on=lambda *a, **k: None)
    cyberpi.audio = types.SimpleNamespace(play_tone=lambda *a: None)
    cyberpi.get_acc = lambda os_: {"x": 0.1, "y": 0.0, "z": 9.8}[os_]
    cyberpi.get_extra_battery = lambda: 100

    mbot2 = types.ModuleType("mbot2")
    mbot2.drive_power = sim.drive_power

    mbuild = types.ModuleType("mbuild")
    mbuild.ultrasonic2 = types.SimpleNamespace(get=lambda i: max(0.0, sim.stena - sim.poloha))
    mbuild.quad_rgb_sensor = types.SimpleNamespace(
        get_offset_track=lambda i: 0,
        get_line_sta=lambda s, i: 6 if sim.ciara else 0,
    )
    sys.modules.update({"cyberpi": cyberpi, "mbot2": mbot2, "mbuild": mbuild})

    spec = importlib.util.spec_from_file_location("nerozlej", CESTA)
    program = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(program)
    program.sleep = sim.krok
    return program


class TestParametre(unittest.TestCase):
    def setUp(self):
        self.p = nacitaj_program(Simulacia())

    def test_predvolene_su_v_rozsahu(self):
        h = self.p.predvolene_hodnoty()
        self.assertEqual(h, self.p.platne_hodnoty(h))

    def test_mimo_rozsahu_sa_obmedzi(self):
        h = self.p.platne_hodnoty({"rychlost": 500, "rozjazd": -3, "brzdenie": 99})
        self.assertEqual(h["rychlost"], 80)
        self.assertEqual(h["rozjazd"], 0.0)
        self.assertEqual(h["brzdenie"], 40)
        self.assertEqual(h["zatacanie"], 4)

    def test_zmena_nejde_za_hranicu(self):
        h = self.p.predvolene_hodnoty()
        for _ in range(50):
            self.p.zmen_parameter(h, 0, 1)
        self.assertEqual(h["rychlost"], 80)
        for _ in range(50):
            self.p.zmen_parameter(h, 1, -1)
        self.assertEqual(h["rozjazd"], 0.0)

    def test_desatinny_krok_sa_nerozbije(self):
        h = self.p.predvolene_hodnoty()
        for _ in range(4):
            self.p.zmen_parameter(h, 1, 1)
        self.assertEqual(h["rozjazd"], 3.0)
        self.assertEqual(self.p.text_parametra(1, h), "Rozjazd 3.0s")

    def test_trasa_sa_zobrazi_menom(self):
        h = self.p.predvolene_hodnoty()
        self.assertEqual(self.p.text_parametra(4, h), "Trasa Ciara")
        self.p.zmen_parameter(h, 4, 1)
        self.assertEqual(self.p.text_parametra(4, h), "Trasa Rovno")

    def test_menu_sa_zmesti_na_displej(self):
        h = self.p.predvolene_hodnoty()
        riadky = self.p.text_menu(0, h, []).split("\n")
        self.assertLessEqual(len(riadky), 10)
        self.assertTrue(all(len(r) <= 20 for r in riadky), riadky)


class TestRiadenie(unittest.TestCase):
    def setUp(self):
        self.p = nacitaj_program(Simulacia())

    def test_rozjazd(self):
        self.assertEqual(self.p.faktor_rozjazdu(0.5, 1.0), 0.5)
        self.assertEqual(self.p.faktor_rozjazdu(5, 1.0), 1.0)
        self.assertEqual(self.p.faktor_rozjazdu(0, 0), 1.0)

    def test_brzdenie(self):
        stop = self.p.STOP_CM
        self.assertEqual(self.p.faktor_brzdenia(stop, 20), 0.0)
        self.assertEqual(self.p.faktor_brzdenia(stop + 10, 20), 0.5)
        self.assertEqual(self.p.faktor_brzdenia(200, 20), 1.0)
        self.assertEqual(self.p.faktor_brzdenia(stop + 1, 0), 1.0)

    def test_vykon_pri_pohybe_neklesne_pod_minimum(self):
        self.assertEqual(self.p.cielovy_vykon(40, 0.01, 1), self.p.MIN_VYKON)
        self.assertEqual(self.p.cielovy_vykon(40, 1, 0), 0)
        self.assertEqual(self.p.cielovy_vykon(40, 1, 1), 40)

    def test_na_ciare_ide_rovno(self):
        self.assertEqual(self.p.vykon_kolies(40, 0, 4), (40, 40))

    def test_vlavo_od_ciary_zatoci_doprava(self):
        lave, prave = self.p.vykon_kolies(40, -50, 4, smer=1)
        self.assertGreater(lave, prave)

    def test_otrasy(self):
        o = self.p.Otrasy((0.0, 0.0, 9.8))
        o.pridaj((3.0, 4.0, 9.8))
        o.pridaj((0.0, 0.0, 9.8))
        self.assertAlmostEqual(o.spicka, 5.0)
        self.assertAlmostEqual(o.priemer(), 2.5)

    def test_najlepsi_cas_len_z_uspesnych(self):
        h = [{"cas": 5.0, "uspech": False}, {"cas": 9.0, "uspech": True}]
        self.assertEqual(self.p.najlepsi_cas(h), 9.0)
        self.assertIsNone(self.p.najlepsi_cas([]))


class TestJazda(unittest.TestCase):
    def test_dojde_k_stene_a_zastavi(self):
        sim = Simulacia(stena_cm=100)
        p = nacitaj_program(sim)
        trvanie, otrasy, dovod = p.jazda(p.predvolene_hodnoty())
        self.assertEqual(dovod, "ciel")
        self.assertEqual(sim.vykony[-1], (0, 0))
        self.assertGreater(trvanie, 0)
        self.assertLess(sim.stena - sim.poloha, p.STOP_CM + 1)

    def test_vykon_nikdy_neprekroci_nastavenu_rychlost(self):
        sim = Simulacia()
        p = nacitaj_program(sim)
        h = p.predvolene_hodnoty()
        p.jazda(h)
        self.assertTrue(all(abs(l) <= h["rychlost"] and abs(r) <= h["rychlost"]
                            for l, r in sim.vykony))

    def test_plynuly_rozjazd(self):
        sim = Simulacia(stena_cm=300)
        p = nacitaj_program(sim)
        h = p.predvolene_hodnoty()
        h["rozjazd"] = 2.0
        p.jazda(h)
        jazdne = [l for l, _ in sim.vykony if l > 0]
        # prvá polovica rozjazdu ešte nesmie byť na plnom výkone
        self.assertLess(jazdne[10], h["rychlost"])

    def test_stratena_ciara_zastavi(self):
        sim = Simulacia(ciara=False)
        p = nacitaj_program(sim)
        _, _, dovod = p.jazda(p.predvolene_hodnoty())
        self.assertEqual(dovod, "bez ciary")
        self.assertEqual(sim.vykony[-1], (0, 0))

    def test_rezim_rovno_ignoruje_ciaru(self):
        sim = Simulacia(ciara=False)
        p = nacitaj_program(sim)
        h = p.predvolene_hodnoty()
        h["trasa"] = 1
        _, _, dovod = p.jazda(h)
        self.assertEqual(dovod, "ciel")

    def test_tlacidlo_b_zastavi(self):
        sim = Simulacia(stena_cm=10000)
        p = nacitaj_program(sim)
        povodny_krok = sim.krok

        def krok(dt):
            povodny_krok(dt)
            if sim.cas > 5:
                sim.stlacene.add("b")
        p.sleep = krok
        vysledok = p.jazda(p.predvolene_hodnoty())
        self.assertIsNotNone(vysledok)   # odpočet prebehol pred 5. sekundou
        self.assertEqual(vysledok[2], "stop B")
        self.assertEqual(sim.vykony[-1], (0, 0))

    def test_prekazka_hned_na_starte(self):
        sim = Simulacia(stena_cm=5)
        p = nacitaj_program(sim)
        _, _, dovod = p.jazda(p.predvolene_hodnoty())
        self.assertEqual(dovod, "ciel")
        self.assertTrue(all(v == (0, 0) for v in sim.vykony))


if __name__ == "__main__":
    unittest.main()
