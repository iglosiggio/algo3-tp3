#ifndef __PUNTUAR_PARAMS_H__
#define __PUNTUAR_PARAMS_H__

#define STATIC_ARRAY_SIZE(array) (sizeof (array) / sizeof ((array)[0]))

static const struct scores bloqueadora {
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

static const struct scores agresiva {
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

static const struct scores al_medio {
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
};

extern const struct config_partida partidas[];
extern const int cant_partidas;

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

	for (int i = 0; i < cant_partidas; i++) {
		const struct config_partida& partida = partidas[i];

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

#undef STATIC_ARRAY_SIZE
#undef PARTIDA

#endif
