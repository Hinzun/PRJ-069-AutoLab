#include "params.h"

#include <cmath>
#include <cstring>

namespace {
struct Range {
    const char* key;
    int Params::*field;
    int min;
    int max;
    int def;
};

const Range RANGES[] = {
    {"max_pwm", &Params::max_pwm, 50, 255, 200},
    {"trim", &Params::trim, -30, 30, 0},
    {"stop_cm", &Params::stop_cm, 5, 50, 20},
};
}  // namespace

void params_reset(Params& p) {
    for (const Range& r : RANGES) p.*(r.field) = r.def;
}

bool params_set(Params& p, const char* key, double value) {
    if (key == nullptr) return false;
    for (const Range& r : RANGES) {
        if (std::strcmp(key, r.key) != 0) continue;
        // Takto zapísaná podmienka odmietne aj NaN.
        if (!(value >= r.min && value <= r.max)) return false;
        p.*(r.field) = static_cast<int>(std::lround(value));
        return true;
    }
    return false;
}
