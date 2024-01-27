#include "led.h"

void led_init()
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10b0);
    //IOMUX_SW_MUX->GPIO1_IO03=0x00000005;
    //IOMUX_SW_PAD->GPIO1_IO03=0x000010b0;
//    IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 0x00000005;
//    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 0x000010b0;
    GPIO_CONFIG conf;
    conf.DIR = GPIO_DIR_OUTPUT;
    conf.OUTPUT_LOGIC = HIGH;
    GPIO_INIT(GPIO1,3,&conf);
    // GPIO1_GDIR = 0x00000008;
    // GPIO1_DR = 0x00000000;
}

void led_on()
{
    GPIO_Write(GPIO1,3,LOW);
}

void led_off()
{
    GPIO_Write(GPIO1,3,HIGH);
}

void led_control(uint8_t status)
{
    if(status)
    {
        led_on();
    }
    else
    {
        led_off();
    }
}