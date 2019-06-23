all:
	$(MAKE) -C src all

tags:
	ctags -R .

clean:
	$(MAKE) -C src clean
	rm -f tags

torneo: juez.o algorithm/jugador.o

.PHONY: clean all tags
