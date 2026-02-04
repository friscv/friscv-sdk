#include <stdint.h>

// Stub LED driver for platforms without LEDs
// All functions are no-ops

void leds_set_all(uint8_t v) {
    (void)v;
}

void leds_set_all_on() {
}

void leds_set_all_off() {
}

uint8_t leds_get_all() {
    return 0;
}

int leds_set(uint8_t led, int v) {
    (void)led;
    (void)v;
    return 0;
}

int leds_set_on(uint8_t led) {
    (void)led;
    return 0;
}

int leds_set_off(uint8_t led) {
    (void)led;
    return 0;
}

int leds_toggle(uint8_t led) {
    (void)led;
    return 0;
}

int leds_get(uint8_t led) {
    (void)led;
    return 0;
}

int leds_blink(uint8_t led, uint32_t delay, int wait_after) {
    (void)led;
    (void)delay;
    (void)wait_after;
    return 0;
}
