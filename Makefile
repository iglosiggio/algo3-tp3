all:
	$(MAKE) -C src all

tags:
	ctags -R .

clean:
	$(MAKE) -C src clean
	rm -f tags

.PHONY: clean all
