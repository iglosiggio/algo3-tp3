#include "../jugador.h"

/* Estos son los parámetros resultado del algoritmo genético utilizando el
 * sistema de puntuación de grid-search, el sistema de cruzamiento 'moneda',
 * el mutador 'normal' y seleccionando los 10 mejores en cada generación (100
 * generaciones en total).
 * El archivo con el resultado experimental se encuentra en
 * resultados/resultados.puntake_moneda_normal_mejores.genetico éste fichero
 * contiene mucha más información, la primer columna indica el tipo de
 * informacíon y la segunda la generación correspondiente.
 *
 * Éste es el mejor individuo de la generación número 100.
 *
 * El puntaje conseguido fué de 9419. */
struct scores params {
	.posc3 = 36,
	.posc2 = 8,
	.posc1 = 507,
	.c3 = 774,
	.c2 = 647,
	.c1 = 645,
	.bloqueos_c3 = 784,
	.bloqueos_c2 = 933,
	.bloqueos_c1 = 889
};
