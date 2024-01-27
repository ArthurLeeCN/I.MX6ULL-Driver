#include "board_init.h"

void clk_enable()
{
    CCM_CCGR1 = 0xFFFFFFFF;
}

void led_init()
{
    IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 0x00000005;
    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 0x000010b0;

    GPIO1_GDIR = 0x00000008;
    GPIO1_DR = 0x00000000;
}