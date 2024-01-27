CC=arm-linux-gnueabihf-gcc
LN=arm-linux-gnueabihf-ld
OBJ=arm-linux-gnueabihf-objcopy
DUMP=arm-linux-gnueabihf-objdump
ADDR=0x87800000

all:leds.dis leds.bin

leds.dis:leds.elf
	$(DUMP) -D leds.elf > leds.dis

leds.bin:leds.elf
	$(OBJ) -O binary -S -g leds.elf leds.bin

leds.elf:leds.o
	$(LN) -Ttext $(ADDR) leds.o -o leds.elf

leds.o: leds.s
	$(CC) -g -c leds.s -o leds.o

.PHONY:clean
clean:
	rm -f leds.dis leds.bin leds.elf leds.o