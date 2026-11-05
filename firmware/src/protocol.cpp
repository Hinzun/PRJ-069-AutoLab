#include "protocol.h"

#include <ArduinoJson.h>

#include <cstring>

MessageResult protocol_handle(const char* data, size_t len, CarState& car, Params& params,
                              uint32_t now_ms) {
    JsonDocument doc;
    if (deserializeJson(doc, data, len) != DeserializationError::Ok) return {false, false};
    const char* type = doc["type"];
    if (type == nullptr) return {false, false};

    car_message_received(car, now_ms);

    if (std::strcmp(type, "ping") == 0) return {true, false};

    if (std::strcmp(type, "drive") == 0) {
        if (!doc["x"].is<float>() || !doc["y"].is<float>()) return {false, false};
        car_drive(car, doc["x"].as<float>(), doc["y"].as<float>());
        return {true, false};
    }

    if (std::strcmp(type, "stop") == 0) {
        car_set_mode(car, Mode::Stop);
        return {true, false};
    }

    if (std::strcmp(type, "mode") == 0) {
        const char* value = doc["value"];
        if (value == nullptr) return {false, false};
        if (std::strcmp(value, "stop") == 0) {
            car_set_mode(car, Mode::Stop);
        } else if (std::strcmp(value, "manual") == 0) {
            car_set_mode(car, Mode::Manual);
        } else {
            return {false, false};  // LINE zatiaľ nie je implementovaný
        }
        return {true, false};
    }

    if (std::strcmp(type, "set") == 0) {
        // Aj po odmietnutí pošleme späť platné hodnoty, aby sa stránka vrátila na ne.
        if (doc["value"].is<double>()) {
            params_set(params, doc["key"], doc["value"].as<double>());
        }
        return {true, true};
    }

    if (std::strcmp(type, "defaults") == 0) {
        params_reset(params);
        return {true, true};
    }

    return {false, false};
}

size_t protocol_state(const CarState& car, char* out, size_t size) {
    JsonDocument doc;
    doc["type"] = "state";
    doc["mode"] = car.mode == Mode::Manual ? "MANUAL" : "STOP";
    doc["cm"] = car.cm;
    doc["blocked"] = car.blocked;
    doc["pwmL"] = car.pwm_l;
    doc["pwmR"] = car.pwm_r;
    return serializeJson(doc, out, size);
}

size_t protocol_params(const Params& params, char* out, size_t size) {
    JsonDocument doc;
    doc["type"] = "params";
    doc["max_pwm"] = params.max_pwm;
    doc["trim"] = params.trim;
    doc["stop_cm"] = params.stop_cm;
    return serializeJson(doc, out, size);
}
