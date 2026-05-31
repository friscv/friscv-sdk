#include "rgb_leds.h"

#define DELAY 1000000

void wait(volatile uint32_t d) {
    for (volatile uint32_t i = 0; i < d; i++);
}

int main(void) {

    //test rgb_set_all_off
    rgb_set_all_off();
    wait(DELAY);

    //test rgb_set_all_on
    rgb_set_all_on();
    wait(DELAY);

    //test rgb_set_all
    rgb_set_all(0x05);
    wait(DELAY);

    rgb_set_all_off();
    wait(DELAY);

    //test rgb_set_color
    rgb_set_color(RGB_RED);
    wait(DELAY);

    rgb_set_color(RGB_GREEN);
    wait(DELAY);

    rgb_set_color(RGB_BLUE);
    wait(DELAY);

    rgb_set_color(RGB_YELLOW);
    wait(DELAY);

    rgb_set_color(RGB_CYAN);
    wait(DELAY);

    rgb_set_color(RGB_MAGENTA);
    wait(DELAY);

    rgb_set_color(RGB_WHITE);
    wait(DELAY);

    rgb_set_color(RGB_OFF);
    wait(DELAY);

    //test rgb_set_on / rgb_set_off 
    rgb_set_on(0);       //red ON
    wait(DELAY);
    rgb_set_on(1);       //+ green ON
    wait(DELAY);
    rgb_set_on(2);       //+ blue ON (all = white)
    wait(DELAY);

    rgb_set_off(0);      //red OFF (cyan)
    wait(DELAY);
    rgb_set_off(1);      //green OFF (blue)
    wait(DELAY);
    rgb_set_off(2);      //blue OFF (off)
    wait(DELAY);

    //test rgb_set
    rgb_set(0, 1);       // red ON
    wait(DELAY);
    rgb_set(0, 0);       // red OFF
    wait(DELAY);

    //test rgb_toggle
    rgb_set_all_off();
    rgb_toggle(1);       // green ON (bila OFF)
    wait(DELAY);
    rgb_toggle(1);       // green OFF (bila ON)
    wait(DELAY);

    //test rgb_get
    rgb_set_all_off();
    rgb_set_on(2);
    if (rgb_get(2) == 1) {
        rgb_set_all_on(); //works, white
    } else {
        rgb_set_color(RGB_RED); //doesn't work, red
    }
    wait(DELAY);
    rgb_set_all_off();
    wait(DELAY);

    //test rgb_get_all
    rgb_set_color(RGB_CYAN);
    if (rgb_get_all() == 0x06) {
        rgb_set_all_on();     //works, white
    } else {
        rgb_set_color(RGB_RED); //doesn't work, red
    }
    wait(DELAY);
    rgb_set_all_off();
    wait(DELAY);

    //test rgb_blink (blink red)
    rgb_set_all_off();
    rgb_blink(0, DELAY, 1);
    wait(DELAY);

    //test rgb_blink_color (blink yellow)
    rgb_blink_color(RGB_YELLOW, DELAY, 1);
    wait(DELAY);

    //no crash, green
    rgb_set_color(RGB_GREEN);

    while (1);

    return 0;

}