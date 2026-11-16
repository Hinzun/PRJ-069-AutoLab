// Wi-Fi access point, webserver a WebSocket.
#pragma once

#include "control.h"
#include "params.h"

void web_init();

// Spracuje správy zo stránky. Volá sa z loop(), takže stav auta mení iba hlavná slučka.
void web_process_messages(CarState& car, Params& params, unsigned long now_ms);

void web_send_state(const CarState& car);
void web_send_params_if_needed(const Params& params);

// Upratuje odpojených klientov. Volá sa pravidelne z loop().
void web_cleanup(unsigned long now_ms);
