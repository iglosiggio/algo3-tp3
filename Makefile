.PHONY: all clean

CXXFLAGS += -Wall -O3

all: jugador

jugador: main.cpp jugador.cpp params.cpp

clean:
	rm -f jugador
