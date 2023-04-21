#include <stdint.h>
#include "uart.h"
#include "gpio.h"


void uart_init() {
    // Configure pins as I/O
    // p486 I: RXD, CTS. O: RTS, TXD.
    GPIO0->PIN_CNF[6] = 0;        // RX p0.08 from schematics p. 1
    GPIO1->PIN_CNF[8] = 1;        // TX   

    // Use pins using PSEL-TXD/RXD registers
    // UART->PSELRXD &= ~(1<<6);     // 0: disconnected, 1: connected
    // UART->PSELTXD &= ~(1<<8);
    // 0... 0100 0110       // portnb = x, GPIOx
    UART->PSELRXD = 6;     // = 0b0000 ... 0000 0110 (connected, port 0, pin 6)
    // UART->PSELTXD = 40;    // = 0b0000 ... 0010 1000 (connected, port 1, pin 8)
    UART->PSELTXD = 8;

    // choose baudrate
    UART->BAUDRATE = 0x00275000;    // from datasheet 9600 

    // Tell UART-module theres no CTS/RTS pins (using PSELRTS/PSELCTS)
    UART->PSELRTS = 1 << 31;        // disconnected
    UART->PSELCTS = 1 << 31;        // disconnected
    // UART->PSELRTS =~ 0;
    // UART->PSELCTS =~ 0;

    // Turn on UART with the ENABLE register.
    UART->ENABLE = 4;       // enable UART

    // Receive messages (using TASKS_STARTRX register)
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter) {
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while (!(UART->EVENTS_TXDRDY));
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;
}


// char uart_read() {
    // if (UART->EVENTS_RXDRDY) {
    //     UART->EVENTS_RXDRDY = 0;
    //     return UART->RXD;
    // }
    // return '\0';
// }

