.PHONY: all clean

CC=g++
CPP_STANDARD=c++11
CFLAGS= -std=$(CPP_STANDARD)

OBJS=jugador.o
BIN=jugador

all: jugador

jugador: main.cpp
	$(CC) $(CFLAGS) $< -o jugador

clean:
	rm -f $(OBJS)
	rm -f $(BIN)
