#include <stdint.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main(void) {

    // konfigurerer jordingspinnene

    GPIO0 -> PIN_CNF[28] = 0;
    GPIO0 -> PIN_CNF[11] = 0;
    GPIO0 -> PIN_CNF[31] = 0;
    GPIO1 -> PIN_CNF[5] = 0;
    GPIO0 -> PIN_CNF[30] = 0; 

    // konfigurerer forsyningspinner

    GPIO0 -> PIN_CNF[21] = 0;
    GPIO0 -> PIN_CNF[22] = 0;
    GPIO0 -> PIN_CNF[15] = 0;
    GPIO0 -> PIN_CNF[24] = 0;
    GPIO0 -> PIN_CNF[19] = 0;

    // setter jordingspinnene til output og logisk lav

    GPIO0 -> DIRSET = (1 << 28);
    GPIO0 -> DIRSET = (1 << 11);
    GPIO0 -> DIRSET = (1 << 31);
    GPIO1 -> DIRSET = (1 << 5);
    GPIO0 -> DIRSET = (1 << 30);

    GPIO0 -> OUTCLR = (1 << 28);
    GPIO0 -> OUTCLR = (1 << 11);
    GPIO0 -> OUTCLR = (1 << 31);
    GPIO1 -> OUTCLR = (1 << 5);
    GPIO0 -> OUTCLR = (1 << 30);

    // konfigurerer knapp
    GPIO0 -> PIN_CNF[14] = 0;

    gpiote_init();
    init_PPI();

    while (1);
    return 0;
}