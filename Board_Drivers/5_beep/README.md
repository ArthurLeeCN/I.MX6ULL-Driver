此为I.MX6ULL实验中C语言实现LED灯的项目形式
该项目目录格式为：
.
├── 4_ledc_sdk.code-workspace
├── bin
│   └── ledc.bin
├── download
│   ├── download.sh
│   ├── imxdownload
│   └── load.imx
├── dump
│   ├── ledc.dis
│   └── ledc.elf
├── include
│   ├── board_init.h
│   ├── cc.h
│   ├── core.h
│   ├── fsl_common.h
│   ├── fsl_iomuxc.h
│   ├── imx6ull_core.h
│   ├── led.h
│   ├── MCIMX6Y2.h
│   └── time.h
├── Makefile
├── obj
│   ├── board_init.o
│   ├── imx6ull.lds
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
    │   ├── board_init.c
    │   ├── led.c
    │   ├── main.c
    │   ├── Makefile
    │   └── time.c
    └── Makefile

其中src/asm下的start.s是芯片的启动文件，控制芯片SP指针，进入C语言环境。src/asm/start.s以及src/c/main.c不可删除，必须实现
include目录下time.h,led.h,board_init.h均为库函数文件，core.h定义了芯片的各项寄存器（已弃用）,imx6ull_core.h为STM32风格的寄存器配置（该实验不使用）
fsl_common.h，fsl_iomuxc.h，MCIMX6Y2.h为NXP提供的SDK驱动文件