Quick & Dirty “¿Qué es esto?” del proyecto:

algorithm/:
Esta carpeta aloja la lógica del jugador (tanto la función parametrizable cómo
el wrapper que permite usar la parametrización con el juez de la cátedra
respetando la entrada y salida propuesta).

algorithm/estrategias:
Parametrizaciones que se entregan cómo parte del ejercicio 3 resultado de cada
estrategia de elección de parámetros.

juez:
Interfaz en C++ (con su implementación correspondiente) que dados dos jugadores
y sus parametrizaciones indica cuál de los dos gana una partida en un tablero
determinado.

grid:
Implementación híper simplista del grid-search, los parámetros están
hardcodeados en el código fuente. Tarda ~1hora en evaluar las combinaciones
(juga muchísimas partidas por cada combinación).

genetico:
Algoritmo genético parametrizable en varias de las operaciones.  Correr el
ejecutable con parámetros inválidos muestra un pequeño texto de ayuda.

informe:
El código fuente del informe.

resultados/:
Resultados de correr el grid-search o el genético. Los parámetros del genético
se evidencian en el nombre del fichero.

puntuar_params:
Algoritmo de puntuación utilizado en el grid-search y en el genético. Éste
algoritmo se describe en el informe.

src/:
Código dado por la cátedra (juez en python y random_player).
