#include "motors.h"

#include <Arduino.h>

#include "config.h"

namespace {
constexpr int PWM_FREQ_HZ = 5000;
constexpr int PWM_BITS = 8;
constexpr int CHANNELS[4] = {0, 1, 2, 3};

void write_motor(int channel1, int channel2, int pwm) {
    ledcWrite(channel1, pwm > 0 ? pwm : 0);
    ledcWrite(channel2, pwm < 0 ? -pwm : 0);
}
}  // namespace

void motors_init() {
    const int pins[4] = {PIN_AIN1, PIN_AIN2, PIN_BIN1, PIN_BIN2};
    for (int i = 0; i < 4; i++) {
        ledcSetup(CHANNELS[i], PWM_FREQ_HZ, PWM_BITS);
        ledcWrite(CHANNELS[i], 0);
        ledcAttachPin(pins[i], CHANNELS[i]);
    }
}

void motors_set(int left, int right, bool brake) {
    if (brake) {
        // DRV8833: oba vstupy motora na HIGH znamenajú brzdenie.
        for (int channel : CHANNELS) ledcWrite(channel, 255);
        return;
    }
    write_motor(CHANNELS[0], CHANNELS[1], left);
    write_motor(CHANNELS[2], CHANNELS[3], right);
}
