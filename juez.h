#ifndef __JUEZ_H__
#define __JUEZ_H__
#include <vector>

using std::vector;

/* 0 significa no hay ficha
 * 1 significa la ficha es mia
 * 2 significa la fichja es del enemigo */
using Tablero = vector<vector<int>>;
using Fichas = vector<int>;

using Jugador = int (*)(Tablero, Fichas, int c, int p, int player,
			const void* ctx);

/* 0 es empate
 * 1 es ganó el primero
 * 2 es ganó el segundo */
int juez(int cols, int rows, int c, int p, Jugador primero, const void* ctx1,
	 Jugador segundo, const void* ctx2);

#endif
