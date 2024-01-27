.global _start @全局标号

_start:
    /* GPIO时钟
     *在imxdownload添加的image头部里面，DCD已经了所有外设使用的时钟CCGR寄存器写了0xFFFFFFFF了
     *这里暂时禁用，更改image头部DCD配置信息的时候再启用 
     */

#    ldr r0, =0x020c406c @CCM_CCGR1寄存器地址，使能GPIO1时钟
#    ldr r1, =0xffffffff @为了方便把CCM_CCGR1全部写1，GPIO1的时钟只用写该寄存器的27-26位
#    str r1, [r0] @将r1值写入r0

    /* 管脚复用功能选择 */

    ldr r0, =0x020e0068 @IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03寄存器地址
    ldr r1, =0x00000005
    str r1, [r0]

    /* 配置管脚电气特性 */
    /*
     * bit 0:0:   0   低压摆率
     * bit 5:3:   110 驱动能力R0/6
     * bit 7:6:   01  速度100MHz
     * bit 11:11: 0   关闭开漏输出，使用推挽输出
     * bit 12:12: 0   关闭Pull/Keeper，Pull/Keeper防止外设突然掉电
     * bit 13:13: 0   Pull/keeper配置
     * bit 15:14: 00  使用100K下拉
     * bit 16:16: 0   关闭施密特触发器
     */

    ldr r0, =0x020e02f4 @IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03寄存器地址
    ldr r1, =0x00000070
    str r1, [r0]

    /* GPIO设置 */

    ldr r0, =0x0209c004 @GPIO1_GDIR地址
    ldr r1, =0x00000008 @GPIO1_IO03设置为输出
    str r1, [r0]

    /* 设置GPIO1_IO03输出低电平 */

    ldr r0, =0x0209c000 @GPIO1_DR地址
    ldr r1, =0x00000000
    ldr r1, [r0]

loop:
    b loop


