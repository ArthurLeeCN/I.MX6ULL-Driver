#include "gpio.h"

/* @brief GPIO初始化设置
 * @param Port: GPIO口设置，类型为GPIO_Type*
 * @param Pin: GPIO引脚号
 * @param Conf: GPIO配置结构体 
 */
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

/* @brief GPIO中断配置
 * @param Port: GPIO口设置，类型为GPIO_Type*
 * @param Pin: GPIO引脚号
 * @param Func: GPIO中断触发方式
 */
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

/* @brief 向GPIO引脚写值
 * @param Port: GPIO口设置，类型为GPIO_Type*
 * @param Pin: GPIO引脚号
 * @param Logic: GPIO写入为高或低
 */
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


/* @brief 读GPIO引脚的值
 * @param Port: GPIO口设置，类型为GPIO_Type*
 * @param Pin: GPIO引脚号
 * @return: uint8_t类型，GPIO口的值
 */
uint8_t GPIO_Read(GPIO_Type* Port, uint32_t Pin)
{
    uint8_t ret = 0;
    ret = ((Port->DR)>>Pin) & 0x1;
    return ret;
}


/* @brief 使能指定Pin口中断
 * @param Port: GPIO口设置，类型为GPIO_Type*
 * @param Pin: GPIO引脚号
 */
void GPIOn_Pin_IRQ_Enable(GPIO_Type* Port, uint32_t Pin)
{
    Port->IMR |= (1 << Pin);
}


/* @brief 关闭指定Pin口中断
 * @param Port: GPIO口设置，类型为GPIO_Type*
 * @param Pin: GPIO引脚号
 */
void GPIOn_Pin_IRQ_Disable(GPIO_Type* Port, uint32_t Pin)
{
    Port->IMR &= ~(1 << Pin);
}


/* @brief 清除中断标志位
 * @param Port: GPIO口设置，类型为GPIO_Type*
 * @param Pin: GPIO引脚号
 */
void GPIOn_Pin_IRQ_INT_FLAG_CLEAR(GPIO_Type* Port, uint32_t Pin)
{
    Port->ISR |= (1 << Pin);
}