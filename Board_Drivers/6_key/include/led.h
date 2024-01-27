#ifndef __LED_H__
#define __LED_H__

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "gpio.h"
#include "cc.h"

void led_init();
void led_on();
void led_off();
void led_control(uint8_t status);

#endif