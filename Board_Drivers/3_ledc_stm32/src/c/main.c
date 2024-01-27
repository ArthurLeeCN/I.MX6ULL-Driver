#include "time.h"
#include "board_init.h"
#include "led.h"

int main()
{
    clk_enable();
    /* 初始化LED */
    led_init();
    /* 闪烁LED */
    while(1)
    {
        led_on();
        delay_ms(250);

        led_off();
        delay_ms(250);
    }

    return 0;
}