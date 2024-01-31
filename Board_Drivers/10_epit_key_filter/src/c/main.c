#include "main.h"

int main()
{
    int i = 0;
    uint8_t led_status = OFF;
    INT_INIT();
    IMX6U_clk_init();
    peripheral_clk_enable();
    EXTI_INIT();
    /* 初始化LED */
    led_init();
    /* 闪烁LED */
    beep_init();
    EPIT1_Init(0,33000000);

    while(1)
    {
        
        i++;
        if(i == 50)
        {
            led_status = !led_status;
            led_control(led_status);
            i = 0;
        }
        delay_ms(10);
        
    }

    return 0;
}