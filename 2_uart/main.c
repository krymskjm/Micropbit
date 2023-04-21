#include "gpio.h"
#include "uart.h"


int main(void) {

    gpio_init();
    uart_init();

    int sleep = 0;
    while (1)
    {
        if (!(GPIO0->IN & (1 << 23))) {     // BTN B pressed
            uart_send('B');
            gpio_lights_on();
        }
        else if (!(GPIO0->IN & (1 << 14))) {    // BTN A pressed
            uart_send('A');
            gpio_lights_off();
        }

        sleep = 10000;
		while(--sleep);
    }

    return 0;
}