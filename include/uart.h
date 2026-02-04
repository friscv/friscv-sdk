#ifndef UART_H
#define UART_H

#include <stdint.h>

int uart_init(void);
void uart_putc(uint8_t c);
void uart_puts(const uint8_t *s);
int uart_getc_nonblocking(void);
uint8_t uart_getc(void);

#endif
