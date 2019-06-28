#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <vector>

using std::vector;
using Tablero = vector<vector<int>>;
using Fichas = vector<int>;

struct scores {
	int posc3;
	int posc2;
	int posc1;
	int c3;
	int c2;
	int c1;
	int bloqueos_c3;
	int bloqueos_c2;
	int bloqueos_c1;
};

int evaluarTableros(Tablero& tablero, Fichas& fichas, int c, int p, int player,
		    const void* ctx);
#endif
