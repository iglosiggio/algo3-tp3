.PHONY: all clean

CXXFLAGS += -Wall

all: jugador.goloso jugador.grid-search jugador.genetico

jugador.%: main.cpp jugador.cpp estrategias/%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f jugador.goloso jugador.grid-search jugador.genetico
