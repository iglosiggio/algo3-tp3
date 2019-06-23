#include <iostream>

#include "jugador.h"

int posiblesC2;
int posiblesC1;
int posiblesC;

int efectivosC2;
int efectivosC1;
int efectivosC;

int bloqueosC3;
int bloqueosC2;
int bloqueosC1;

void puntuarHorizontal(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){

    int contadorEfectivo = 0;
    int contadorPosibles = 0;
    int contadorBloqueos = 0;

    for(int i= coljugada + 1 - c; i < coljugada + c; i++){

        if(i >= 0 && i < m){

            if(tablero[fichas[coljugada]][i] != 0) {
                if(tablero[fichas[coljugada]][i] == player) {
                    contadorEfectivo++;
                    contadorPosibles++;
                    contadorBloqueos = 0;

                    if(contadorEfectivo == c-2)
                        efectivosC2++;
                    if(contadorEfectivo == c-1)
                        efectivosC1++;
                    if(contadorEfectivo == c)
                        efectivosC++;

                }else {
                    contadorBloqueos++;
                    contadorEfectivo = 0;
                    contadorPosibles = 0;

                    if(contadorBloqueos == c-3)
                        bloqueosC3++;
                    if(contadorBloqueos == c-2)
                        bloqueosC2++;
                    if(contadorBloqueos == c-1)
                        bloqueosC1++;
                }
            } else {
                contadorPosibles++;
            }

            if(contadorPosibles >= c-2)
                posiblesC2++;
            if(contadorPosibles >=c-1)
                posiblesC1++;
            if(contadorPosibles >=c)
                posiblesC++;
        }
    }
}

void puntuarVertical(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){

    int contadorEfectivo = 0;
    int contadorPosibles = 0;
    int contadorBloqueos = 0;

    for(int i= fichas[coljugada] + 1 - c; i < fichas[coljugada] + c; i++){
        if(i >= 0 && i < n){
            if(tablero[i][coljugada] != 0) {
                if(tablero[i][coljugada] == player) {
                    contadorEfectivo++;
                    contadorPosibles++;
                    contadorBloqueos = 0;

                    if(contadorEfectivo == c-2)
                        efectivosC2++;
                    if(contadorEfectivo == c-1)
                        efectivosC1++;
                    if(contadorEfectivo == c)
                        efectivosC++;
                }else {
                    contadorBloqueos++;
                    contadorEfectivo = 0;
                    contadorPosibles = 0;

                    if(contadorBloqueos == c-3)
                        bloqueosC3++;
                    if(contadorBloqueos == c-2)
                        bloqueosC2++;
                    if(contadorBloqueos == c-1)
                        bloqueosC1++;
                }
            } else
                contadorPosibles++;

            if(contadorPosibles >= c-2)
                posiblesC2++;
            if(contadorPosibles >=c-1)
                posiblesC1++;
            if(contadorPosibles >=c)
                posiblesC++;
        }
    }
}


void puntuarDiagSE(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){

    int contadorEfectivo = 0;
    int contadorPosibles = 0;
    int contadorBloqueos = 0;

    int rowindex = fichas[coljugada] + 1 - c;
    int colindex = coljugada + 1 - c;

    for(int i = 0; i < c * 2; i++){

        if(rowindex >= 0 && colindex >= 0 && rowindex < n && colindex < m){

            if(tablero[rowindex][colindex] != 0) {
                if(tablero[rowindex][colindex] == player) {
                    contadorEfectivo++;
                    contadorPosibles++;
                    contadorBloqueos = 0;

                    if(contadorEfectivo == c-2)
                        efectivosC2++;
                    if(contadorEfectivo == c-1)
                        efectivosC1++;
                    if(contadorEfectivo == c)
                        efectivosC++;
                }else {
                    contadorBloqueos++;
                    contadorEfectivo = 0;
                    contadorPosibles = 0;

                    if(contadorBloqueos == c-3)
                        bloqueosC3++;
                    if(contadorBloqueos == c-2)
                        bloqueosC2++;
                    if(contadorBloqueos == c-1)
                        bloqueosC1++;
                }
            } else {
                contadorPosibles++;


            }

            if(contadorPosibles >= c-2)
                posiblesC2++;
            if(contadorPosibles >=c-1)
                posiblesC1++;
            if(contadorPosibles >=c)
                posiblesC++;
        }
        rowindex++;
        colindex++;
    }
}

void puntuarDiagNE(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){

    int contadorEfectivo = 0;
    int contadorPosibles = 0;
    int contadorBloqueos = 0;

    int rowindex = fichas[coljugada] + 1 - c;
    int colindex = coljugada + c;

    for(int i = 0; i < c * 2; i++){

        if(rowindex >= 0 && colindex >= 0 && rowindex < n && colindex < m){

            if(tablero[rowindex][colindex] != 0) {
                if(tablero[rowindex][colindex] == player) {
                    contadorEfectivo++;
                    contadorPosibles++;
                    contadorBloqueos = 0;

                    if(contadorEfectivo == c-2)
                        efectivosC2++;
                    if(contadorEfectivo == c-1)
                        efectivosC1++;
                    if(contadorEfectivo == c)
                        efectivosC++;
                }else {
                    contadorBloqueos++;
                    contadorEfectivo = 0;
                    contadorPosibles = 0;

                    if(contadorBloqueos == c-3)
                        bloqueosC3++;
                    if(contadorBloqueos == c-2)
                        bloqueosC2++;
                    if(contadorBloqueos == c-1)
                        bloqueosC1++;
                }
            } else
                contadorPosibles++;

            if(contadorPosibles >= c-2)
                posiblesC2++;
            if(contadorPosibles >=c-1)
                posiblesC1++;
            if(contadorPosibles >=c)
                posiblesC++;
        }
        rowindex++;
        colindex--;
    }
}


int score(Tablero tablero, Fichas fichas, const struct scores* scores) {
    int score = 0;
    score += scores->posc2 * posiblesC2;
    score += scores->posc1 * posiblesC1;
    score += scores->posc * posiblesC;
    score += scores->c2 * efectivosC2;
    score += scores->c1 * efectivosC1;
    score += scores->c * efectivosC;
    score += scores->bloqueos_c3 * bloqueosC3;
    score += scores->bloqueos_c2 * bloqueosC2;
    score += scores->bloqueos_c1 * bloqueosC1;
    return score;
}

int puntuarJugada(Tablero tablero, Fichas fichas, int coljugada, int c, int p,
		  int player, const struct scores* scores) {
    int m = tablero[0].size();
    int n = tablero.size();
    posiblesC2 = 0;
    posiblesC1 = 0;
    posiblesC = 0;

    efectivosC2 = 0;
    efectivosC1 = 0;
    efectivosC = 0;

    bloqueosC3 = 0;
    bloqueosC2 = 0;
    bloqueosC1 = 0;
    puntuarHorizontal(tablero, fichas, coljugada, m, n, c, p, player);
    puntuarVertical(tablero, fichas, coljugada, m, n, c, p, player);
    puntuarDiagSE(tablero, fichas, coljugada, m, n, c, p, player);
    puntuarDiagNE(tablero, fichas, coljugada, m, n, c, p, player);

    return score(tablero, fichas, scores);

}

int evaluarTableros(Tablero tablero, Fichas fichas, int c, int p, int player,
		    const void* ctx) {

    int columns = tablero[0].size();
    int rows = tablero.size();
    int mejorPuntaje = 0;
    int mejorCol;
    
    for(int col = 0; col < columns; col++) {

        if(fichas[col] < rows){
            tablero[fichas[col]][col] = player;
            int puntaje = puntuarJugada(tablero, fichas, col, c, p, player,
					(const struct scores*) ctx);

	    std::cerr << "col: " << col
		      << " puntaje: " << puntaje << std::endl;
            if(mejorPuntaje < puntaje){
                mejorPuntaje = puntaje;
                mejorCol = col;
            }
            tablero[fichas[col]][col] = 0;
        }
    }

    return mejorCol;
}
