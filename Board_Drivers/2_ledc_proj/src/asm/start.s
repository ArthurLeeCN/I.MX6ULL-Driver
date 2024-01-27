
.global _start

_start:
    /* 设置进入SVC模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f)
    orr r0, r0, #0x13 @bit[4:0] : 10011
    msr cpsr, r0 @写入到cpsr

    /* 设置SP指针
     * I.MX6ULL DDR起始位置为0x80000000
     * 栈空间设置为2M，cortex-A的栈向下增长
     * SP指针设置到0x80200000
     */
    ldr sp, =0x80200000
    b main @跳转到C语言main函数

