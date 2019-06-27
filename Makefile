CXXFLAGS+=-Wall

all: genetico grid
	$(MAKE) -C src all
	$(MAKE) -C algorithm all
	$(MAKE) -C resultados all
	$(MAKE) -C informe all

tags:
	ctags -R .

clean:
	rm -f genetico grid tags
	$(MAKE) -C src clean
	$(MAKE) -C algorithm clean
	$(MAKE) -C resultados clean
	$(MAKE) -C informe clean

genetico: genetico.cpp juez.cpp algorithm/jugador.cpp

grid: grid.cpp juez.cpp algorithm/jugador.cpp

.PHONY: clean all tags
