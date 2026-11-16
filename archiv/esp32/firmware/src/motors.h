// Motory cez DRV8833.
#pragma once

void motors_init();

// PWM od -255 do 255; záporné znamená dozadu. Pri brake = true motory aktívne brzdia.
void motors_set(int left, int right, bool brake);
