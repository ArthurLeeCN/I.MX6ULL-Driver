SECTIONS{
    . = 0x87800000;
    .text :
    {
        start.o
        main.o
        *(.text)
    }
    .rodata ALIGN(4) : 
    {
        *(.rodata)
    }
    . = ALIGN(4);
    __bss_start = . ;
    .bss ALIGN(4) : 
    {
        *(.bss) *(COMMON)
    }
    __bss_end = . ;
}