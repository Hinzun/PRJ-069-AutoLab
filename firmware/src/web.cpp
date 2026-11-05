#include "web.h"

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <WiFi.h>

#include <cstring>

#include "config.h"
#include "protocol.h"

namespace {
constexpr size_t MAX_MESSAGE_LEN = 96;
constexpr int QUEUE_LENGTH = 16;
constexpr unsigned long CLEANUP_PERIOD_MS = 1000;

struct RawMessage {
    uint16_t len;
    char data[MAX_MESSAGE_LEN];
};

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
QueueHandle_t queue = nullptr;
volatile bool params_pending = false;
unsigned long last_cleanup_ms = 0;

// Beží v úlohe webservera, nie v loop(). Správu preto len odloží do frontu.
void on_ws_event(AsyncWebSocket*, AsyncWebSocketClient*, AwsEventType type, void* arg,
                 uint8_t* data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        params_pending = true;
        return;
    }
    if (type != WS_EVT_DATA) return;

    const AwsFrameInfo* info = static_cast<AwsFrameInfo*>(arg);
    const bool whole_text_frame =
        info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT;
    if (!whole_text_frame || len > MAX_MESSAGE_LEN) return;

    RawMessage message;
    message.len = static_cast<uint16_t>(len);
    std::memcpy(message.data, data, len);
    xQueueSend(queue, &message, 0);
}
}  // namespace

void web_init() {
    queue = xQueueCreate(QUEUE_LENGTH, sizeof(RawMessage));

    WiFi.mode(WIFI_AP);
    const String ssid = String("AutoLab-") + CAR_ID;
    if (!WiFi.softAP(ssid.c_str(), nullptr, WIFI_CHANNEL)) {
        Serial.println("Chyba: Wi-Fi sieť sa nepodarilo vytvoriť");
    }
    WiFi.setSleep(false);  // menšie oneskorenie povelov
    Serial.printf("Wi-Fi %s, kanál %d, adresa %s\n", ssid.c_str(), WIFI_CHANNEL,
                  WiFi.softAPIP().toString().c_str());

    if (!LittleFS.begin(true)) Serial.println("Chyba: LittleFS sa nepodarilo pripojiť");

    ws.onEvent(on_ws_event);
    server.addHandler(&ws);
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
    server.onNotFound([](AsyncWebServerRequest* request) {
        request->send(404, "text/plain; charset=utf-8",
                      "Stránka nie je v aute. Nahraj ju: pio run -t uploadfs");
    });
    server.begin();
}

void web_process_messages(CarState& car, Params& params, unsigned long now_ms) {
    RawMessage message;
    while (xQueueReceive(queue, &message, 0) == pdTRUE) {
        const MessageResult result =
            protocol_handle(message.data, message.len, car, params, now_ms);
        if (result.send_params) params_pending = true;
    }
}

void web_send_state(const CarState& car) {
    if (ws.count() == 0 || !ws.availableForWriteAll()) return;
    char buffer[128];
    const size_t len = protocol_state(car, buffer, sizeof(buffer));
    ws.textAll(buffer, len);
}

void web_send_params_if_needed(const Params& params) {
    if (!params_pending || ws.count() == 0 || !ws.availableForWriteAll()) return;
    params_pending = false;
    char buffer[96];
    const size_t len = protocol_params(params, buffer, sizeof(buffer));
    ws.textAll(buffer, len);
}

void web_cleanup(unsigned long now_ms) {
    if (now_ms - last_cleanup_ms < CLEANUP_PERIOD_MS) return;
    last_cleanup_ms = now_ms;
    ws.cleanupClients();
}
