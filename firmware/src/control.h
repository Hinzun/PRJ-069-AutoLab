// Režimy, bezpečnosť a prepočet joysticku na motory. Bez závislosti od Arduina,
// aby sa to dalo testovať na PC (firmware/test).
#pragma once

#include <cstdint>

#include "params.h"

enum class Mode { Stop, Manual };

constexpr uint32_t WATCHDOG_MS = 1000;  // STOP po 1 s bez správy zo stránky
constexpr int RAMP_STEP = 15;           // nárast PWM za 20 ms, 0 → 255 za asi 0,35 s
constexpr float DEADZONE = 0.05f;       // okolie stredu joysticku, kde auto stojí
constexpr int NO_DISTANCE = -1;         // senzor neodpovedá

struct Wheels {
    int l;
    int r;
    bool forward;  // joystick velí jazdu dopredu (pred pripočítaním trim)
};

struct CarState {
    Mode mode;
    float x;
    float y;
    uint32_t last_msg_ms;
    int cm;        // posledná vzdialenosť, NO_DISTANCE ak nie je k dispozícii
    bool blocked;  // prekážka bližšie ako stop_cm
    int pwm_l;
    int pwm_r;
    bool brake;  // motory aktívne brzdia
};

Wheels control_mix(float x, float y, const Params& p);
int control_ramp(int current, int target, int step);

void car_init(CarState& s);
void car_message_received(CarState& s, uint32_t now_ms);
void car_set_mode(CarState& s, Mode mode);
void car_drive(CarState& s, float x, float y);
void car_tick(CarState& s, const Params& p, int cm, uint32_t now_ms);
