#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

void leds_set_all(uint8_t v);
void leds_set_all_on();
void leds_set_all_off();
uint8_t leds_get_all();

int leds_set(uint8_t led, int v);
int leds_set_on(uint8_t led);
int leds_set_off(uint8_t led);
int leds_toggle(uint8_t led);
int leds_get(uint8_t led);
int leds_blink(uint8_t led, uint32_t delay, int wait_after);

#endif
