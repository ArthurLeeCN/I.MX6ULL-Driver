#include "main.h"

int main()
{
    uint8_t led_status = OFF;
    INT_Init();
    IMX6U_clk_init();
    peripheral_clk_enable();
    EXTI_INIT();
    /* 初始化LED */
    led_init();
    /* 闪烁LED */
    beep_init();
    EPIT1_Init(0,33000000);
    GPT1_Init();
    GPT1_INT_Disable();
    GPT1_Start();

    while(1)
    {
        led_status = !led_status;
        led_control(led_status);
        delay_ms(500);
    }

    return 0;
}