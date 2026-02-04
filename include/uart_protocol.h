#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#include <stdint.h>

typedef enum {
    CMD_IGNORE = 0,
    CMD_ECHO = 1,
    CMD_ECHO_REPLY = 2,
} uart_cmd_t;

typedef struct {
    uart_cmd_t cmd;
    uint8_t len;
    uint8_t data[255];
} uart_packet_t;

int uart_read_packet(uart_packet_t *pkt);
void uart_send_packet(uart_cmd_t cmd, uint8_t len, uint8_t *data);

#endif
