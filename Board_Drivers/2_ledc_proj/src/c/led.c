#include "led.h"

void led_on()
{
    GPIO1_DR &= ~(1<<3);
}

void led_off()
{
    GPIO1_DR |= (1<<3);
}