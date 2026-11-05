// AutoLab: hlavná slučka. Nikdy neblokuje, úlohy spúšťa podľa millis().
#include <Arduino.h>

#include "config.h"
#include "control.h"
#include "motors.h"
#include "params.h"
#include "sensors.h"
#include "web.h"

namespace {
CarState car;
Params params;
unsigned long last_control_ms = 0;
unsigned long last_state_ms = 0;
}  // namespace

void setup() {
    // Motory ako prvé, aby auto po zapnutí stálo.
    motors_init();
    motors_set(0, 0, true);

    Serial.begin(115200);
    params_reset(params);
    car_init(car);
    sensors_init();
    web_init();
}

void loop() {
    const unsigned long now = millis();

    sensors_tick(now);
    web_process_messages(car, params, now);

    if (now - last_control_ms >= CONTROL_PERIOD_MS) {
        last_control_ms = now;
        car_tick(car, params, sensors_distance_cm(), now);
        motors_set(car.pwm_l, car.pwm_r, car.brake);
    }

    web_send_params_if_needed(params);

    if (now - last_state_ms >= STATE_PERIOD_MS) {
        last_state_ms = now;
        web_send_state(car);
    }

    web_cleanup(now);
}
