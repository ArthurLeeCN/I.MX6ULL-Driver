#include "gpt.h"

/* @breif GPT1初始化
 */
void GPT1_Init()
{
    GPT1->CR = 0;

    /* 软复位 */
    GPT1->CR |= (1 << 15);
    while ((GPT1->CR >> 15) & 0x01);

    GPT1->CR |= (1 << 1);
    GPT1->CR |= (1 << 6);
    
    GPT1->PR &= ~(0xfff << 0);
    GPT1->PR |= (65 << 0);

    /* 设置输出比较通道1，仅该通道支持restart模式 */
    GPT1->OCR[0] = 0xffffffff;
//    GPT1_INT_Enable();
    REG_IRQ_Handle(GPT1_IRQn,GPT1_OCR1_IRQ_Handler);
}

/* @brief 关闭GPT1
 */
void GPT1_Stop()
{
    GPT1->CR &= 1;
}

/* @brief 开启GPT1
 */
void GPT1_Start()
{
    GPT1->CR |= 1;
}


/* @brief GPT1中断使能
 */
void GPT1_INT_Enable()
{
    GPT1->IR |= (1 << 0);
    GIC_EnableIRQ(GPT1_IRQn);
}

/* @brief GPT1中断禁止
 */
void GPT1_INT_Disable()
{
    GPT1->IR &= ~(1 << 0);
    GIC_DisableIRQ(GPT1_IRQn);
}

/* @brief 使用GPT1作为us计时
 * @param us: 需要计时的微秒数
 */
void delay_us(uint32_t us)
{
    uint32_t newcnt,oldcnt;
    
    uint32_t cntval = 0;
    oldcnt = GPT1->CNT;
    while(cntval < us)
    {
        newcnt = GPT1->CNT;
        if(newcnt > oldcnt)
        {
            cntval += newcnt - oldcnt;
        }
        else
        {
            cntval += 0xFFFFFFFF - oldcnt + newcnt;
        }
        oldcnt = newcnt;
    }
    
}


/* @brief 使用GPT1作为ms计时
 * @param ms: 需要计时的毫秒数
 */
void delay_ms(uint32_t ms)
{
    int i = 0;
    for(i = 0; i<ms; i++)
    {
        delay_us(1000);
    }
}


/* @brief GPT1输出比较通道1中断服务函数
 */
void GPT1_OCR1_IRQ_Handler()
{
    static uint8_t led_status = ON;
    if(GPT1->SR & 0x01)
    {
        led_status = !led_status;
        led_control(led_status);
    }
    GPT1->SR |= (1 << 0);
}

