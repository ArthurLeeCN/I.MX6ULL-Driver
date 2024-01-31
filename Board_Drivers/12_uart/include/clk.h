#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"

#define BIT_MASK_6 0x3f
#define BIT_MASK_7 0x7f

void peripheral_clk_enable();
void IMX6U_clk_init();

#endif