
.global _start
.global _bss_start
_bss_start:
    .word __bss_start

.global _bss_end
_bss_end:
    .word __bss_end

_start:
    /* 设置进入SVC模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f)
    orr r0, r0, #0x13 @bit[4:0] : 10011
    msr cpsr, r0 @写入到cpsr

    /* 清空bss段 */
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    mov r2, #0
bss_loop:
    stmia r0!, {r2} @stmia指令是指将大括号中的寄存器的值赋值给r0指定的地址，每次赋值后r0+1
    cmp r0,r1
    ble bss_loop@lower or equal


    /* 设置SP指针
     * I.MX6ULL DDR起始位置为0x80000000
     * 栈空间设置为2M，cortex-A的栈向下增长
     * SP指针设置到0x80200000
     */
    ldr sp, =0x80200000
    b main @跳转到C语言main函数

