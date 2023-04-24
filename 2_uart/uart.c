#include <stdint.h>
#include "uart.h"
#include "gpio.h"
#include <stdio.h>
#include <newlib.h>


void uart_init() {
    // Configure pins as I/O
    // p486 I: RXD, CTS. O: RTS, TXD.
    // GPIO0->PIN_CNF[6] = 0;        // RX p0.08 from schematics p. 1
    // GPIO1->PIN_CNF[8] = 1;        // TX

    // UART->PSELRXD = 8;      // TX -> RX
    // UART->PSELTXD = 6;      // RX -> TX

    GPIO0->PIN_CNF[6] = 1;  // TX
    GPIO0->PIN_CNF[8] = 0;

    GPIO1->PIN_CNF[8] = 0;  // RX
    GPIO0->PIN_CNF[29] = 1;

    UART->PSELRXD = (1<<5) | 8;
    UART->PSELTXD = 6;

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
    // iprintf("sending: %c", letter);
    while (!(UART->EVENTS_TXDRDY));
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;
}


char uart_read() {
    if (UART->EVENTS_RXDRDY == 0) {
        return '\0';
    }
    char data = UART->RXD;
    // iprintf("received: %c", data);
    UART->EVENTS_RXDRDY = 0;
    return data;


    // UART->TASKS_STARTRX = 1;
    // UART->EVENTS_RXDRDY = 0;
    // if (UART->RXD != 0) {
    //     return UART->RXD;
    // }
    // return '\0';
}

