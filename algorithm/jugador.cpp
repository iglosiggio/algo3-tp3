#include <iostream>

#include "jugador.h"

struct contadores {
    int C, C1, C2, C3;
};

struct contadores bloqueos {0, 0, 0, 0};
struct contadores efectivos {0, 0, 0, 0};
struct contadores posibles {0, 0, 0, 0};

int elegirEje(int valor, int eje, int c){
    return valor - eje * (c - 1);
}

void actualizarContadores(struct contadores& contadores, int racha, int c) {
    if(racha >= c)
        contadores.C++;
    if(racha >= c - 1)
        contadores.C1++;
    if(racha >= c - 2)
        contadores.C2++;
    if(racha >= c - 3)
        contadores.C3++;
}

void puntuar(int ejeX, int ejeY, Tablero tablero, Fichas fichas, int coljugada, int c, int p, int player){

    int m = tablero[0].size();
    int n = tablero.size();

    int rachaEfectiva = 0;
    int rachaPosible = 0;
    int rachaBloqueada = 0;

    int rowindex = elegirEje(coljugada, ejeX, c);
    int colindex = elegirEje(fichas[coljugada], ejeY, c);

    for(int i = 0; i < c * 2 - 1; i++) {

        if(rowindex >= 0 && colindex >= 0 && rowindex < m && colindex < n) {

            if(tablero[colindex][rowindex] != 0) {
                if(tablero[colindex][rowindex] == player) {
                    rachaEfectiva++;
                    rachaPosible++;
                    rachaBloqueada = 0;

                    actualizarContadores(efectivos, rachaEfectiva, c);
                } else {
                    rachaBloqueada++;
                    rachaEfectiva = 0;
                    rachaPosible = 0;

                    actualizarContadores(bloqueos, rachaBloqueada, c);
                }
            } else
                rachaPosible++;
            
            actualizarContadores(posibles, rachaPosible, c);
        }

        rowindex += ejeX;
        colindex += ejeY;
    }
}

int score(Tablero tablero, Fichas fichas, const struct scores* scores) {
    int score = 0;
    score += scores->posc3       * posibles.C3;
    score += scores->posc2       * posibles.C2;
    score += scores->posc1        * posibles.C1;
    score += scores->c3          * efectivos.C3;
    score += scores->c2          * efectivos.C2;
    score += scores->c1          * efectivos.C1;
    score += scores->bloqueos_c3 * bloqueos.C3;
    score += scores->bloqueos_c2 * bloqueos.C2;
    score += scores->bloqueos_c1 * bloqueos.C1;
    return score;
}

int puntuarJugada(Tablero tablero, Fichas fichas, int coljugada, int c, int p,
		  int player, const struct scores* scores) {

    bloqueos  = {0, 0, 0, 0};
    efectivos = {0, 0, 0, 0};
    posibles  = {0, 0, 0, 0};

    puntuar(1, 0, tablero, fichas, coljugada, c, p, player);
    puntuar(0, 1, tablero, fichas, coljugada, c, p, player);
    puntuar(1, 1, tablero, fichas, coljugada, c, p, player);
    puntuar(1, -1, tablero, fichas, coljugada, c, p, player);

    return score(tablero, fichas, scores);

}

int puntuarEnemigo(Tablero tablero, Fichas fichas, int c, int p, int player,
		    const struct scores* params) {

    int columns = tablero[0].size();
    int rows = tablero.size();
    int mejorPuntaje = INT32_MIN;
    int mejorCol;
    
    for(int col = 0; col < columns; col++) {

        if(fichas[col] < rows){
            int puntaje = puntuarJugada(tablero, fichas, col, c, p, player,
					params);

            if(mejorPuntaje < puntaje){
                mejorPuntaje = puntaje;
                mejorCol = col;
            }
        }
    }

    return mejorCol;
}

int evaluarTableros(Tablero tablero, Fichas fichas, int c, int p, int player,
		    const void* ctx) {

    int columns = tablero[0].size();
    int rows = tablero.size();
    int mejorPuntaje = INT32_MIN;
    int mejorCol;
    const struct scores* params = (const struct scores*) ctx;
    
    for(int col = 0; col < columns; col++) {

        if(fichas[col] < rows){
            int puntaje = puntuarJugada(tablero, fichas, col, c, p, player,
					params);

            
            tablero[fichas[col]][col] = 1;
            fichas[col]++;
            puntaje -= puntuarEnemigo(tablero, fichas, c, p, 2, params) / 2;
            fichas[col]--;
            tablero[fichas[col]][col] = 0;
            

            std::cerr << "col: " << col
                      << " puntaje: " << puntaje << std::endl;

            if(mejorPuntaje < puntaje){
                mejorPuntaje = puntaje;
                mejorCol = col;
            }
        }
    }

    return mejorCol;
}
