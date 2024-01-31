CC=arm-linux-gnueabihf-gcc
INCLUDE=-I ../../include -I ../../stdio/include
PROJ=ledc

SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,../../obj/%.o,$(SRC))

all:$(OBJS)

../../obj/%.o:%.c
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -O2 $(INCLUDE) -c $< -o $@