#include <stdint.h>

#define RGB_BASE  (*(volatile uint32_t *)0x40020000)

void rgb_set_all(uint8_t color) {
    RGB_BASE = color & 0x07;
}

void rgb_set_all_on() {
    RGB_BASE = 0x07;
}

void rgb_set_all_off() {
    RGB_BASE = 0x00;
}

uint8_t rgb_get_all() {
    return RGB_BASE & 0x07;
}

int rgb_check_idx(uint8_t ch) {
    if (ch >= 3) {
        return -1;
    }
    return 0;
}

void rgb_set_nocheck(uint8_t ch, int v) {
    if (v != 0) {
        RGB_BASE |= (1 << ch);
    } else {
        RGB_BASE &= ~(1 << ch);
    }
}

int rgb_set(uint8_t ch, int v) {
    if (rgb_check_idx(ch)) {
        return -1;
    }
    rgb_set_nocheck(ch, v);
    return 0;
}

int rgb_set_on(uint8_t ch) {
    return rgb_set(ch, 1);
}

int rgb_set_off(uint8_t ch) {
    return rgb_set(ch, 0);
}

int rgb_get_nocheck(uint8_t ch) {
    return (RGB_BASE >> ch) & 0x1;
}

void rgb_toggle_nocheck(uint8_t ch) {
    rgb_set_nocheck(ch, !rgb_get_nocheck(ch));
}

int rgb_toggle(uint8_t ch) {
    if (rgb_check_idx(ch)) {
        return -1;
    }
    rgb_toggle_nocheck(ch);
    return 0;
}

int rgb_get(uint8_t ch) {
    if (rgb_check_idx(ch)) {
        return -1;
    }
    return rgb_get_nocheck(ch);
}

void rgb_set_color(uint8_t color) {
    RGB_BASE = color & 0x07;
}

static void wait_cycles(volatile uint32_t delay) {
    for (uint32_t i = 0; i < delay; i++);
}

int rgb_blink(uint8_t ch, uint32_t delay, int wait_after) {
    if (rgb_check_idx(ch)) {
        return -1;
    }
    rgb_toggle_nocheck(ch);
    wait_cycles(delay);
    rgb_toggle_nocheck(ch);
    if (wait_after) {
        wait_cycles(delay);
    }
    return 0;
}

void rgb_blink_color(uint8_t color, uint32_t delay, int wait_after) {
    RGB_BASE = color & 0x07;
    wait_cycles(delay);
    RGB_BASE = 0x00;
    if (wait_after) {
        wait_cycles(delay);
    }
}