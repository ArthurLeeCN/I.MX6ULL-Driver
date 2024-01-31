#include "beep.h"

void beep_init()
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10b0);

    GPIO_CONFIG conf;
    conf.DIR = GPIO_DIR_OUTPUT;
    conf.OUTPUT_LOGIC = HIGH;
    GPIO_INIT(GPIO5,1,&conf);
}

void beep_control(uint8_t status)
{
    if(status == ON)
    {
        GPIO_Write(GPIO5,1,LOW);
    }
    else if(status == OFF)
    {
        GPIO_Write(GPIO5,1,HIGH);
    }
}