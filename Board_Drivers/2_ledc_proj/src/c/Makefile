CC=arm-linux-gnueabihf-gcc
INCLUDE=-I ../../include
PROJ=ledc

SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,../../obj/%.o,$(SRC))

all:$(OBJS)

../../obj/%.o:%.c
	$(CC) -g $(INCLUDE) -c $< -o $@