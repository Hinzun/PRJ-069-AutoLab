// Piny a periódy úloh. Zapojenie: docs/navrh-zadania.md, kapitola 6.
#pragma once

#ifndef CAR_ID
#define CAR_ID 1
#endif
#ifndef WIFI_CHANNEL
#define WIFI_CHANNEL 1
#endif

constexpr int PIN_AIN1 = 25;  // motor L
constexpr int PIN_AIN2 = 26;
constexpr int PIN_BIN1 = 32;  // motor R
constexpr int PIN_BIN2 = 33;
constexpr int PIN_TRIG = 5;
constexpr int PIN_ECHO = 18;

constexpr unsigned long CONTROL_PERIOD_MS = 20;  // 50 Hz
constexpr unsigned long SENSOR_PERIOD_MS = 60;
constexpr unsigned long STATE_PERIOD_MS = 100;
