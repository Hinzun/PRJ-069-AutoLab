// Testy logiky bez ESP32: pio test -e native
#include <unity.h>

#include <cstring>

#include "control.h"
#include "params.h"
#include "protocol.h"

namespace {
Params params;
CarState car;

MessageResult send(const char* json, uint32_t now_ms = 0) {
    return protocol_handle(json, std::strlen(json), car, params, now_ms);
}

void drive_forward_at(uint32_t now_ms) {
    send("{\"type\":\"mode\",\"value\":\"manual\"}", now_ms);
    send("{\"type\":\"drive\",\"x\":0,\"y\":1}", now_ms);
}
}  // namespace

void setUp() {
    params_reset(params);
    car_init(car);
}

void tearDown() {}

// --- parametre ---

void test_params_defaults() {
    TEST_ASSERT_EQUAL(200, params.max_pwm);
    TEST_ASSERT_EQUAL(0, params.trim);
    TEST_ASSERT_EQUAL(20, params.stop_cm);
}

void test_params_accept_range_limits() {
    TEST_ASSERT_TRUE(params_set(params, "max_pwm", 50));
    TEST_ASSERT_EQUAL(50, params.max_pwm);
    TEST_ASSERT_TRUE(params_set(params, "trim", -30));
    TEST_ASSERT_EQUAL(-30, params.trim);
}

void test_params_reject_out_of_range_and_keep_value() {
    TEST_ASSERT_FALSE(params_set(params, "stop_cm", 4));
    TEST_ASSERT_FALSE(params_set(params, "stop_cm", 51));
    TEST_ASSERT_EQUAL(20, params.stop_cm);
}

void test_params_reject_unknown_key() {
    TEST_ASSERT_FALSE(params_set(params, "nieco", 10));
    TEST_ASSERT_FALSE(params_set(params, nullptr, 10));
}

// --- prepočet joysticku ---

void test_mix_forward_uses_max_pwm() {
    const Wheels w = control_mix(0, 1, params);
    TEST_ASSERT_EQUAL(200, w.l);
    TEST_ASSERT_EQUAL(200, w.r);
    TEST_ASSERT_TRUE(w.forward);
}

void test_mix_center_with_trim_stands_still() {
    params.trim = 20;
    const Wheels w = control_mix(0, 0, params);
    TEST_ASSERT_EQUAL(0, w.l);
    TEST_ASSERT_EQUAL(0, w.r);
}

void test_mix_deadzone() {
    const Wheels w = control_mix(0.04f, -0.04f, params);
    TEST_ASSERT_EQUAL(0, w.l);
    TEST_ASSERT_EQUAL(0, w.r);
}

void test_trim_forward() {
    params.trim = 10;
    const Wheels w = control_mix(0, 1, params);
    TEST_ASSERT_EQUAL(210, w.l);
    TEST_ASSERT_EQUAL(190, w.r);
}

void test_trim_acts_the_same_in_reverse() {
    params.trim = 10;
    const Wheels w = control_mix(0, -1, params);
    TEST_ASSERT_EQUAL(-210, w.l);
    TEST_ASSERT_EQUAL(-190, w.r);
}

void test_trim_never_flips_direction() {
    params.trim = 30;
    const Wheels w = control_mix(0, 0.1f, params);  // pravé koleso 20 PWM − 30
    TEST_ASSERT_EQUAL(0, w.r);
}

void test_trim_does_not_start_standing_wheel() {
    params.trim = 30;
    const Wheels w = control_mix(0.5f, 0.5f, params);  // pravé koleso stojí
    TEST_ASSERT_EQUAL(0, w.r);
}

void test_output_is_clipped() {
    params.max_pwm = 255;
    params.trim = 30;
    const Wheels w = control_mix(0, 1, params);
    TEST_ASSERT_EQUAL(255, w.l);
}

// --- rampa ---

void test_ramp_limits_acceleration() {
    TEST_ASSERT_EQUAL(15, control_ramp(0, 200, 15));
    TEST_ASSERT_EQUAL(-15, control_ramp(0, -200, 15));
    TEST_ASSERT_EQUAL(200, control_ramp(190, 200, 15));
}

void test_ramp_slows_down_immediately() {
    TEST_ASSERT_EQUAL(50, control_ramp(200, 50, 15));
    TEST_ASSERT_EQUAL(0, control_ramp(200, 0, 15));
}

void test_ramp_direction_change_goes_through_zero() {
    TEST_ASSERT_EQUAL(0, control_ramp(200, -200, 15));
    TEST_ASSERT_EQUAL(0, control_ramp(-200, 200, 15));
}

// --- režimy a bezpečnosť ---

void test_starts_in_stop_and_ignores_drive() {
    send("{\"type\":\"drive\",\"x\":0,\"y\":1}");
    car_tick(car, params, 100, 20);
    TEST_ASSERT_TRUE(car.mode == Mode::Stop);
    TEST_ASSERT_EQUAL(0, car.pwm_l);
    TEST_ASSERT_TRUE(car.brake);
}

void test_manual_drives_with_ramp() {
    drive_forward_at(0);
    car_tick(car, params, 100, 20);
    TEST_ASSERT_EQUAL(RAMP_STEP, car.pwm_l);
    TEST_ASSERT_FALSE(car.brake);
}

void test_mode_change_clears_old_joystick_command() {
    drive_forward_at(0);
    send("{\"type\":\"stop\"}");
    send("{\"type\":\"mode\",\"value\":\"manual\"}");
    car_tick(car, params, 100, 20);
    TEST_ASSERT_EQUAL(0, car.pwm_l);
}

void test_obstacle_brakes_forward_without_changing_mode() {
    drive_forward_at(0);
    car_tick(car, params, 10, 20);
    TEST_ASSERT_TRUE(car.blocked);
    TEST_ASSERT_TRUE(car.brake);
    TEST_ASSERT_EQUAL(0, car.pwm_l);
    TEST_ASSERT_TRUE(car.mode == Mode::Manual);
}

void test_obstacle_exactly_at_stop_cm_does_not_block() {
    drive_forward_at(0);
    car_tick(car, params, params.stop_cm, 20);
    TEST_ASSERT_FALSE(car.blocked);
}

void test_obstacle_allows_reverse() {
    send("{\"type\":\"mode\",\"value\":\"manual\"}");
    send("{\"type\":\"drive\",\"x\":0,\"y\":-1}");
    car_tick(car, params, 10, 20);
    TEST_ASSERT_FALSE(car.brake);
    TEST_ASSERT_EQUAL(-RAMP_STEP, car.pwm_l);
}

void test_obstacle_allows_spin_even_with_trim() {
    params.trim = 30;
    send("{\"type\":\"mode\",\"value\":\"manual\"}");
    send("{\"type\":\"drive\",\"x\":1,\"y\":0}");
    car_tick(car, params, 10, 20);
    TEST_ASSERT_FALSE(car.brake);
}

void test_drive_continues_after_obstacle_is_gone() {
    drive_forward_at(0);
    car_tick(car, params, 10, 20);
    car_tick(car, params, 100, 40);
    TEST_ASSERT_FALSE(car.brake);
    TEST_ASSERT_EQUAL(RAMP_STEP, car.pwm_l);
}

void test_missing_distance_does_not_block() {
    drive_forward_at(0);
    car_tick(car, params, NO_DISTANCE, 20);
    TEST_ASSERT_FALSE(car.blocked);
    TEST_ASSERT_FALSE(car.brake);
}

void test_watchdog_stops_after_one_second() {
    drive_forward_at(0);
    car_tick(car, params, 100, 999);
    TEST_ASSERT_TRUE(car.mode == Mode::Manual);
    car_tick(car, params, 100, 1000);
    TEST_ASSERT_TRUE(car.mode == Mode::Stop);
    TEST_ASSERT_TRUE(car.brake);
}

void test_ping_keeps_connection_alive() {
    drive_forward_at(0);
    send("{\"type\":\"ping\"}", 900);
    car_tick(car, params, 100, 1500);
    TEST_ASSERT_TRUE(car.mode == Mode::Manual);
}

void test_watchdog_handles_millis_overflow() {
    drive_forward_at(0xFFFFFF00u);
    car_tick(car, params, 100, 0x00000010u);  // ubehlo len 272 ms
    TEST_ASSERT_TRUE(car.mode == Mode::Manual);
}

void test_after_watchdog_car_stays_stopped_when_page_returns() {
    drive_forward_at(0);
    car_tick(car, params, 100, 1000);
    send("{\"type\":\"drive\",\"x\":0,\"y\":1}", 1100);
    car_tick(car, params, 100, 1120);
    TEST_ASSERT_TRUE(car.mode == Mode::Stop);
    TEST_ASSERT_EQUAL(0, car.pwm_l);
}

// --- JSON protokol ---

void test_protocol_set_valid_value() {
    const MessageResult r = send("{\"type\":\"set\",\"key\":\"stop_cm\",\"value\":30}");
    TEST_ASSERT_TRUE(r.send_params);
    TEST_ASSERT_EQUAL(30, params.stop_cm);
}

void test_protocol_set_out_of_range_sends_params_back() {
    const MessageResult r = send("{\"type\":\"set\",\"key\":\"stop_cm\",\"value\":999}");
    TEST_ASSERT_TRUE(r.send_params);
    TEST_ASSERT_EQUAL(20, params.stop_cm);
}

void test_protocol_set_without_number_changes_nothing() {
    const MessageResult r = send("{\"type\":\"set\",\"key\":\"stop_cm\",\"value\":\"x\"}");
    TEST_ASSERT_TRUE(r.send_params);
    TEST_ASSERT_EQUAL(20, params.stop_cm);
}

void test_protocol_defaults() {
    params.max_pwm = 100;
    const MessageResult r = send("{\"type\":\"defaults\"}");
    TEST_ASSERT_TRUE(r.send_params);
    TEST_ASSERT_EQUAL(200, params.max_pwm);
}

void test_protocol_invalid_json_does_not_refresh_watchdog() {
    drive_forward_at(0);
    const MessageResult r = send("{nie je json", 900);
    TEST_ASSERT_FALSE(r.valid);
    car_tick(car, params, 100, 1000);
    TEST_ASSERT_TRUE(car.mode == Mode::Stop);
}

void test_protocol_rejects_line_mode() {
    const MessageResult r = send("{\"type\":\"mode\",\"value\":\"line\"}");
    TEST_ASSERT_FALSE(r.valid);
    TEST_ASSERT_TRUE(car.mode == Mode::Stop);
}

void test_protocol_drive_without_numbers_is_ignored() {
    drive_forward_at(0);
    const MessageResult r = send("{\"type\":\"drive\",\"x\":\"a\",\"y\":0}");
    TEST_ASSERT_FALSE(r.valid);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, car.y);
}

void test_protocol_state_format() {
    car.mode = Mode::Manual;
    car.cm = 42;
    car.pwm_l = 150;
    car.pwm_r = 140;
    char out[128];
    protocol_state(car, out, sizeof(out));
    TEST_ASSERT_EQUAL_STRING(
        "{\"type\":\"state\",\"mode\":\"MANUAL\",\"cm\":42,\"blocked\":false,"
        "\"pwmL\":150,\"pwmR\":140}",
        out);
}

void test_protocol_params_format() {
    char out[96];
    protocol_params(params, out, sizeof(out));
    TEST_ASSERT_EQUAL_STRING("{\"type\":\"params\",\"max_pwm\":200,\"trim\":0,\"stop_cm\":20}",
                             out);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_params_defaults);
    RUN_TEST(test_params_accept_range_limits);
    RUN_TEST(test_params_reject_out_of_range_and_keep_value);
    RUN_TEST(test_params_reject_unknown_key);
    RUN_TEST(test_mix_forward_uses_max_pwm);
    RUN_TEST(test_mix_center_with_trim_stands_still);
    RUN_TEST(test_mix_deadzone);
    RUN_TEST(test_trim_forward);
    RUN_TEST(test_trim_acts_the_same_in_reverse);
    RUN_TEST(test_trim_never_flips_direction);
    RUN_TEST(test_trim_does_not_start_standing_wheel);
    RUN_TEST(test_output_is_clipped);
    RUN_TEST(test_ramp_limits_acceleration);
    RUN_TEST(test_ramp_slows_down_immediately);
    RUN_TEST(test_ramp_direction_change_goes_through_zero);
    RUN_TEST(test_starts_in_stop_and_ignores_drive);
    RUN_TEST(test_manual_drives_with_ramp);
    RUN_TEST(test_mode_change_clears_old_joystick_command);
    RUN_TEST(test_obstacle_brakes_forward_without_changing_mode);
    RUN_TEST(test_obstacle_exactly_at_stop_cm_does_not_block);
    RUN_TEST(test_obstacle_allows_reverse);
    RUN_TEST(test_obstacle_allows_spin_even_with_trim);
    RUN_TEST(test_drive_continues_after_obstacle_is_gone);
    RUN_TEST(test_missing_distance_does_not_block);
    RUN_TEST(test_watchdog_stops_after_one_second);
    RUN_TEST(test_ping_keeps_connection_alive);
    RUN_TEST(test_watchdog_handles_millis_overflow);
    RUN_TEST(test_after_watchdog_car_stays_stopped_when_page_returns);
    RUN_TEST(test_protocol_set_valid_value);
    RUN_TEST(test_protocol_set_out_of_range_sends_params_back);
    RUN_TEST(test_protocol_set_without_number_changes_nothing);
    RUN_TEST(test_protocol_defaults);
    RUN_TEST(test_protocol_invalid_json_does_not_refresh_watchdog);
    RUN_TEST(test_protocol_rejects_line_mode);
    RUN_TEST(test_protocol_drive_without_numbers_is_ignored);
    RUN_TEST(test_protocol_state_format);
    RUN_TEST(test_protocol_params_format);
    return UNITY_END();
}
