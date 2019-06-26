#include <iostream>

#include "juez.h"
#include "algorithm/jugador.h"
#include "puntuar_params.h"

#define STATIC_ARRAY_SIZE(array) (sizeof (array) / sizeof ((array)[0]))

const struct config_partida partidas[] = {
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
const int cant_partidas = STATIC_ARRAY_SIZE(partidas);

/* Recorre los arreglos de valores de cada parámetro */
#define EACH(param) for (int param : valores_ ## param)

int valores_p3[] = {5, 10, 15, 20};
int valores_p2[] = {15, 25, 35, 45};
int valores_p1[] = {20, 30, 40, 50};
int valores_c3[] = {150, 200, 250};
int valores_c2[] = {400, 500, 600};
int valores_c1[] = {1000000};
int valores_b3[] = {20, 50, 80, 110};
int valores_b2[] = {300, 400, 500, 600};
int valores_b1[] = {333333};

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
		std::cerr << "Procesados " << procesados << "/" << total
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
			procesados++;
		}
	}
	imprimir_params(mejores_params, mejor_puntaje);
	return 0;
}
