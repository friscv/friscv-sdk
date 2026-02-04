#include <stdint.h>

#define LEDS_BASE  (*(volatile uint32_t *)0x40000000)

void leds_set_all(uint8_t v) {
    LEDS_BASE = v & 0x0F;
}

void leds_set_all_on() {
    LEDS_BASE = 0x0F;
}

void leds_set_all_off() {
    LEDS_BASE = 0x00;
}

uint8_t leds_get_all() {
    return LEDS_BASE;
}

int leds_check_idx(uint8_t led) {
    if (led < 0 || led >= 4) {
        return -1;
    }
    return 0;
}

void leds_set_nocheck(uint8_t led, int v) {
    if (v != 0) {
        LEDS_BASE |= (1 << led);
    } else {
        LEDS_BASE &= ~(1 << led);
    }
    return 0;
}

int leds_set(uint8_t led, int v) {
    if (leds_check_idx(led)) {
        return -1;
    }
    leds_set_nocheck(led, v);
    return 0;
}

int leds_set_on(uint8_t led) {
    return leds_set(led, 1);
}

int leds_set_off(uint8_t led) {
    return leds_set(led, 0);
}

void leds_toggle_nocheck(uint8_t led) {
    leds_set_nocheck(led, !leds_get_nocheck(led));
}

int leds_toggle(uint8_t led) {
    if (leds_check_idx(led)) {
        return -1;
    }
    leds_toggle_nocheck(led);
    return 0;
}

int leds_get_nocheck(uint8_t led) {
    return (LEDS_BASE >> led) & 0x1;
}

int leds_get(uint8_t led) {
    if (leds_check_idx(led)) {
        return -1;
    }
    return leds_get_nocheck(led);
}

void wait_cycles(volatile uint32_t delay) {
    for (int i = 0; i < delay; i++);
}

int leds_blink(uint8_t led, uint32_t delay, int wait_after) {
    if (leds_check_idx(led)) {
        return -1;
    }
    leds_toggle_nocheck(led);
    wait_cycles(delay);
    leds_toggle_nocheck(led);
    if (wait_after) {
        wait_cycles(delay);
    }
    return 0;
}
