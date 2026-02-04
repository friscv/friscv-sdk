#define _DEFAULT_SOURCE  // For CRTSCTS

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

int serial_port;

int uart_init(void) {
    serial_port = open("/dev/ttyAMA0", O_RDWR);

    if (serial_port < 0) {
        perror("Error opening serial port");
        return -1;
    }

    struct termios tty;

    if (tcgetattr(serial_port, &tty) != 0) {
        perror("Error getting serial attributes");
        close(serial_port);
        return -1;
    }

    // Set baud rate 115200
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    // 8 data bits, no parity, 1 stop bit
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    // Raw mode
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;

    // Disable software flow control
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_lflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    // Raw output
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;

    // Set read timeout (VTIME in deciseconds, VMIN in characters)
    tty.c_cc[VTIME] = 10;  // 1 second timeout
    tty.c_cc[VMIN] = 0;    // Return immediately with available data

    // Apply settings
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        perror("Error setting serial attributes");
        close(serial_port);
        return -1;
    }

    return 0;
}

void uart_putc(uint8_t c) {
    write(serial_port, &c, 1);
}

void uart_puts(const uint8_t *s) {
    write(serial_port, s, strlen((const char *)s));
}

int uart_getc_nonblocking(void) {
    uint8_t c;
    int bytes_available;

    if (ioctl(serial_port, FIONREAD, &bytes_available) < 0) {
        return -1;
    }

    if (bytes_available > 0) {
        if (read(serial_port, &c, 1) == 1) {
            return c;
        }
    }
    return -1;
}

uint8_t uart_getc(void) {
    uint8_t c;
    while (read(serial_port, &c, 1) != 1) {
        // Keep trying until we get a character
    }
    return c;
}
