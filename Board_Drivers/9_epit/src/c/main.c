#include "main.h"

int main()
{
    INT_INIT();
    IMX6U_clk_init();
    peripheral_clk_enable();
    EXTI_INIT();
    EPIT_Init(0,33000000);
    /* 初始化LED */
    led_init();
    /* 闪烁LED */
    beep_init();
    

    while(1)
    {

    }

    return 0;
}