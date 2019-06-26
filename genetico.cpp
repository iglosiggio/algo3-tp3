#include <iostream>
#include <vector>
#include <deque>
#include <random>

#include "juez.h"
#include "algorithm/jugador.h"
#include "puntuar_params.h"

std::default_random_engine gen;

struct ejemplar {
	struct scores params;
	float fitness;
};

/* Así std::sort me pone los mejores primero */
bool operator<(const struct ejemplar& a, const struct ejemplar& b) {
	return a.fitness > b.fitness;
}

using std::vector;
using poblacion = vector<struct ejemplar>;

const struct config_partida partidas[] = {
	{7, 6, 4},
	{15, 8, 5},
	{8, 13, 6}
};
const int cant_partidas = sizeof(partidas) / sizeof (partidas[0]);

static void fitness_torneo(poblacion& ejemplares) {
	for (const struct config_partida& p : partidas) {
		for (int i = 0; i < ejemplares.size(); i++)
		for (int j = i + 1; j < ejemplares.size(); j++) {
			struct resultados ida = juez(
				p.n, p.m, p.c, p.n * p.m,
				evaluarTableros, &ejemplares[i].params,
				evaluarTableros, &ejemplares[j].params
			);
			struct resultados vuelta = juez(
				p.n, p.m, p.c, p.n * p.m,
				evaluarTableros, &ejemplares[j].params,
				evaluarTableros, &ejemplares[i].params
			);

			switch (ida.ganador) {
				case 1:
					ejemplares[i].fitness += 3;
					break;
				case 2:
					ejemplares[j].fitness += 3;
					break;
				default:
					ejemplares[i].fitness += 1;
					ejemplares[j].fitness += 1;
					break;
			}

			switch (vuelta.ganador) {
				case 1:
					ejemplares[j].fitness += 3;
					break;
				case 2:
					ejemplares[i].fitness += 3;
					break;
				default:
					ejemplares[i].fitness += 1;
					ejemplares[j].fitness += 1;
					break;
			}
		}
	}
}

static void fitness_puntaje(poblacion& ejemplares) {
	for (struct ejemplar& ejemplar : ejemplares) {
		ejemplar.fitness = puntuar(&ejemplar.params);
	}
}

static const struct {
	const char* nombre;
	void (*evaluar)(poblacion&);
} evaluaciones[] = {
	{"torneo",	fitness_torneo},
	{"puntaje",	fitness_puntaje}
};

static struct scores crossover_moneda(const struct scores& a,
				      const struct scores& b) {
	struct scores resultado = a;
	std::bernoulli_distribution moneda(0.5);

	if (moneda(gen))
		resultado.posc3 = b.posc3;
	if (moneda(gen))
		resultado.posc2 = b.posc2;
	if (moneda(gen))
		resultado.posc1 = b.posc1;
	if (moneda(gen))
		resultado.c3 = b.c3;
	if (moneda(gen))
		resultado.c2 = b.c2;
	if (moneda(gen))
		resultado.c1 = b.c1;
	if (moneda(gen))
		resultado.bloqueos_c3 = b.bloqueos_c3;
	if (moneda(gen))
		resultado.bloqueos_c2 = b.bloqueos_c2;
	if (moneda(gen))
		resultado.bloqueos_c1 = b.bloqueos_c1;

	return resultado;
}

static struct scores crossover_promedio(const struct scores& a,
					const struct scores& b) {
	struct scores resultado;

	resultado.posc3 = (a.posc3 + b.posc3) / 2;
	resultado.posc2 = (a.posc2 + b.posc2) / 2;
	resultado.posc1 = (a.posc1 + b.posc1) / 2;
	resultado.c3 = (a.c3 + b.c3) / 2;
	resultado.c2 = (a.c2 + b.c2) / 2;
	resultado.c1 = (a.c1 + b.c1) / 2;
	resultado.bloqueos_c3 = (a.bloqueos_c3 + b.bloqueos_c3) / 2;
	resultado.bloqueos_c2 = (a.bloqueos_c2 + b.bloqueos_c2) / 2;
	resultado.bloqueos_c1 = (a.bloqueos_c1 + b.bloqueos_c1) / 2;

	return resultado;
}

static const struct {
	const char* nombre;
	struct scores (*cruzar)(const struct scores&, const struct scores&);
} crossovers[] = {
	{"moneda",	crossover_moneda},
	{"promedio",	crossover_promedio}
};

static void mutacion_uniforme(struct scores& a) {
	std::bernoulli_distribution moneda(0.01);
	std::uniform_real_distribution<float> uniforme(0.8, 1.2);

	if (moneda(gen))
		a.posc3 *= uniforme(gen);
	if (moneda(gen))
		a.posc2 *= uniforme(gen);
	if (moneda(gen))
		a.posc1 *= uniforme(gen);
	if (moneda(gen))
		a.c3 *= uniforme(gen);
	if (moneda(gen))
		a.c2 *= uniforme(gen);
	if (moneda(gen))
		a.c1 *= uniforme(gen);
	if (moneda(gen))
		a.bloqueos_c3 *= uniforme(gen);
	if (moneda(gen))
		a.bloqueos_c2 *= uniforme(gen);
	if (moneda(gen))
		a.bloqueos_c1 *= uniforme(gen);
}

static void mutacion_normal(struct scores& a) {
	std::uniform_real_distribution<float> normal(1, 0.05);

	a.posc3 *= normal(gen);
	a.posc2 *= normal(gen);
	a.posc1 *= normal(gen);
	a.c3 *= normal(gen);
	a.c2 *= normal(gen);
	a.c1 *= normal(gen);
	a.bloqueos_c3 *= normal(gen);
	a.bloqueos_c2 *= normal(gen);
	a.bloqueos_c1 *= normal(gen);
}

static const struct {
	const char* nombre;
	void (*mutar)(struct scores&);
} mutations[] = {
	{"uniforme",	mutacion_uniforme},
	{"normal",	mutacion_normal}
};

static poblacion seleccionar_mejores(const poblacion& ejemplares, int k) {
	return poblacion(ejemplares.begin(), ejemplares.begin() + k);
}

static poblacion seleccionar_sorteando(const poblacion& ejemplares, int k) {
	std::deque<struct ejemplar> cola(ejemplares.begin(), ejemplares.end());
	poblacion resultado;
	resultado.reserve(k);

	while (resultado.size() < k) {
		const struct ejemplar& ejemplar = cola.front();
		std::bernoulli_distribution moneda(ejemplar.fitness);

		if (moneda(gen))
			resultado.push_back(ejemplar);
		else
			cola.push_back(ejemplar);

		cola.pop_front();
	}

	return resultado;
}

static const struct {
	const char* nombre;
	poblacion (*seleccionar)(const poblacion&, int);
} selectores[] = {
	{"mejores",	seleccionar_mejores},
	{"sortear",	seleccionar_sorteando}
};

int main (int argc, char** argv) {
	return 0;
}
