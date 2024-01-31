#ifndef __GPT_H
#define __GPT_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"
#include "led.h"
#include "IMX6U_INT.h"

void GPT1_Init();
void GPT1_Stop();
void GPT1_Start();
void GPT1_INT_Enable();
void GPT1_INT_Disable();
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void GPT1_OCR1_IRQ_Handler();

#endif