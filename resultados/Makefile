resultados_geneticos = $(wildcard *.genetico)

all: $(resultados_geneticos:=.pdf)

%.genetico.pdf: %.genetico
	../grafico-fitness.py $@ "Evolución del fitness promedio" < $<

clean:
	rm -f *.pdf

.PHONY: all clean
