CC=arm-linux-gnueabihf-gcc
PROJ=ledc

SRC=$(wildcard *.s)
OBJS=$(patsubst %.s,../../obj/%.o,$(SRC))

all:$(OBJS)

../../obj/%.o:%.s
	$(CC) -g -c $< -o $@