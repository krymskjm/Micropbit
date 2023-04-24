#ifndef __UART__
#define __UART__
#include <stdint.h>
#include "gpio.h"
#include <stdio.h>
#include <newlib.h>

#define UART ((NRF_UART_REG*)0x40002000)    // UART base address

typedef struct {
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED0[3];     // correct
    volatile uint32_t TASKS_SUSPEND;
    volatile uint32_t RESERVED1[56];    // correct
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];     // correct
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED3;          // correct
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED4[7];     // correct
    volatile uint32_t EVENTS_RXTO;
    volatile uint32_t RESERVED5[46];        // correct
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED6[64];        // correct
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED7[93];       // correct
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED8[31];       // correct
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED9;       // correct
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED10;       // correct
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED11[17];     // correct
    volatile uint32_t CONFIG;
} NRF_UART_REG;

// Side 502 datablad



void uart_init();
void uart_send(char letter);
char uart_read();


#endif