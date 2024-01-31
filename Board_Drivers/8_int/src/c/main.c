#include "main.h"

int main()
{
    uint8_t led_status = OFF;
    int i = 0;
    INT_INIT();
    IMX6U_clk_init();
    peripheral_clk_enable();
    EXTI_INIT();
    /* 初始化LED */
    led_init();
    /* 闪烁LED */
    beep_init();
    

    while(1)
    {
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