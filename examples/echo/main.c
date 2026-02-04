#include "uart.h"
#include "leds.h"

int main() {
    leds_set_all_on();
    uart_init();

    uart_puts((uint8_t *)"Ready\r\n");

    int first = 1;

    while (1) {
        uint8_t c = uart_getc();

        if (first) {
            first = 0;
            leds_set_all_off();
        }
        leds_toggle(0);

        uart_putc(c);
        
        if (c == '\r') {
            uart_putc('\n');
        }
    }

    return 1;
}
