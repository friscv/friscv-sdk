#ifndef RGB_H
#define RGB_H

#include <stdint.h>

#define RGB_OFF     0x00
#define RGB_RED     0x01
#define RGB_GREEN   0x02
#define RGB_BLUE    0x04
#define RGB_YELLOW  0x03
#define RGB_CYAN    0x06
#define RGB_MAGENTA 0x05
#define RGB_WHITE   0x07

void rgb_set_all(uint8_t color);
void rgb_set_all_on();
void rgb_set_all_off();
uint8_t rgb_get_all();

int rgb_set(uint8_t ch, int v);
int rgb_set_on(uint8_t ch);
int rgb_set_off(uint8_t ch);
int rgb_toggle(uint8_t ch);
int rgb_get(uint8_t ch);
int rgb_blink(uint8_t ch, uint32_t delay, int wait_after);

void rgb_set_color(uint8_t color);
void rgb_blink_color(uint8_t color, uint32_t delay, int wait_after);

#endif