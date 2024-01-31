#include "epit.h"

/* EPIT计数器初始化
 * @Param frac: 计数器分频值0~4095
 * @Param load: 加载计数器值
 */
void EPIT_Init(uint32_t frac, uint32_t load)
{
    EPIT1->CR = 0;
    EPIT1->CR |= (1 << 24);
    if(frac > 4095)
    {
        frac = 4095;
    }
    EPIT1->CR |= (frac << 4);
    EPIT1->CR |= (7 << 1);
    EPIT1->LR = load;
    EPIT1->CMPR = 0;

    GIC_EnableIRQ(EPIT1_IRQn);
    REG_IRQ_Handle(EPIT1_IRQn, EPIT1_IRQ_Handler);

    EPIT1->CR |= 1;
    
}


/* EPIT计数器中断服务函数
 */
void EPIT1_IRQ_Handler()
{
    static uint8_t status = ON;
    
    if(EPIT1->SR & 0x01)
    {
        status = !status;
        led_control(status);
    }

    EPIT1->SR |= 1;
}