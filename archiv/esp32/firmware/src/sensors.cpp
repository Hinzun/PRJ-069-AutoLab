#include "sensors.h"

#include <Arduino.h>

#include "config.h"
#include "control.h"

namespace {
constexpr unsigned long SENSOR_TIMEOUT_MS = 300;
constexpr int MAX_CM = 400;
constexpr unsigned long US_PER_CM = 58;  // ozvena prejde dráhu tam aj späť

volatile unsigned long echo_start_us = 0;
volatile unsigned long echo_length_us = 0;
volatile bool echo_done = false;

unsigned long last_measure_ms = 0;
unsigned long last_echo_ms = 0;
int distance_cm = NO_DISTANCE;

void ARDUINO_ISR_ATTR on_echo() {
    const unsigned long now = micros();
    if (digitalRead(PIN_ECHO) == HIGH) {
        echo_start_us = now;
    } else {
        echo_length_us = now - echo_start_us;
        echo_done = true;
    }
}
}  // namespace

void sensors_init() {
    pinMode(PIN_TRIG, OUTPUT);
    digitalWrite(PIN_TRIG, LOW);
    pinMode(PIN_ECHO, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN_ECHO), on_echo, CHANGE);
}

void sensors_tick(unsigned long now_ms) {
    if (now_ms - last_measure_ms < SENSOR_PERIOD_MS) return;
    last_measure_ms = now_ms;

    if (echo_done) {
        noInterrupts();
        const unsigned long length_us = echo_length_us;
        echo_done = false;
        interrupts();
        const unsigned long cm = length_us / US_PER_CM;
        distance_cm = cm > MAX_CM ? MAX_CM : static_cast<int>(cm);
        last_echo_ms = now_ms;
    } else if (now_ms - last_echo_ms > SENSOR_TIMEOUT_MS) {
        distance_cm = NO_DISTANCE;
    }

    // Nové meranie spustíme, len ak predošlá ozvena skončila.
    if (digitalRead(PIN_ECHO) == LOW) {
        digitalWrite(PIN_TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(PIN_TRIG, LOW);
    }
}

int sensors_distance_cm() {
    return distance_cm;
}
