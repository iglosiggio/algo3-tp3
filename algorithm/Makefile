.PHONY: all clean

CXXFLAGS += -Wall
ESTRATEGIAS = $(wildcard estrategias/*)
JUGADORES = $(ESTRATEGIAS:estrategias/%.cpp=jugador.%)

all: $(JUGADORES)

jugador.%: main.cpp jugador.cpp estrategias/%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(JUGADORES)
