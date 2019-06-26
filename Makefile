all:
	$(MAKE) -C src all

tags:
	ctags -R .

clean:
	$(MAKE) -C src clean
	rm -f tags

torneo: torneo.cpp juez.cpp algorithm/jugador.cpp

grid: grid.cpp juez.cpp algorithm/jugador.cpp

.PHONY: clean all tags
