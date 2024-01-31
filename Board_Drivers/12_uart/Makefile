CSTDIO=$(wildcard stdio/lib/*.c)
CFILE=$(notdir $(CSTDIO))
COBJS=$(patsubst %.c,obj/%.o,$(CFILE))
SSTDIO=$(wildcard stdio/lib/*.S)
SCFILE=$(notdir $(SSTDIO))
SOBJS=$(patsubst %.S,obj/%.o,$(SFILE))
CC=arm-linux-gnueabihf-gcc
INCLUDE=-I include -I stdio/include

all:$(COBJS) $(SOBJS)
	@make -C src && make -C obj

obj/%.o:stdio/lib/%.c
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -O2 $(INCLUDE) -c $< -o $@

obj/%.o:stdio/lib/%.S
	$(CC) -Wall -nostdlib -O2 -c $< -o $@


.PHONY:clean
clean:
	rm -f ./obj/*.o ./dump/*.elf ./dump/*.dis ./bin/*.bin