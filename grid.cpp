#include <iostream>

#include "juez.h"
#include "algorithm/jugador.h"

struct scores bloqueadora {
	.posc3 = 5,
	.posc2 = 15,
	.posc1 = 20,
	.c3 = 150,
	.c2 = 400,
	.c1 = 1000000,
	.bloqueos_c3 = 200,
	.bloqueos_c2 = 500,
	.bloqueos_c1 = 333333
};

struct scores agresiva {
	.posc3 = 5,
	.posc2 = 15,
	.posc1 = 20,
	.c3 = 200,
	.c2 = 500,
	.c1 = 1000000,
	.bloqueos_c3 = 20,
	.bloqueos_c2 = 300,
	.bloqueos_c1 = 333333
};

struct scores al_medio {
	.posc3 = 10,
	.posc2 = 25,
	.posc1 = 40,
	.c3 = 150,
	.c2 = 500,
	.c1 = 1000000,
	.bloqueos_c3 = 20,
	.bloqueos_c2 = 600,
	.bloqueos_c1 = 333333
};

struct config_partida {
	int n, m, c;
} partidas[] = {
	{6, 5, 3},
	{9, 5, 3},
	{8, 7, 4},
	{12, 6, 4},
	{15, 8, 5},
	{18, 9, 6},
	{12, 11, 6},
	{14, 13, 7},
	{21, 11, 7},
	{16, 15, 8},
	{24, 12, 8},
	{18, 17, 9},
	{20, 19, 10},
	{30, 15, 10},
};

/* Recorre los arreglos de valores de cada parámetro */
#define EACH(param) \
	for (int i = 0, param = valores_ ## param [0]; \
	     i < STATIC_ARRAY_SIZE(valores_ ## param); \
	     i++, param = valores_ ## param[i])

int valores_p3[] = {5, 10, 15, 20};
int valores_p2[] = {15, 25, 35, 45};
int valores_p1[] = {20, 30, 40, 50};
int valores_c3[] = {150, 200, 250};
int valores_c2[] = {400, 500, 600};
int valores_c1[] = {1000000};
int valores_b3[] = {20, 50, 80, 110};
int valores_b2[] = {300, 400, 500, 600};
int valores_b1[] = {333333};

#define STATIC_ARRAY_SIZE(array) (sizeof (array) / sizeof ((array)[0]))

const int total = STATIC_ARRAY_SIZE(valores_p3) * STATIC_ARRAY_SIZE(valores_p2)
		* STATIC_ARRAY_SIZE(valores_p1) * STATIC_ARRAY_SIZE(valores_c3)
		* STATIC_ARRAY_SIZE(valores_c2) * STATIC_ARRAY_SIZE(valores_c1)
		* STATIC_ARRAY_SIZE(valores_b3) * STATIC_ARRAY_SIZE(valores_b2)
		* STATIC_ARRAY_SIZE(valores_b1);

#define PRINT_FIELD(val, field) \
	std::cout << #field "\t" << val.field << std::endl

void imprimir_params(const struct scores& params, int puntaje) {
	std::cout << "PUNTAJE\t" << puntaje << std::endl;
	PRINT_FIELD(params,  posc3);
	PRINT_FIELD(params,  posc2);
	PRINT_FIELD(params,  posc1);
	PRINT_FIELD(params,  c3);
	PRINT_FIELD(params,  c2);
	PRINT_FIELD(params,  c1);
	PRINT_FIELD(params,  bloqueos_c3);
	PRINT_FIELD(params,  bloqueos_c2);
	PRINT_FIELD(params,  bloqueos_c1);
}

#define PARTIDA(enemigo) \
	struct resultados enemigo ## _ida = \
		juez(partida.n, partida.m, partida.c, partida.n * partida.m, \
		     evaluarTableros, params, evaluarTableros, &enemigo); \
	struct resultados enemigo ## _vuelta = \
		juez(partida.n, partida.m, partida.c, partida.n * partida.m, \
		     evaluarTableros, &enemigo, evaluarTableros, params);

static inline int sumar_ida(struct resultados resultados) {
	switch (resultados.ganador) {
		/* Ganó */
		case 1:
			return 250 - resultados.turnos / 2;
		/* Perdió */
		case 2:
			return -400 + resultados.turnos / 2;
		/* Empató */
		default:
			return 0;
	}
}

static inline int sumar_vuelta(struct resultados resultados) {
	switch (resultados.ganador) {
		/* Ganó */
		case 2:
			return 500 - resultados.turnos / 2;
		/* Perdió */
		case 1:
			return -250 + resultados.turnos / 2;
		/* Empató */
		default:
			return 100;
	}
}

static int puntuar(const struct scores* params) {
	int puntaje = 0;

	for (int i = 0; i < STATIC_ARRAY_SIZE(partidas); i++) {
		struct config_partida& partida = partidas[i];

		PARTIDA(bloqueadora);
		PARTIDA(agresiva);
		PARTIDA(al_medio);

		puntaje += sumar_ida(bloqueadora_ida);
		puntaje += sumar_ida(agresiva_ida);
		puntaje += sumar_ida(al_medio_ida);
		puntaje += sumar_vuelta(bloqueadora_vuelta);
		puntaje += sumar_vuelta(agresiva_vuelta);
		puntaje += sumar_vuelta(al_medio_vuelta);
	}

	return puntaje;
}

int main (int argc, char** argv) {
	int procesados = 0;
	int mejor_puntaje = INT32_MIN;
	struct scores mejores_params = {
		valores_p3[0], valores_p2[0], valores_p1[0],
		valores_c3[0], valores_c2[0], valores_c1[0],
		valores_b3[0], valores_b2[0], valores_b1[0],
	};

	/* Sí, son 9 fors anidados */
	EACH(p3)
	EACH(p2)
	EACH(p1)
	EACH(c3)
	EACH(c2)
	EACH(c1) {
		std::cout << "Procesados " << procesados << "/" << total
			  << std::endl;
		EACH(b3)
		EACH(b2)
		EACH(b1) {
			struct scores params = {
				p3, p2, p1, c3, c2, c1, b3, b2, b1
			};
			int puntaje = puntuar(&params);
			if (puntaje > mejor_puntaje) {
				mejor_puntaje = puntaje;
				mejores_params = params;
			}
		}
	}
	imprimir_params(mejores_params, mejor_puntaje);
	return 0;
}
