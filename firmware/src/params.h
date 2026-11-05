// Parametre nastaviteľné zo stránky. Rozsahy: docs/specifikacia.md, kapitola 7.
#pragma once

struct Params {
    int max_pwm;
    int trim;
    int stop_cm;
};

void params_reset(Params& p);

// Nastaví parameter. Neznámy kľúč alebo hodnotu mimo rozsahu odmietne (vráti false)
// a pôvodnú hodnotu nechá.
bool params_set(Params& p, const char* key, double value);
