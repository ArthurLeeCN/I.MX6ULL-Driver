#ifndef __GPIO_H
#define __GPIO_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"

#define HIGH        1
#define LOW         0

typedef enum
{
    GPIO_DIR_INPUT = 0x0u,
    GPIO_DIR_OUTPUT = 0x1u,
}GPIO_DIR;

typedef enum
{
    GPIO_IRQ_LOW = 0,
    GPIO_IRQ_HIGH,
    GPIO_IRQ_RISING,
    GPIO_IRQ_FALLING,
    GPIO_IRQ_RISING_FALLING,
    GPIO_IRQ_NO_INT,
}GPIO_INT_FUNCTION;

typedef struct
{
    GPIO_DIR DIR;
    uint8_t OUTPUT_LOGIC;
    GPIO_INT_FUNCTION GPIO_INT;
}GPIO_CONFIG;

void GPIO_INIT(GPIO_Type* Port, uint32_t Pin, GPIO_CONFIG* Conf);
void GPIO_INT_INIT(GPIO_Type* Port, uint32_t Pin, GPIO_INT_FUNCTION Func);
void GPIO_Write(GPIO_Type* Port, uint32_t Pin, uint8_t Logic);
uint8_t GPIO_Read(GPIO_Type* Port, uint32_t Pin);
void GPIOn_Pin_IRQ_INT_FLAG_CLEAR(GPIO_Type* Port, uint32_t Pin);
void GPIO_INT_INIT(GPIO_Type* Port, uint32_t Pin, GPIO_INT_FUNCTION Func);
void GPIOn_Pin_IRQ_Enable(GPIO_Type* Port, uint32_t Pin);
void GPIOn_Pin_IRQ_Disable(GPIO_Type* Port, uint32_t Pin);
#endif