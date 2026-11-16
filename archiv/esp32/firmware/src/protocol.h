// JSON správy medzi stránkou a autom. Formát: docs/specifikacia.md, kapitola 6.
#pragma once

#include <cstddef>
#include <cstdint>

#include "control.h"
#include "params.h"

struct MessageResult {
    bool valid;
    bool send_params;  // stránke treba poslať platné parametre
};

MessageResult protocol_handle(const char* data, size_t len, CarState& car, Params& params,
                              uint32_t now_ms);

// Zapíšu správu do `out` ako reťazec a vrátia jej dĺžku.
size_t protocol_state(const CarState& car, char* out, size_t size);
size_t protocol_params(const Params& params, char* out, size_t size);
