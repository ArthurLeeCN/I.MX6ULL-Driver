#include "time.h"
#include "board_init.h"
#include "led.h"
#include "cc.h"
#include "beep.h"
#include "key.h"

int main()
{
    uint8_t beep_status = OFF;
    uint8_t led_status = OFF;
    clk_enable();
    /* 初始化LED */
    led_init();
    /* 闪烁LED */
    beep_init();
    key_init();


    while(1)
    {
        if(key_val())
        {
            led_status = !led_status;
            beep_status = !beep_status;
            led_control(led_status);
            beep_control(beep_status);
        }
    }

    return 0;
}