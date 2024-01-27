#ifndef __BEEP_H
#define __BEEP_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

void beep_init();
void beep_control(uint8_t status);


#endif