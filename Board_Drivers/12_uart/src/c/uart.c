#include "uart.h"

/* @brief 初始化UART1,波特率115200
 *
 */
void UART1_Init()
{
    CCM->CSCDR1 &= ~(0x7f << 0); //UART时钟源为PPL3，分频1，得到UART时钟频率为80MHz
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX,0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX,0);

    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10b0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10b0);

    UART1_Disable();
    UART1_SoftReset();

    UART1->UCR1 = 0;

    UART1->UCR2 = 0;
    UART1->UCR2 |= (1 << 1);
    UART1->UCR2 |= (1 << 2);
    UART1->UCR2 |= (1 << 5);
    UART1->UCR2 |= (1 << 14);

    UART1->UCR3 |= (1 << 2);

    /* 设置波特率115200 */
    UART_SetBaudRate(UART1,115200,80000000);

}

/* @brief 关闭UART1
 * 
 */
void UART1_Disable()
{
    UART1->UCR1 &= ~(1 << 0);
}

/* @brief 开启UART1
 *  
 */
void UART1_Enable()
{
    UART1->UCR1 |= (1 << 0);
}

/* @brief 复位UART1
 */
void UART1_SoftReset()
{
    UART1->UCR2 &= ~(1 << 0);
    while((UART1->UCR2 & 0x01) == 0);
}

/* @brief 通过UART1发送一个字节
 * @param c: 要发送的字节
 */
void putc(unsigned char c)
{
    while(((UART1->USR2 >> 3) & 0x01) == 0);//等待上一次发送完成
    UART1->UTXD = c;
}

/* @brief 从UART1中读一个字节
 * @return uint8_t类型
 */
unsigned char getc(void)
{
    while(((UART1->USR2) & 0x01) == 0);//等待有数据读取
    return UART1->URXD;
}


/* @brief 通过UART1发送字符串
 * @param str: char类型数组
 */
void puts(char* str)
{
    char* ptr = str;
    while(*ptr)
    {
        putc(*ptr++);
    }
}


/* @brief NXP提供的SDK中的波特率设置函数
 * @param base: UART口
 * @param baudrate: 波特率
 * @param srcclock_hz: 时钟源频率
 */
void UART_SetBaudRate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz)
{
    uint32_t numerator = 0u;		//分子
    uint32_t denominator = 0U;		//分母
    uint32_t divisor = 0U;
    uint32_t refFreqDiv = 0U;
    uint32_t divider = 1U;
    uint64_t baudDiff = 0U;
    uint64_t tempNumerator = 0U;
    uint32_t tempDenominator = 0u;

    /* get the approximately maximum divisor */
    numerator = srcclock_hz;
    denominator = baudrate << 4;
    divisor = 1;

    while (denominator != 0)
    {
        divisor = denominator;
        denominator = numerator % denominator;
        numerator = divisor;
    }

    numerator = srcclock_hz / divisor;
    denominator = (baudrate << 4) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7)) || (denominator > UART_UBIR_INC_MASK))
    {
        uint32_t m = (numerator - 1) / (UART_UBIR_INC_MASK * 7) + 1;
        uint32_t n = (denominator - 1) / UART_UBIR_INC_MASK + 1;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0 == numerator)
        {
            numerator = 1;
        }
        if (0 == denominator)
        {
            denominator = 1;
        }
    }
    divider = (numerator - 1) / UART_UBIR_INC_MASK + 1;

    switch (divider)
    {
        case 1:
            refFreqDiv = 0x05;
            break;
        case 2:
            refFreqDiv = 0x04;
            break;
        case 3:
            refFreqDiv = 0x03;
            break;
        case 4:
            refFreqDiv = 0x02;
            break;
        case 5:
            refFreqDiv = 0x01;
            break;
        case 6:
            refFreqDiv = 0x00;
            break;
        case 7:
            refFreqDiv = 0x06;
            break;
        default:
            refFreqDiv = 0x05;
            break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator = srcclock_hz;
    tempDenominator = (numerator << 4);
    divisor = 1;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0)
    {
        divisor = tempDenominator;
        tempDenominator = tempNumerator % tempDenominator;
        tempNumerator = divisor;
    }
    tempNumerator = srcclock_hz / divisor;
    tempDenominator = (numerator << 4) / divisor;
    baudDiff = (tempNumerator * denominator) / tempDenominator;
    baudDiff = (baudDiff >= baudrate) ? (baudDiff - baudrate) : (baudrate - baudDiff);

    if (baudDiff < (baudrate / 100) * 3)
    {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR = UART_UBIR_INC(denominator - 1); //要先写UBIR寄存器，然后在写UBMR寄存器，3592页 
        base->UBMR = UART_UBMR_MOD(numerator / divider - 1);
    }
}

/* @brief 防止编译报错，不要实现
 */
void raise(int sig_nr)
{

}