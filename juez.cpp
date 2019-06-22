#include "juez.h"

/* TODO: Implementar */
static inline bool hay_ganador(const Tablero& t) {
	return false;
}

int juez(int cols, int rows, int c, int p, Jugador primero, Jugador segundo) {
	Tablero partida(cols, vector<int>(rows, 0));
	Fichas fichas(cols, 0);

	for (int i = 0; i < p; i++) {
		int jugada;
	       
		jugada = primero(partida, fichas, c, p, 1);
		partida[fichas[jugada]][jugada] = 1;
		fichas[jugada]++;
		if (hay_ganador(partida))
			return 1;

		jugada = primero(partida, fichas, c, p, 2);
		partida[fichas[jugada]][jugada] = 2;
		fichas[jugada]++;
		if (hay_ganador(partida))
			return 2;
	}

	return 0;
}
