#include <iostream>

#include "juez.h"
#include "algorithm/jugador.h"

/* NOTA: Esto es código de prueba por ahora para mostrar cómo se usa juez
 *       pedorro que hice. Probablemente tengamos que agregar un par de
 *       punteros para utilzar como contexto en lugar de meter todo como
 *       globales en `evaluarTableros` */
int main (int argc, char** argv) {
	std::cout << "El ganador es: "
		  << juez(10, 10, 7, 50, evaluarTableros, evaluarTableros)
		  << std::endl;

	return 0;
}
