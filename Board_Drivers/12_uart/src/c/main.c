#include "main.h"

int main()
{
    int a,b;
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
    UART1_Init();
    UART1_Enable();

    while(1)
    {
        printf("请输入两个整数，用空格隔开: ");
        scanf("%d %d",&a,&b);
        printf("\r\n%d+%d=%d\r\n",a,b,a+b);
    }

    return 0;
}