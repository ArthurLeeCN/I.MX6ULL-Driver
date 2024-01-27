#ifndef __MAIN_H__
#define __MAIN_H__

/* 定义要使用的寄存器 */

#define CCM_CCGR0 *((volatile unsigned int*)0x020c4068)
#define CCM_CCGR1 *((volatile unsigned int*)0x020c406c)

#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 *((volatile unsigned int*)0x020e0068)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 *((volatile unsigned int*)0x020e02f4)

#define GPIO1_GDIR *((volatile unsigned int*)0x0209c004)
#define GPIO1_DR *((volatile unsigned int*)0x0209c000)

#endif