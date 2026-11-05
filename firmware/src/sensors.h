// Ultrazvukový senzor vzdialenosti (HC-SR04). Meria cez prerušenie, slučku neblokuje.
#pragma once

void sensors_init();
void sensors_tick(unsigned long now_ms);

// Posledná vzdialenosť v cm, alebo NO_DISTANCE, ak senzor dlhšie neodpovedá.
int sensors_distance_cm();
