#include "exti.h"

/* @brief 外部中断初始化
 */
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

/* @brief GPIO1_Pin18的外部中断服务函数
 */

void GPIO1_Pin18_EXTI_Handler()
{
    EPIT1_Reload(66000000/100);

    GPIOn_Pin_IRQ_INT_FLAG_CLEAR(GPIO1, 18);
}
