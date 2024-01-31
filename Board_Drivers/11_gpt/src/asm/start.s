
.global _start
.global _bss_start


_start:
    /* 设置中断向量表 */
    ldr pc, =RESET_Handler
    ldr pc, =UNDEF_INS_Handler
    ldr pc, =SVC_Handler
    ldr pc, =PREFETCH_ABORT_Handler
    ldr pc, =DATA_ABORT_Handler
    ldr pc, =NOT_USED_Handler
    ldr pc, =IRQ_Handler
    ldr pc, =FIQ_Handler

RESET_Handler:

    /* 关中断，防止打断初始化操作 */
    cpsid i 
    cpsid f

    /* 关闭I，D Cache和MMU
     * 上电时内存并没有准备好，直接读内存可能出错
     * cp15协处理器提供一些系统控制功能，主要针对内存管理部分
     * 使用CP15协处理器使用读改写的方式修改SCTLR寄存器
     * SCTLR寄存器bit0用于控制MMU
     * bit1 对齐控制位
     * bit2 D Cache控制位
     * bit11 分支预测控制位
     * bit12 I Cache控制位
     */
    mrc p15, 0, r0, c1, c0, 0//读
    bic r0, r0, #(1 << 12)
    bic r0, r0, #(1 << 11)
    bic r0, r0, #(1 << 2)
    bic r0, r0, #(1 << 1)
    bic r0, r0, #(1 << 0)
    mcr p15, 0, r0, c1, c0, 0//写

    /* 设置中断向量偏移
     * 将中断向量新的首地址写入到CP15协处理器的VBAR寄存器里
     */

    /*ldr r0, =0x87800000
    dsb
    isb
    mcr p15, 0, r0, c12, c0, 0
    dsb
    isb
    */
    /* 设置各个模式下的SP指针
     * I.MX6ULL DDR起始位置为0x80000000
     * 栈空间设置为2M，cortex-A的栈向下增长
     * SP指针设置到0x80200000
     */
_bss_start:
    .word __bss_start

.global _bss_end
_bss_end:
    .word __bss_end
    /* 清空bss段 */
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    mov r2, #0
bss_loop:
    stmia r0!, {r2} @stmia指令是指将大括号中的寄存器的值赋值给r0指定的地址，每次赋值后r0+1
    cmp r0,r1
    ble bss_loop@lower or equal

    /* 设置进入UND模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f),清空后五位
    orr r0, r0, #0x1b @bit[4:0] : 11011
    msr cpsr, r0 @写入到cpsr,进入UND模式
    ldr sp, =0x81000000

    /* 设置进入HYP模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f),清空后五位
    orr r0, r0, #0x1a @bit[4:0] : 11010
    msr cpsr, r0 @写入到cpsr,进入HYP模式
    ldr sp, =0x80e00000

    /* 设置进入ABT模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f),清空后五位
    orr r0, r0, #0x17 @bit[4:0] : 10111
    msr cpsr, r0 @写入到cpsr,进入ABT模式
    ldr sp, =0x80c00000

    /* 设置进入MON模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f),清空后五位
    orr r0, r0, #0x16 @bit[4:0] : 10110
    msr cpsr, r0 @写入到cpsr,进入MON模式
    ldr sp, =0x80a00000

    /* 设置进入SYS模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f),清空后五位
    orr r0, r0, #0x1f @bit[4:0] : 11111
    msr cpsr, r0 @写入到cpsr,进入SYS模式
    ldr sp, =0x80800000 @SYS模式下的SP指针地址为0x80800000,栈空间0x80600000~0x80800000
                        @SYS模式下SP指针与USER模式共用

    /* 设置进入FIR模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f),清空后五位
    orr r0, r0, #0x11 @bit[4:0] : 10001
    msr cpsr, r0 @写入到cpsr,进入FIR模式
    ldr sp, =0x80600000 @FIR模式下的SP指针地址为0x80600000,栈空间0x80400000~0x80600000

    /* 设置进入IRQ模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f),清空后五位
    orr r0, r0, #0x12 @bit[4:0] : 10010
    msr cpsr, r0 @写入到cpsr,进入IRQ模式
    ldr sp, =0x80400000 @IRQ模式下的SP指针地址为0x80400000,栈空间0x80200000~0x80400000
    
    /* 设置进入SVC模式 */
    mrs r0, cpsr  @读取cpsr寄存器的值
    bic r0, r0, #0x1f @r0 = r0 & (~0x1f)
    orr r0, r0, #0x13 @bit[4:0] : 10011
    msr cpsr, r0 @写入到cpsr,进入SVC模式
    ldr sp, =0x80200000 @SVC模式下的SP指针地址为0x80200000,栈空间0x80000000~0x80200000

    /* 开中断 */
    cpsie i
    cpsid f

    b main @跳转到C语言main函数

UNDEF_INS_Handler:
    ldr r0, =UNDEF_INS_Handler
    bx r0

SVC_Handler:
    ldr r0, =SVC_Handler
    bx r0

PREFETCH_ABORT_Handler:
    ldr r0, =PREFETCH_ABORT_Handler
    bx r0

DATA_ABORT_Handler:
    ldr r0, =DATA_ABORT_Handler
    bx r0

NOT_USED_Handler:
    ldr r0, =NOT_USED_Handler
    bx r0

IRQ_Handler:
    push {lr} /* lr寄存器(R14)保存了子程序返回地址，
               * 当子程序返回时从lr寄存器读地址到pc可以完成子程序的返回
               * 将lr寄存器入栈可以实现中断和子程序的嵌套
               */
    push {r0-r3, r12} @将没有自动保存的寄存器入栈

    mrs r0, spsr
    push {r0}@保存spsr状态

    mrc p15, 4, r1, c15, c0, 0 /* 读取CP15的CBAR寄存器
                                * CBAR寄存器保存了GIC控制器的首地址
                                */
    add r1, r1, #0x2000 /* CBAR寄存器偏移0x1000的位置是GIC控制器的分发段首地址，控制硬件
                         * 偏移0x2000的位置是GIC控制器的CPU接口段
                         */

    ldr r0, [r1, #0xc] /* GIC控制器CPU接口段偏移0xC的位置是GIC_IAR寄存器，bit0~9保存了中断ID
                        * 通过中断ID跳转到对应的服务函数
                        */
    push {r0, r1}

    cps #0x13 /* 进入SVC模式，在特权模式（除用户模式外均为特权模式）下可以直接进入其他模式
               * 使用cps指令直接修改CPSR寄存器[4:0]的值
               * 这里进入SVC模式让其他中断可以进来
               */
    push {lr} @保存SVC的lr指针
    ldr r2, =SYS_IRQ_Handler @调用C语言的中断服务函数，函数有一个参数，已经保存到r0
    blx r2 @blx指令会将返回地址写到lr指针中，

    pop {lr} @执行完成，lr出栈
    cps #0x12 @进入IRQ模式
    pop {r0, r1}
    str r0, [r1, #0x10] @中断处理完成，把GIC_IAR的值写到GIC_EOIR里面去，表示中断处理完成

    pop {r0}
    msr spsr_cxsf, r0 @恢复spsr
    pop {r0-r3, r12}
    pop {lr}
    subs pc, lr ,#4 /* ARM Cortex-A7采用三条流水线的方式
                     * 取指
                     * 译址
                     * 执行
                     * 当前指令完成取指后立即进行的是下一条指令的取指，PC+4
                     * 完成译址后PC+8
                     * 中断发生处于执行阶段，此时的PC指针已经直到当前指令的之后第二条指令了
                     * 如果不减4会漏掉PC+4这条已经完成取指正在译址的指令
                     */


FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0


