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

typedef struct
{
    GPIO_DIR DIR;
    uint8_t OUTPUT_LOGIC;
}GPIO_CONFIG;

void GPIO_INIT(GPIO_Type* Port, uint16_t Pin, GPIO_CONFIG* Conf);
void GPIO_Write(GPIO_Type* Port, uint16_t Pin, uint8_t Logic);
uint8_t GPIO_Read(GPIO_Type* Port, uint16_t Pin);


#endif