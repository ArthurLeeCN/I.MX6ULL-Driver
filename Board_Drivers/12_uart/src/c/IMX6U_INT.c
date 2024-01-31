#include "IMX6U_INT.h"

static uint32_t irqNesting = 0;
static SYS_IRQ_Handle_t IRQ_Table[NUMBER_OF_INT_VECTORS];


/* @brief IRQ中断函数表初始化
 */
void IRQ_Table_Init()
{
    uint16_t i = 0;
    irqNesting = 0;
    for(i = 0; i<NUMBER_OF_INT_VECTORS; i++)
    {
        IRQ_Table[i].IRQ_Handle = IRQ_Handler_Default;
    }
}


/* @brief 注册中断服务函数
 * @param irqn: 中断号
 * @param handler： 中断服务函数函数指针
 */
void REG_IRQ_Handle(IRQn_Type irqn, SYS_IRQ_Handler_t handler)
{
    IRQ_Table[irqn].IRQ_Handle = handler;
}


/* @brief 中断的初始化
 */
void INT_Init()
{
    GIC_Init();
    IRQ_Table_Init();
    //设置中断向量偏移
    __set_VBAR(0x87800000);
}
/* @brief 默认的中断服务函数，空函数，不要使用
 */
void IRQ_Handler_Default(){}

/* @brief 系统中断服务函数，作用是根据GIC_IAR的值调用指定中断函数
 * @param giciar，CP15协处理器GIC_IAR寄存器的值，包含中断号，由汇编的中断处理函数负责传参
 */
void SYS_IRQ_Handler(uint32_t giciar)
{
    uint32_t irqNUM = (giciar & 0x3ff);
    if(irqNUM >= 160)
    {
        return;
    }
    irqNesting++;
    IRQ_Table[irqNUM].IRQ_Handle();
    irqNesting--;
}