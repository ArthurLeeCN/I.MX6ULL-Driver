#ifndef __EPIT_H
#define __EPIT_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "core_ca7.h"
#include "cc.h"
#include "IMX6U_INT.h"
#include "led.h"
#include "beep.h"
#include "gpio.h"

void EPIT1_Init(uint32_t frac, uint32_t load);
void EPIT1_Stop();
void EPIT1_Start();
void EPIT1_IRQ_Handler();
void EPIT1_Reload(uint32_t reload);

#endif