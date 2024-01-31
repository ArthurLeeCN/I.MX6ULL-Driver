此为I.MX6ULL实验中C语言实现LED灯的项目形式
该项目目录格式为：

.
├── 12_uart.code-workspace
├── bin
│   └── int.bin
├── download
│   ├── download.sh
│   ├── imxdownload
│   └── load.imx
├── dump
│   ├── int.dis
│   └── int.elf
├── include
│   ├── beep.h
│   ├── cc.h
│   ├── clk.h
│   ├── core_ca7.h
│   ├── epit.h
│   ├── exti.h
│   ├── fsl_common.h
│   ├── fsl_iomuxc.h
│   ├── gpio.h
│   ├── gpt.h
│   ├── IMX6U_INT.h
│   ├── key.h
│   ├── led.h
│   ├── main.h
│   ├── MCIMX6Y2.h
│   └── uart.h
├── Makefile
├── obj
│   ├── beep.o
│   ├── clk.o
│   ├── ctype.o
│   ├── div64.o
│   ├── epit.o
│   ├── exti.o
│   ├── gpio.o
│   ├── gpt.o
│   ├── IMX6U_INT.o
│   ├── imx6ull.lds
│   ├── key.o
│   ├── led.o
│   ├── main.o
│   ├── Makefile
│   ├── muldi3.o
│   ├── printf.o
│   ├── start.o
│   ├── string.o
│   ├── uart.o
│   └── vsprintf.o
├── README.md
├── src
│   ├── asm
│   │   ├── Makefile
│   │   └── start.s
│   ├── c
│   │   ├── beep.c
│   │   ├── clk.c
│   │   ├── epit.c
│   │   ├── exti.c
│   │   ├── gpio.c
│   │   ├── gpt.c
│   │   ├── IMX6U_INT.c
│   │   ├── key.c
│   │   ├── led.c
│   │   ├── main.c
│   │   ├── Makefile
│   │   └── uart.c
│   └── Makefile
└── stdio
    ├── include
    │   ├── ctype.h
    │   ├── div64.h
    │   ├── gcclib.h
    │   ├── kernel.h
    │   ├── printf.h
    │   ├── stdio.h
    │   ├── string.h
    │   ├── system.h
    │   ├── types.h
    │   └── vsprintf.h
    └── lib
        ├── ctype.c
        ├── div64.c
        ├── lib1funcs.S
        ├── muldi3.c
        ├── printf.c
        ├── string.c
        └── vsprintf.c

其中src/asm下的start.s是芯片的启动文件，控制芯片SP指针，进入C语言环境。src/asm/start.s以及src/c/main.c不可删除，必须实现
include目录下time.h,led.h,board_init.h均为库函数文件，core.h定义了芯片的各项寄存器（已移除）,imx6ull_core.h为STM32风格的寄存器配置（已移除）
fsl_common.h，fsl_iomuxc.h，MCIMX6Y2.h为NXP提供的SDK驱动文件
本项目重新封装了GPIO,在之后的项目中直接使用gpio.h中提供的函数即可完成GPIO初始化，读写操作
同时，本项目修复了使用静态变量可能出错的问题，将obj目录下的imx6ull.lds链接脚本中的__bss_start进行了四字节对齐，防止了start.s中对bss区进行清零操作时可能会产生的程序跑飞的错误
使用EPIT计时器（32位向下计数器）实现了按键中断的消抖，使用IPG_CLK
使用GPT计数器（32位向上计数器）实现精准计时，使用IPG_CLK
移植了stdio中的printf和scanf，使用UART1输出，但该printf和scanf不支持浮点计算