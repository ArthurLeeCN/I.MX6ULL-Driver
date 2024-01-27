#include "time.h"
#include "board_init.h"
#include "led.h"
#include "cc.h"
#include "beep.h"

int main()
{
    clk_enable();
    /* 初始化LED */
    led_init();
    /* 闪烁LED */
    beep_init();
    while(1)
    {
        led_on();
        beep_control(ON);
        delay_ms(1000);

        beep_control(OFF);
        led_off();
        delay_ms(1000);
    }

    return 0;
}