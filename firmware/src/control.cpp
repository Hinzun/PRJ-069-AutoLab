#include "control.h"

#include <cmath>

namespace {
float clamp1(float v) {
    if (v > 1.0f) return 1.0f;
    if (v < -1.0f) return -1.0f;
    return v;
}

float apply_deadzone(float v) {
    return std::fabs(v) < DEADZONE ? 0.0f : v;
}

// Trim mení silu kolesa, nie smer: v oboch smeroch jazdy pôsobí rovnako
// a koleso, ktoré má stáť, nerozbehne.
int apply_trim(int pwm, int trim) {
    if (pwm == 0) return 0;
    int magnitude = (pwm > 0 ? pwm : -pwm) + trim;
    if (magnitude < 0) magnitude = 0;
    if (magnitude > 255) magnitude = 255;
    return pwm > 0 ? magnitude : -magnitude;
}
}  // namespace

Wheels control_mix(float x, float y, const Params& p) {
    x = apply_deadzone(clamp1(x));
    y = apply_deadzone(clamp1(y));
    const float left = clamp1(y + x);
    const float right = clamp1(y - x);
    const int l = static_cast<int>(std::lround(left * p.max_pwm));
    const int r = static_cast<int>(std::lround(right * p.max_pwm));
    return {apply_trim(l, p.trim), apply_trim(r, -p.trim), left + right > 0.0f};
}

int control_ramp(int current, int target, int step) {
    if (target == 0) return 0;
    // Zmena smeru ide cez nulu.
    if ((current > 0 && target < 0) || (current < 0 && target > 0)) return 0;
    if (target > 0) {
        if (target <= current) return target;  // spomaľovanie je okamžité
        return current + step > target ? target : current + step;
    }
    if (target >= current) return target;
    return current - step < target ? target : current - step;
}

void car_init(CarState& s) {
    s = CarState{Mode::Stop, 0.0f, 0.0f, 0, NO_DISTANCE, false, 0, 0, true};
}

void car_message_received(CarState& s, uint32_t now_ms) {
    s.last_msg_ms = now_ms;
}

void car_set_mode(CarState& s, Mode mode) {
    s.mode = mode;
    // Po zmene režimu auto nesmie pokračovať podľa starého povelu joysticku.
    s.x = 0.0f;
    s.y = 0.0f;
}

void car_drive(CarState& s, float x, float y) {
    if (s.mode != Mode::Manual) return;
    s.x = clamp1(x);
    s.y = clamp1(y);
}

void car_tick(CarState& s, const Params& p, int cm, uint32_t now_ms) {
    s.cm = cm;
    s.blocked = cm != NO_DISTANCE && cm < p.stop_cm;

    if (s.mode != Mode::Stop && now_ms - s.last_msg_ms >= WATCHDOG_MS) {
        car_set_mode(s, Mode::Stop);
    }

    if (s.mode == Mode::Stop) {
        s.pwm_l = 0;
        s.pwm_r = 0;
        s.brake = true;
        return;
    }

    const Wheels target = control_mix(s.x, s.y, p);
    if (s.blocked && target.forward) {
        s.pwm_l = 0;
        s.pwm_r = 0;
        s.brake = true;
        return;
    }

    s.pwm_l = control_ramp(s.pwm_l, target.l, RAMP_STEP);
    s.pwm_r = control_ramp(s.pwm_r, target.r, RAMP_STEP);
    s.brake = false;
}
