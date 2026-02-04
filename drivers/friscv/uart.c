#include <stdint.h>

// UARTLite register definitions
#define UART_BASE      0x40600000
#define UART_RX_FIFO   (*(volatile uint32_t *)(UART_BASE + 0x0))
#define UART_TX_FIFO   (*(volatile uint32_t *)(UART_BASE + 0x4))
#define UART_STAT_REG  (*(volatile uint32_t *)(UART_BASE + 0x8))
#define UART_CTRL_REG  (*(volatile uint32_t *)(UART_BASE + 0xC))

// Status register bits
#define UART_SR_RX_VALID    0x01  // Receive FIFO valid data
#define UART_SR_RX_FULL     0x02  // Receive FIFO full
#define UART_SR_TX_EMPTY    0x04  // Transmit FIFO empty
#define UART_SR_TX_FULL     0x08  // Transmit FIFO full

// Control register bits
#define UART_CR_RST_TX      0x01  // Reset transmit FIFO
#define UART_CR_RST_RX      0x02  // Reset receive FIFO
#define UART_CR_ENABLE_INT  0x10  // Enable interrupt

int uart_init() {
    // Reset TX and RX
    UART_CTRL_REG = UART_CR_RST_TX | UART_CR_RST_RX;
    // Release reset
    UART_CTRL_REG = 0;
    return 0;
}

void uart_putc(uint8_t c) {
    while (UART_STAT_REG & UART_SR_TX_FULL) {
        // Wait if TX FIFO is full
    }
    // Put char when not full
    UART_TX_FIFO = c;
}

void uart_puts(const uint8_t *s) {
    // Send all chars before `\0`
    while (*s) {
        uart_putc(*s++);
    }
}

int uart_getc_nonblocking() {
    // If there is a char in the RX FIFO, return it
    if (UART_STAT_REG & UART_SR_RX_VALID) {
        return UART_RX_FIFO & 0xFF;
    }
    // Otherwise, return -1 immediately
    return -1;
}

uint8_t uart_getc() {
    while (!(UART_STAT_REG & UART_SR_RX_VALID)) {
        // Wait if RX FIFO is empty
    }
    return UART_RX_FIFO & 0xFF;
}
