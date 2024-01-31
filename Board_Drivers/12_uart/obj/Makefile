LN=arm-linux-gnueabihf-ld
CP=arm-linux-gnueabihf-objcopy
DUMP=arm-linux-gnueabihf-objdump
ADDR=0x87800000
PROJ=int
FILE=$(wildcard *.o)
OBJS=start.o main.o $(filter-out start.o main.o,$(FILE))
LIBPATH=-lgcc -L /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4

all:../dump/$(PROJ).dis ../bin/$(PROJ).bin

../dump/$(PROJ).dis:../dump/$(PROJ).elf
	$(DUMP) -D -m arm $< > $@

../bin/$(PROJ).bin:../dump/$(PROJ).elf
	$(CP) -O binary -S $< $@

../dump/$(PROJ).elf:$(OBJS)
	$(LN) -T imx6ull.lds $^ -o $@ $(LIBPATH)