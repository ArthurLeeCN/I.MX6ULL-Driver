#include "time.h"


/*
*@Description: 短暂延迟
*@param 1: n: 执行n次循环
*/
void delay(volatile unsigned int n)
{
    while(n--);
}

/*
*@Description: 396MHz主频下控制毫秒延迟
*@Param 1: ms: 延迟ms毫秒
*/
void delay_ms(volatile unsigned int ms)
{
    while(ms--)
    {
        delay(0x7ff);
    }
}