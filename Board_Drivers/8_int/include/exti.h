#ifndef __EXTI_H
#define __EXTI_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"
#include "gpio.h"
#include "IMX6U_INT.h"
#include "time.h"
#include "beep.h"
#include "led.h"

void EXTI_INIT();
void GPIO1_Pin18_EXTI_Handler();

#endif