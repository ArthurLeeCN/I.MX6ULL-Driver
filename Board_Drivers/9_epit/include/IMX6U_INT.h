#ifndef __IMX6U_INT_H
#define __IMX6U_INT_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"
#include "core_ca7.h"

typedef void (*SYS_IRQ_Handler_t)();

typedef struct
{
    SYS_IRQ_Handler_t IRQ_Handle;
}SYS_IRQ_Handle_t;


void IRQ_Table_Init();
void INT_INIT();
void IRQ_Handler_Default(unsigned int GIC_Init, void* Param);
void REG_IRQ_Handle(IRQn_Type irqn, SYS_IRQ_Handler_t handler);
void SYS_IRQ_Handler(uint32_t giciar);

#endif