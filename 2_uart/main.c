#include "gpio.h"
#include "uart.h"
#include <stdio.h>
#include <newlib.h>

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    return count;
}



int main(void) {

    gpio_init();
    uart_init();
    
    int lightsOn = 0;
    gpio_lights_off();
    int sleep = 0;
    while (1)
    {
        if (!(GPIO0->IN & (1 << 23))) {     // BTN B pressed
            uart_send('B');
            // iprintf("sending: %c", 'B');
            gpio_lights_on();
        }
        else if (!(GPIO0->IN & (1 << 14))) {    // BTN A pressed
            uart_send('A');
            gpio_lights_off();
        }

        sleep = 10000;
		while(--sleep);

        char c = uart_read();
        if (c != '\0') {
            if (lightsOn) {
                gpio_lights_off();
                lightsOn = 0;
            }
            else if (!lightsOn) {
                gpio_lights_on();
                lightsOn = 1;
                iprintf("The average grade in TTK%d was in %d and %d: %c\n\r",4235,2019,2018,'C');
            }
        }


    }

    return 0;
}