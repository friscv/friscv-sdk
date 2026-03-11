#include <stdint.h>

#define UART_CLK_HZ 90909088

// UART 16550 register definitions (8-bit registers, 4-byte aligned)
#define UART_BASE       0x40600000

#define UART_RBR    (*(volatile uint32_t *)(UART_BASE + 0x00))  // Receive Buffer Register (read)
#define UART_THR    (*(volatile uint32_t *)(UART_BASE + 0x00))  // Transmit Holding Register (write)
#define UART_IER    (*(volatile uint32_t *)(UART_BASE + 0x04))  // Interrupt Enable Register
#define UART_FCR    (*(volatile uint32_t *)(UART_BASE + 0x08))  // FIFO Control Register (write)
#define UART_LCR    (*(volatile uint32_t *)(UART_BASE + 0x0C))  // Line Control Register
#define UART_MCR    (*(volatile uint32_t *)(UART_BASE + 0x10))  // Modem Control Register
#define UART_LSR    (*(volatile uint32_t *)(UART_BASE + 0x14))  // Line Status Register
#define UART_DLL    (*(volatile uint32_t *)(UART_BASE + 0x00))  // Divisor Latch Low (when LCR[7]=1)
#define UART_DLH    (*(volatile uint32_t *)(UART_BASE + 0x04))  // Divisor Latch High (when LCR[7]=1)

// Line Status Register bits
#define UART_LSR_DR     0x01  // Data Ready
#define UART_LSR_THRE   0x20  // Transmit Holding Register Empty

// Line Control Register bits
#define UART_LCR_WLS_8  0x03  // 8-bit word length
#define UART_LCR_DLAB   0x80  // Divisor Latch Access Bit

// FIFO Control Register bits
#define UART_FCR_ENABLE     0x01  // Enable FIFOs
#define UART_FCR_CLR_RX     0x02  // Clear receive FIFO
#define UART_FCR_CLR_TX     0x04  // Clear transmit FIFO

int uart_init(void) {
    // 115200 baud: UART_CLK_HZ / (16 * 115200) = 49
    uint32_t divisor = UART_CLK_HZ / (16 * 115200);

    // Disable interrupts
    UART_IER = 0x00;

    // Set DLAB to access divisor latches
    UART_LCR = UART_LCR_DLAB;

    // Set baud rate divisor
    UART_DLL = divisor & 0xFF;
    UART_DLH = (divisor >> 8) & 0xFF;

    // 8N1, clear DLAB
    UART_LCR = UART_LCR_WLS_8;

    // Enable and clear FIFOs
    UART_FCR = UART_FCR_ENABLE | UART_FCR_CLR_RX | UART_FCR_CLR_TX;

    // No modem control signals
    UART_MCR = 0x00;

    return 0;
}

void uart_putc(uint8_t c) {
    while (!(UART_LSR & UART_LSR_THRE)) {
        // Wait until transmit holding register is empty
    }
    UART_THR = c;
}

void uart_puts(const uint8_t *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

int uart_getc_nonblocking(void) {
    if (UART_LSR & UART_LSR_DR) {
        return UART_RBR & 0xFF;
    }
    return -1;
}

uint8_t uart_getc(void) {
    while (!(UART_LSR & UART_LSR_DR)) {
        // Wait until data is ready
    }
    return UART_RBR & 0xFF;
}
