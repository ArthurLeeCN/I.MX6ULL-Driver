#include "gpio.h"

void GPIO_INIT(GPIO_Type* Port, uint16_t Pin, GPIO_CONFIG* Conf)
{
    if(Conf->DIR == GPIO_DIR_INPUT)
    {
        Port->GDIR &= ~(1<<Pin);
    }
    else if(Conf->DIR == GPIO_DIR_OUTPUT)
    {
        Port->GDIR |= (1<<Pin);
        GPIO_Write(Port,Pin,Conf->OUTPUT_LOGIC);
    }
}

void GPIO_Write(GPIO_Type* Port, uint16_t Pin, uint8_t Logic)
{
    if(Logic == 0)
    {
        Port->DR &= ~(1<<Pin);
    }
    else
    {
        Port->DR |= (1<<Pin);
    }
}

uint8_t GPIO_Read(GPIO_Type* Port, uint16_t Pin)
{
    uint8_t ret = 0;
    ret = ((Port->DR)>>Pin) & 0x1;
    return ret;
}