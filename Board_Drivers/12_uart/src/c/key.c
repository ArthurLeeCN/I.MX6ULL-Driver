#include "key.h"

void key_init()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    GPIO_CONFIG conf;
    conf.DIR = GPIO_DIR_INPUT;
    GPIO_INIT(GPIO1,18,&conf);
}

uint8_t read_key()
{
    uint8_t ret = 0;
    ret = GPIO_Read(GPIO1,18);
    return ret;
}

uint8_t key_val()
{
    uint8_t ret = 0;
    static uint8_t release = 1;
    if((read_key() == 0) && (release == 1))
    {
        delay_ms(10);
        release = 0;
        if(read_key() == 0)
        {
            ret = KEY0_VAL;
        }
    }
    else if(read_key() == 1)
    {
        ret = KEY_NON;
        release = 1;
    }

    return ret;
}