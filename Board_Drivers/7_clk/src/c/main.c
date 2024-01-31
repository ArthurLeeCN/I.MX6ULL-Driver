#include "time.h"
#include "clk.h"
#include "led.h"
#include "cc.h"
#include "beep.h"
#include "key.h"

int main()
{
    uint8_t beep_status = OFF;
    uint8_t led_status = OFF;
    int i = 0;
    IMX6U_clk_init();
    peripheral_clk_enable();
    /* 初始化LED */
    led_init();
    /* 闪烁LED */
    beep_init();
    key_init();
    

    while(1)
    {
        if(key_val())
        {
            beep_status = !beep_status;
            beep_control(beep_status);
        }


        i++;
        if(i == 50)
        {
            i=0;
            led_status = !led_status;
            led_control(led_status);
        }

        delay_ms(10);

    }

    return 0;
}