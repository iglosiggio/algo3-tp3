#include <iostream>

#include "juez.h"
#include "algorithm/jugador.h"

/* NOTA: Esto es código de prueba por ahora para mostrar cómo se usa juez
 *       pedorro que hice. Probablemente tengamos que agregar un par de
 *       punteros para utilzar como contexto en lugar de meter todo como
 *       globales en `evaluarTableros` */
struct scores greedy_conf {
	.posc3 = 10,
	.posc2 = 15,
	.posc1 = 20,
	.c3 = 100,
	.c2 = 300,
	.c1 = 10000,
	.bloqueos_c3 = 20,
	.bloqueos_c2 = 200,
	.bloqueos_c1 = 3000
};

int main (int argc, char** argv) {
	struct resultados partida = juez(
		10, 10, 7, 50, evaluarTableros, &greedy_conf, evaluarTableros,
		&greedy_conf
	);
	std::cout << "El ganador es: " << partida.ganador
		  << " a los " << partida.turnos << " turnos"
		  << std::endl;

	return 0;
}
