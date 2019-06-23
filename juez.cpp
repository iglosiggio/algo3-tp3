#include "juez.h"

static inline bool hay_c(const Tablero& t, int c, int i, int j, int di,
			 int dj) {
	int jugador = t[i][j];

	if (jugador == 0)
		return false;

	do {
		c--;
		i += di;
		j += dj;
		if (t[i][j] != jugador)
			return false;
	} while (c);

	return true;
}

static inline bool hay_ganador(const Tablero& t, int c) {
	int filas = t.size();
	int columnas = t[0].size();

	for (int i = 0; i < filas; i++)
		for (int j = 0; j < columnas; j++) {
			bool hay_espacio_e = columnas - j + 1 >= c;
			bool hay_espacio_s = filas - i + 1 >= c;
			bool hay_espacio_se = hay_espacio_e && hay_espacio_s;
			bool hay_espacio_sw = hay_espacio_s && j + 1 >= c;

			if (   hay_espacio_e  && hay_c(t, c, i, j, 0,  1)
			    || hay_espacio_s  && hay_c(t, c, i, j, 1,  0)
			    || hay_espacio_se && hay_c(t, c, i, j, 1,  1)
			    || hay_espacio_sw && hay_c(t, c, i, j, 1, -1))
				return true;
		}

	return false;
}

#include <iostream>

int juez(int cols, int rows, int c, int p, Jugador primero, Jugador segundo) {
	Tablero partida(cols, vector<int>(rows, 0));
	Fichas fichas(cols, 0);

	for (int i = 0; i < p; i++) {
		int jugada;
	       
		jugada = primero(partida, fichas, c, p, 1);
		partida[fichas[jugada]][jugada] = 1;
		fichas[jugada]++;
		if (hay_ganador(partida, c))
			return 1;

		jugada = primero(partida, fichas, c, p, 2);
		partida[fichas[jugada]][jugada] = 2;
		fichas[jugada]++;
		if (hay_ganador(partida, c))
			return 2;
	}

	return 0;
}
