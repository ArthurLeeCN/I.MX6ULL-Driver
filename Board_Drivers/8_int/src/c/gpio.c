#include "gpio.h"
/* GPIO初始化设置 */
void GPIO_INIT(GPIO_Type* Port, uint32_t Pin, GPIO_CONFIG* Conf)
{
    if(Conf->DIR == GPIO_DIR_INPUT)
    {
        Port->GDIR &= ~(1<<Pin);
    }
    else if(Conf->DIR == GPIO_DIR_OUTPUT)
    {
        Port->GDIR |= (1<<Pin);
        GPIO_Write(Port,Pin,Conf->OUTPUT_LOGIC);
    }
    GPIO_INT_INIT(Port, Pin, Conf->GPIO_INT);
}
/* GPIO中断设置 */
void GPIO_INT_INIT(GPIO_Type* Port, uint32_t Pin, GPIO_INT_FUNCTION Func)
{
    __IO uint32_t* ICR;
    uint32_t Pin_Shift = Pin;

    Port->EDGE_SEL &= ~(1 << Pin);
    if(Pin < 16)
    {
        ICR = &(Port->ICR1);
    }
    else
    {
        ICR = &(Port->ICR2);
        Pin_Shift -= 16;
    }
    switch (Func)
    {
    case GPIO_IRQ_LOW:
        *ICR &= ~(3 << (2*Pin_Shift));
        *ICR |= (Func << (2*Pin_Shift));
        break;
    case GPIO_IRQ_HIGH:
        *ICR &= ~(3 << (2*Pin_Shift));
        *ICR |= (Func << (2*Pin_Shift));
        break;
    case GPIO_IRQ_FALLING:
        *ICR &= ~(3 << (2*Pin_Shift));
        *ICR |= (Func << (2*Pin_Shift));
        break;
    case GPIO_IRQ_RISING:
        *ICR &= ~(3 << (2*Pin_Shift));
        *ICR |= (Func << (2*Pin_Shift));
        break;
    case GPIO_IRQ_RISING_FALLING:
        Port->EDGE_SEL |= (1 << Pin);
        break;
    case GPIO_IRQ_NO_INT:
        break;
    }
}

/* 读GPIO口的值 */
void GPIO_Write(GPIO_Type* Port, uint32_t Pin, uint8_t Logic)
{
    if(Logic == 0)
    {
        Port->DR &= ~(1<<Pin);
    }
    else
    {
        Port->DR |= (1<<Pin);
    }
}
/* 向GPIO口写值 */
uint8_t GPIO_Read(GPIO_Type* Port, uint32_t Pin)
{
    uint8_t ret = 0;
    ret = ((Port->DR)>>Pin) & 0x1;
    return ret;
}
/* 使能指定Pin口中断 */
void GPIOn_Pin_IRQ_Enable(GPIO_Type* Port, uint32_t Pin)
{
    Port->IMR |= (1 << Pin);
}
/* 关闭指定Pin口中断 */
void GPIOn_Pin_IRQ_Disable(GPIO_Type* Port, uint32_t Pin)
{
    Port->IMR &= ~(1 << Pin);
}
/* 清除中断标志位 */
void GPIOn_Pin_IRQ_INT_FLAG_CLEAR(GPIO_Type* Port, uint32_t Pin)
{
    Port->ISR |= (1 << Pin);
}