#include "exti.h"

void EXTI_INIT()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    GPIO_CONFIG conf;
    conf.DIR = GPIO_DIR_INPUT;
    conf.GPIO_INT = GPIO_IRQ_FALLING;

    GPIO_INIT(GPIO1,18,&conf);
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    REG_IRQ_Handle(GPIO1_Combined_16_31_IRQn,GPIO1_Pin18_EXTI_Handler);
    GPIOn_Pin_IRQ_Enable(GPIO1,18);
}

void GPIO1_Pin18_EXTI_Handler()
{
    static uint8_t status = OFF;
    delay_ms(10);
    if(GPIO_Read(GPIO1, 18) == 0)
    {
        status = !status;
        beep_control(status);
        led_control(status);
    }

    GPIOn_Pin_IRQ_INT_FLAG_CLEAR(GPIO1, 18);
}