#include "juez.h"

static inline bool hay_c(const Tablero& t, int c, int i, int j, int di,
			 int dj) {
	int jugador = t[i][j];

	if (jugador == 0)
		return false;

	while (--c) {
		i += di;
		j += dj;
		if (t[i][j] != jugador)
			return false;
	}

	return true;
}

static inline bool hay_ganador(const Tablero& t, int c) {
	int filas = t.size();
	int columnas = t[0].size();

	for (int i = 0; i < filas; i++)
		for (int j = 0; j < columnas; j++) {
			bool hay_espacio_e = columnas - j >= c;
			bool hay_espacio_s = filas - i >= c;
			bool hay_espacio_se = hay_espacio_e && hay_espacio_s;
			bool hay_espacio_sw = hay_espacio_s && j + 1 >= c;

			if (   (hay_espacio_e  && hay_c(t, c, i, j, 0,  1))
			    || (hay_espacio_s  && hay_c(t, c, i, j, 1,  0))
			    || (hay_espacio_se && hay_c(t, c, i, j, 1,  1))
			    || (hay_espacio_sw && hay_c(t, c, i, j, 1, -1)))
				return true;
		}

	return false;
}

static inline int min(int a, int b) {
	return a < b ? a : b;
}

struct resultados juez(int cols, int rows, int c, int p, Jugador primero,
	const void* ctx1, Jugador segundo, const void* ctx2) {
	int turnos = min(2 * p, rows * cols);
	Tablero partida(rows, vector<int>(cols, 0));
	Fichas fichas(cols, 0);

	for (int i = 0; i < turnos; i++) {
		int jugada;
	       
		jugada = primero(partida, fichas, c, p, 1, ctx1);
		partida[fichas[jugada]][jugada] = 1;
		fichas[jugada]++;
		if (hay_ganador(partida, c))
			return {1, i};

		i++;
		if (i >= turnos)
			return {0, i};

		jugada = segundo(partida, fichas, c, p, 2, ctx2);
		partida[fichas[jugada]][jugada] = 2;
		fichas[jugada]++;
		if (hay_ganador(partida, c))
			return {2, i};
	}

	return {0, turnos};
}
