#include "beep.h"
#include "cc.h"

void beep_init()
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10b0);

    GPIO5->GDIR |= (1<<1);
    GPIO5->DR |= (1<<1);
}

void beep_control(uint8_t status)
{
    if(status == ON)
    {
        GPIO5->DR &= ~(1<<1);
    }
    else if(status == OFF)
    {
        GPIO5->DR |= (1<<1);
    }
}