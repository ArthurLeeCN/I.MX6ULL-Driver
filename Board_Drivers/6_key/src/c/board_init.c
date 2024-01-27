#include "board_init.h"

void clk_enable()
{
    CCM->CCGR1 = 0xFFFFFFFF;
}