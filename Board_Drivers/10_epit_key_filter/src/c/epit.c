#include "epit.h"

/* EPIT1计数器初始化
 * @param frac: 计数器分频值0~4095
 * @param load: 加载计数器值
 */
void EPIT1_Init(uint32_t frac, uint32_t load)
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

    
}

/* @brief 关闭EPIT1计数器
 */
void EPIT1_Stop()
{
    EPIT1->CR &= ~(1);
}

/* @brief 开启EPIT1计数器
 */
void EPIT1_Start()
{
    EPIT1->CR |= 1;
}

/* @brief EPIT1加载寄存器重哉值
 * @param reload: EPIT1加载寄存器的重载值
 */
void EPIT1_Reload(uint32_t reload)
{
    EPIT1_Stop();
    EPIT1->LR = reload;
    EPIT1_Start();
}

/* @brief EPIT1计数器中断服务函数
 */
void EPIT1_IRQ_Handler()
{
    static uint8_t beep_status = ON;
    
    if(EPIT1->SR & 0x01)
    {
        if(GPIO_Read(GPIO1,18) == 1)
        {
            beep_status = !beep_status;
            beep_control(beep_status);
            EPIT1_Stop();
        }
    }

    EPIT1->SR |= 1;
}