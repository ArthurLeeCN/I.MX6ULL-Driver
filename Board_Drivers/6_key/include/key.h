#ifndef __KEY_H
#define __KEY_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "time.h"
#include "cc.h"
#include "gpio.h"

enum KeyNum
{
    KEY_NON = 0,
    KEY0_VAL
};

void key_init();
uint8_t read_key();
uint8_t key_val();

#endif