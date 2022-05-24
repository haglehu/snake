##
# Snake
#
# @file
# @version 0.1
CC = gcc
OUT = ./bin/game
FLAGS = -O3 -std=c99 -g -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Iinc/

all:
	mkdir -p bin
	$(CC) src/*.c $(FLAGS) -o $(OUT)

make: all

run: all
	./$(OUT)
# end
