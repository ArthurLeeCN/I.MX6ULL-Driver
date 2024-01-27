LN=arm-linux-gnueabihf-ld
CP=arm-linux-gnueabihf-objcopy
DUMP=arm-linux-gnueabihf-objdump
ADDR=0x87800000
PROJ=ledc
FILE=$(wildcard *.o)
OBJS=start.o main.o $(filter-out start.o main.o,$(FILE))

all:../dump/$(PROJ).dis ../bin/$(PROJ).bin

../dump/$(PROJ).dis:../dump/$(PROJ).elf
	$(DUMP) -D -m arm $< > $@

../bin/$(PROJ).bin:../dump/$(PROJ).elf
	$(CP) -O binary -S $< $@

../dump/$(PROJ).elf:$(OBJS)
	$(LN) -T imx6ull.lds $^ -o $@