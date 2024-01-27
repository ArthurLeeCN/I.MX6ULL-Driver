#include "led.h"

void led_on()
{
    GPIO1->DR &= ~(1<<3);
}

void led_off()
{
    GPIO1->DR |= (1<<3);
}