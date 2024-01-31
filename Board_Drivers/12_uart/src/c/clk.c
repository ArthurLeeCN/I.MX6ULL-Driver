#include "clk.h"

void peripheral_clk_enable()
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

void IMX6U_clk_init()
{
    /* 设置主频528MHz */
    if(((CCM->CCSR >> 2)&0x1) == 0)
    {
        CCM->CCSR &= ~(1 << 8);
        CCM->CCSR |= (1 << 2); /* ARM内核暂时使用外部24MHz晶振直接产生的时钟 */
    }
    /* PLL1 设置为 1056 MHz */
    CCM_ANALOG->PLL_ARM &= ~(0x7f);
    CCM_ANALOG->PLL_ARM |= 0x58;
    CCM_ANALOG->PLL_ARM |= (1 << 13);

    /* PLL1二分频输出到ARM内核 */
    CCM->CACRR = 0x001;
    CCM->CCSR &= ~(1 << 2);

    /* 设置PLL2和PLL3的PFD时钟为推荐值 */
    int reg = CCM_ANALOG->PFD_528;
    reg &= ~(0x3f3f3f3f);
    reg |= (27 << 0); //PLL2_PFD0 352MHz
    reg |= (26 << 8); //PLL2_PFD1 594MHz
    reg |= (24 << 16); //PLL2_PFD2 396MHz
    reg |= (32 << 24); //PLL2_PFD3 297MHz
    CCM_ANALOG->PFD_528 = reg;

    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0x3f3f3f3f);
    reg |= (12 << 0); //PLL3_PFD0 720MHz
    reg |= (16 << 8); //PLL3_PFD1 540MHz
    reg |= (17 << 0); //PLL3_PFD2 508.2MHz
    reg |= (19 << 0); //PLL3_PFD3 454.7MHz
    CCM_ANALOG->PFD_480 = reg;

    /* AHB_CLK_ROOT设置为132MHz */
    CCM->CBCMR &= ~(3 << 18); //时钟源PLL2_PFD2
    while(CCM->CDHIPR & (1 << 1));
    CCM->CBCMR |= (1 << 18); 
    CCM->CBCDR &= ~(1 << 25);
    while(CCM->CDHIPR & (1 << 1));

    /* IPG_CLK_ROOT设置为66MHz */
    CCM->CBCDR &= ~(3 << 8);
    CCM->CBCDR |= (1 << 8);
    /* PERCLK_CLK_ROOT 设置从IPG_CLK_ROOT来 */
    CCM->CSCMR1 &= ~(1 << 6);
    CCM->CSCMR1 &= ~(BIT_MASK_6);
}