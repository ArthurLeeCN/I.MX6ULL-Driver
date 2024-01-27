CC=arm-linux-gnueabihf-gcc
LN=arm-linux-gnueabihf-ld
CP=arm-linux-gnueabihf-objcopy
DUMP=arm-linux-gnueabihf-objdump
ADDR=0x87800000
PROJ=ledc
OBJ=start.o main.o time.o board_init.o led.o

all:$(PROJ).dis $(PROJ).bin

$(PROJ).dis:$(PROJ).elf
	$(DUMP) -D -m arm $< > $@

$(PROJ).bin:$(PROJ).elf
	$(CP) -O binary -S $< $@

$(PROJ).elf:$(OBJ)
	$(LN) -Ttext $(ADDR) $^ -o $@

%.o: %.s
	$(CC) -g -c $< -o $@

%.o: %.c
	$(CC) -g -c $< -o $@


.PHONY:clean
clean:
	rm -f *.o *.elf *.dis