#ifndef __UART_H
#define __UART_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"
#include "IMX6U_INT.h"

void UART1_Init();
void UART1_Disable();
void UART1_Enable();
void UART1_SoftReset();
void putc(unsigned char c);
unsigned char getc(void);
void puts(char* str);
void UART_SetBaudRate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz);
void raise(int sig_nr);

#endif