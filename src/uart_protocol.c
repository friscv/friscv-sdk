#include "uart.h"
#include "uart_protocol.h"

int uart_read_packet(uart_packet_t *pkt) {
    pkt->cmd = uart_getc();
    pkt->len = uart_getc();

    for (int i = 0; i < pkt->len; i++) {
        pkt->data[i] = uart_getc();
    }

    return 0;
}

void uart_send_packet(uart_cmd_t cmd, uint8_t len, uint8_t *data) {
    uart_putc(cmd);
    uart_putc(len);
    for (int i = 0; i < len; i++) {
        uart_putc(data[i]);
    }
}
