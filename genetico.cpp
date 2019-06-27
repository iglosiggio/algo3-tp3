#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>

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

using std::string;
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
		for (long unsigned i = 0; i < ejemplares.size(); i++)
		for (long unsigned j = i + 1; j < ejemplares.size(); j++) {
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
	/* Perder todas las partidas en el turno 0 */
	const int minimo_puntaje = (-400 + -250) * 3 * 3;

	for (struct ejemplar& ejemplar : ejemplares) {
		ejemplar.fitness = puntuar(&ejemplar.params) - minimo_puntaje;
	}
}

struct evaluador {
	string nombre;
	void (*evaluar)(poblacion&);
};

static const vector<struct evaluador> evaluaciones = {
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

struct cruzador {
	string nombre;
	struct scores (*cruzar)(const struct scores&, const struct scores&);
};

static const vector<struct cruzador> crossovers = {
	{"moneda",	crossover_moneda},
	{"promedio",	crossover_promedio}
};

static void mutacion_uniforme(struct scores& a) {
	std::bernoulli_distribution moneda(0.01);
	std::uniform_real_distribution<float> uniforme(-0.2, 0.2);

	a.posc3 += moneda(gen) * uniforme(gen) * a.posc3;
	a.posc2 += moneda(gen) * uniforme(gen) * a.posc2;
	a.posc1 += moneda(gen) * uniforme(gen) * a.posc1;
	a.c3 += moneda(gen) * uniforme(gen) * a.c3;
	a.c2 += moneda(gen) * uniforme(gen) * a.c2;
	a.c1 += moneda(gen) * uniforme(gen) * a.c1;
	a.bloqueos_c3 += moneda(gen) * uniforme(gen) * a.bloqueos_c3;
	a.bloqueos_c2 += moneda(gen) * uniforme(gen) * a.bloqueos_c2;
	a.bloqueos_c1 += moneda(gen) * uniforme(gen) * a.bloqueos_c1;
}

static void mutacion_normal(struct scores& a) {
	std::bernoulli_distribution moneda(0.01);
	std::uniform_real_distribution<float> normal(0, 0.1);

	a.posc3 += moneda(gen) * normal(gen) * a.posc3;
	a.posc2 += moneda(gen) * normal(gen) * a.posc2;
	a.posc1 += moneda(gen) * normal(gen) * a.posc1;
	a.c3 += moneda(gen) * normal(gen) * a.c3;
	a.c2 += moneda(gen) * normal(gen) * a.c2;
	a.c1 += moneda(gen) * normal(gen) * a.c1;
	a.bloqueos_c3 += moneda(gen) * normal(gen) * a.bloqueos_c3;
	a.bloqueos_c2 += moneda(gen) * normal(gen) * a.bloqueos_c2;
	a.bloqueos_c1 += moneda(gen) * normal(gen) * a.bloqueos_c1;
}

struct mutador {
	string nombre;
	void (*mutar)(struct scores&);
};

static const vector<struct mutador> mutaciones = {
	{"uniforme",	mutacion_uniforme},
	{"normal",	mutacion_normal}
};

static poblacion seleccionar_mejores(const poblacion& ejemplares,
				     long unsigned k) {
	return poblacion(ejemplares.begin(), ejemplares.begin() + k);
}

static poblacion seleccionar_sorteando(const poblacion& ejemplares,
				       long unsigned k) {
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

struct selector {
	string nombre;
	poblacion (*seleccionar)(const poblacion&, long unsigned);
};

static const vector<struct selector> selectores = {
	{"mejores",	seleccionar_mejores},
	{"sortear",	seleccionar_sorteando}
};

static inline poblacion nueva_poblacion(int tamanio) {
	poblacion resultado;
	resultado.reserve(tamanio);

	std::uniform_int_distribution<int> dado(0, 1000);

	for (int i = 0; i < tamanio; i++) {
		resultado.push_back({{
			dado(gen), dado(gen), dado(gen), dado(gen), dado(gen),
			dado(gen), dado(gen), dado(gen), dado(gen)
		}, 0});
	}

	return resultado;
}

static inline void imprimir_fitness(const poblacion& poblacion, int gen) {
	using std::cout;
	using std::endl;

	float fitness_total = 0;
	for (const struct ejemplar& e : poblacion)
		fitness_total += e.fitness;

	float fitness_promedio = fitness_total / poblacion.size();
	float fitness_error_cuadrado = 0;
	for (const struct ejemplar& e : poblacion)
		fitness_error_cuadrado += (e.fitness - fitness_promedio)
					* (e.fitness - fitness_promedio);

	float mayor_fitness = poblacion[0].fitness;
	const struct scores& mejor = poblacion[0].params;

	/* Formato:
	 * TIPO    GEN    CAMPO1    CAMPO2    CAMPO3    ...    CAMPOn */
	cout << "data\t"
	     << gen << "\t"
	     << fitness_promedio << "\t"
	     << sqrt(fitness_error_cuadrado / (poblacion.size() - 1)) << endl;
	cout << "mejor\t"
	     << gen << "\t"
	     << mayor_fitness << "\t"
	     << mejor.posc3 << "\t"
	     << mejor.posc2 << "\t"
	     << mejor.posc1 << "\t"
	     << mejor.c3 << "\t"
	     << mejor.c2 << "\t"
	     << mejor.c1 << "\t"
	     << mejor.bloqueos_c3 << "\t"
	     << mejor.bloqueos_c2 << "\t"
	     << mejor.bloqueos_c1 << endl;
	for (const struct ejemplar& e : poblacion) {
		const struct scores& s = e.params;
		cout << "ejemplar\t"
		     << gen << "\t"
		     << e.fitness << "\t"
		     << s.posc3 << "\t"
		     << s.posc2 << "\t"
		     << s.posc1 << "\t"
		     << s.c3 << "\t"
		     << s.c2 << "\t"
		     << s.c1 << "\t"
		     << s.bloqueos_c3 << "\t"
		     << s.bloqueos_c2 << "\t"
		     << s.bloqueos_c1 << endl;
	}
}

template <class T>
static inline T buscar(const char* nombre, const vector<T>& opciones) {
	for (const auto& opcion : opciones)
		if (opcion.nombre == nombre)
			return opcion;
	throw "No encontrado";
}

template <class T>
static inline void opciones_param(const char* nombre, const vector<T>& opciones) {
	using std::cout;
	using std::endl;

	cout << "\t " << nombre << "\t = " << opciones[0].nombre;

	for (unsigned long i = 1; i < opciones.size(); i++)
		cout << " | " << opciones[i].nombre;

	cout << endl;
}

int main (int argc, char** argv) {
	using std::cout;
	using std::endl;
	using std::stoi;
	using std::sort;

	int generaciones;
	struct evaluador evaluador;
	struct cruzador cruzador;
	struct mutador mutador;
	struct selector selector;

	try {
		if (argc != 6)
			throw "Pocos params";

		generaciones = stoi(argv[1]);
		evaluador = buscar(argv[2], evaluaciones);
		cruzador = buscar(argv[3], crossovers);
		mutador = buscar(argv[4], mutaciones);
		selector = buscar(argv[5], selectores);
	} catch (...) {
		cout << "Uso: " << argv[0]
		     << " <generaciones> <fit> <cross> <mut> <sel>" << endl;
		cout << "\t generaciones = número" << endl;
		opciones_param("fit", evaluaciones);
		opciones_param("cross", crossovers);
		opciones_param("mut", mutaciones);
		opciones_param("sel", selectores);
		return 1;
	}

	const int K = 5;
	const int tamanio_poblacion = 50;
	/* Generamos la poblacion inicial */
	poblacion actual = nueva_poblacion(tamanio_poblacion);

	for (int i = 0; i < generaciones; i++) {
		/* 1. Evalúo la aptitud de cada ejemplar */
		evaluador.evaluar(actual);
		sort(actual.begin(), actual.end());

		imprimir_fitness(actual, i);

		float fitness_total = 0;
		for (const struct ejemplar& e : actual)
			fitness_total += e.fitness;

		/* Normalizo los fitness para el selector */
		for (struct ejemplar& e : actual)
			e.fitness /= fitness_total;

		/* 2. Selecciono un subconjunto de la población */
		actual = selector.seleccionar(actual, K);
		actual.reserve(tamanio_poblacion);

		/* Limpio los valores de fitness de los nuevos */
		for (struct ejemplar& e : actual)
			e.fitness = 0;

		/* Duplico los padres (en la nueva generación los muto). */
		actual.insert(actual.end(), actual.begin(), actual.end());

		/* 3. Genero la nueva generación cruzando ejemplares */
		for (int i = 0; i < K; i++)
		for (int j = i + 1; j < K; j++) {
			/* Cada pareja tiene 4 hijos */
			struct scores params = cruzador.cruzar(
				actual[i].params, actual[j].params
			);
			actual.push_back({params, 0});

			params = cruzador.cruzar(
				actual[i].params, actual[j].params
			);
			actual.push_back({params, 0});

			params = cruzador.cruzar(
				actual[i].params, actual[j].params
			);
			actual.push_back({params, 0});

			params = cruzador.cruzar(
				actual[i].params, actual[j].params
			);
			actual.push_back({params, 0});
		}

		/* 4. Muto los ejemplares */
		for (long unsigned i = K; i < actual.size(); i++)
			mutador.mutar(actual[i].params);
	}

	return 0;
}
