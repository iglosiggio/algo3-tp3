CXXFLAGS+=-Wall

all:
	$(MAKE) -C src all

tags:
	ctags -R .

clean:
	rm -f genetico grid
	$(MAKE) -C src clean
	rm -f tags

genetico: genetico.cpp juez.cpp algorithm/jugador.cpp

grid: grid.cpp juez.cpp algorithm/jugador.cpp

.PHONY: clean all tags
