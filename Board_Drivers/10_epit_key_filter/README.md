此为I.MX6ULL实验中C语言实现LED灯的项目形式
该项目目录格式为：

.
├── 10_epit_key_filter.code-workspace
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
│   ├── core.h
│   ├── epit.h
│   ├── exti.h
│   ├── fsl_common.h
│   ├── fsl_iomuxc.h
│   ├── gpio.h
│   ├── IMX6U_INT.h
│   ├── imx6ull_core.h
│   ├── key.h
│   ├── led.h
│   ├── main.h
│   ├── MCIMX6Y2.h
│   └── time.h
├── Makefile
├── obj
│   ├── beep.o
│   ├── clk.o
│   ├── epit.o
│   ├── exti.o
│   ├── gpio.o
│   ├── IMX6U_INT.o
│   ├── imx6ull.lds
│   ├── key.o
│   ├── led.o
│   ├── main.o
│   ├── Makefile
│   ├── start.o
│   └── time.o
├── README.md
└── src
    ├── asm
    │   ├── Makefile
    │   └── start.s
    ├── c
    │   ├── beep.c
    │   ├── clk.c
    │   ├── epit.c
    │   ├── exti.c
    │   ├── gpio.c
    │   ├── IMX6U_INT.c
    │   ├── key.c
    │   ├── led.c
    │   ├── main.c
    │   ├── Makefile
    │   └── time.c
    └── Makefile

其中src/asm下的start.s是芯片的启动文件，控制芯片SP指针，进入C语言环境。src/asm/start.s以及src/c/main.c不可删除，必须实现
include目录下time.h,led.h,board_init.h均为库函数文件，core.h定义了芯片的各项寄存器（已弃用）,imx6ull_core.h为STM32风格的寄存器配置（该实验不使用）
fsl_common.h，fsl_iomuxc.h，MCIMX6Y2.h为NXP提供的SDK驱动文件
本项目重新封装了GPIO,在之后的项目中直接使用gpio.h中提供的函数即可完成GPIO初始化，读写操作
同时，本项目修复了使用静态变量可能出错的问题，将obj目录下的imx6ull.lds链接脚本中的__bss_start进行了四字节对齐，防止了start.s中对bss区进行清零操作时可能会产生的程序跑飞的错误
使用EPIT计时器实现了按键中断的消抖