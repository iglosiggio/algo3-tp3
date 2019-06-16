#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>

using namespace std;

std::random_device rd;
std::mt19937 generator(rd());

using Tablero = vector<vector<int>>;
using Fichas = vector<int>;

int SCORE_POSC2 = 10;
int SCORE_POSC1 = 15;
int SCORE_POSC = 20;

int SCORE_C2 = 100;
int SCORE_C1 = 300;
int SCORE_C = 10000;

int posiblesC2;
int posiblesC1;
int posiblesC;

int efectivosC2;
int efectivosC1;
int efectivosC;

void send(const std::string& msg) {
    std::cout << msg << std::endl;
}

void send(int msg) {
    std::cout << msg << std::endl;
}

int read_int() {
    std::string msg;
    std::cin >> msg;
    if (msg == "salir") {
        send("listo");
        std::exit(0);
    }
    return std::stoi(msg);
}

std::string read_str() {
    std::string msg;
    std::cin >> msg;
    if (msg == "salir") {
        send("listo");
        std::exit(0);
    }
    return msg;
}


int puntuarHorizontal(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){

    int contadorEfectivo = 0;
    int contadorPosibles = 0;

    for(int i= coljugada + 1 - c; i < coljugada + c; i++){
        if(i >= 0 && i < m){
            if(tablero[fichas[coljugada]][i] != 0) {
                if(tablero[fichas[coljugada]][i] == player) {
                    contadorEfectivo++;
                    contadorPosibles++;

                    if(contadorEfectivo == c-2)
                        efectivosC2++;
                    if(contadorEfectivo == c-1)
                        efectivosC1++;
                    if(contadorEfectivo == c)
                        efectivosC++;
                }else {
                    contadorEfectivo = 0;
                    contadorPosibles = 0;
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

int puntuarVertical(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){

    int contadorEfectivo = 0;
    int contadorPosibles = 0;

    for(int i= fichas[coljugada] + 1 - c; i < fichas[coljugada] + c; i++){
        if(i >= 0 && i < n){
            if(tablero[i][coljugada] != 0) {
                if(tablero[i][coljugada] == player) {
                    contadorEfectivo++;
                    contadorPosibles++;

                    if(contadorEfectivo == c-2)
                        efectivosC2++;
                    if(contadorEfectivo == c-1)
                        efectivosC1++;
                    if(contadorEfectivo == c)
                        efectivosC++;
                }else {
                    contadorEfectivo = 0;
                    contadorPosibles = 0;
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


int puntuarDiagSE(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){

    int contadorEfectivo = 0;
    int contadorPosibles = 0;

    int rowindex = fichas[coljugada] + 1 - c;
    int colindex = coljugada + 1 - c;

    for(int i = 0; i < c; i++){

        if(rowindex >= 0 && colindex >= 0 && rowindex < n && colindex < m){

            if(tablero[rowindex][colindex] != 0) {
                if(tablero[rowindex][colindex] == player) {
                    contadorEfectivo++;
                    contadorPosibles++;

                    if(contadorEfectivo == c-2)
                        efectivosC2++;
                    if(contadorEfectivo == c-1)
                        efectivosC1++;
                    if(contadorEfectivo == c)
                        efectivosC++;
                }else {
                    contadorEfectivo = 0;
                    contadorPosibles = 0;
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
        colindex++;
    }
}

int puntuarDiagNE(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){

    int contadorEfectivo = 0;
    int contadorPosibles = 0;

    int rowindex = fichas[coljugada] + 1 - c;
    int colindex = coljugada + c;

    for(int i = 0; i < c; i++){

        if(rowindex >= 0 && colindex >= 0 && rowindex < n && colindex < m){

            if(tablero[rowindex][colindex] != 0) {
                if(tablero[rowindex][colindex] == player) {
                    contadorEfectivo++;
                    contadorPosibles++;

                    if(contadorEfectivo == c-2)
                        efectivosC2++;
                    if(contadorEfectivo == c-1)
                        efectivosC1++;
                    if(contadorEfectivo == c)
                        efectivosC++;
                }else {
                    contadorEfectivo = 0;
                    contadorPosibles = 0;
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



int score(Tablero tablero, Fichas fichas){
    int score = 0;

        /*
        cerr << "     " << endl;
        cerr << "------" << endl;

        cerr << "matrix" << endl;

        for(int i= 0; i < tablero.size(); i++){
            for(int j= 0; j < tablero[0].size(); j++){
                cerr << tablero[i][j];
            }
            cerr << endl;
        }

    
        cerr << "------" << endl;
        cerr << "posiblesC2: " << posiblesC2 << endl;
        cerr << "posiblesC1: " << posiblesC1 << endl;
        cerr << "posiblesC: " << posiblesC << endl;
        cerr << "efectivosC2: " << efectivosC2 << endl;
        cerr << "efectivosC1: " << efectivosC1 << endl;
        cerr << "efectivosC: " << efectivosC << endl;
        cerr << "------" << endl;
        cerr << "     " << endl;
        */    

    score += SCORE_POSC2 * posiblesC2;
    score += SCORE_POSC1 * posiblesC1;
    score += SCORE_POSC * posiblesC;
    score += SCORE_C2 * efectivosC2;
    score += SCORE_C1 * efectivosC1;
    score += SCORE_C * efectivosC;
    return score;
}

int puntuarJugada(Tablero tablero, Fichas fichas, int coljugada, int m, int n, int c, int p, int player){
    posiblesC2 = 0;
    posiblesC1 = 0;
    posiblesC = 0;

    efectivosC2 = 0;
    efectivosC1 = 0;
    efectivosC = 0;

    puntuarHorizontal(tablero, fichas, coljugada, m, n, c, p, player);
    puntuarVertical(tablero, fichas, coljugada, m, n, c, p, player);
    puntuarDiagSE(tablero, fichas, coljugada, m, n, c, p, player);
    puntuarDiagNE(tablero, fichas, coljugada, m, n, c, p, player);


    return score(tablero, fichas);

}

int evaluarTableros(Tablero tablero, Fichas fichas, int columns, int rows, int c, int p, int player){

    int mejorPuntaje = 0;
    int mejorCol;
    
    for(int col = 0; col < columns; col++) {
        
        tablero[fichas[col]][col] = 1;
        int puntaje = puntuarJugada(tablero, fichas, col, columns, rows, c, p, player);

        //cerr << "puntaje: " << puntaje << endl;
        if(mejorPuntaje < puntaje){
            mejorPuntaje = puntaje;
            mejorCol = col;
        }
        tablero[fichas[col]][col] = 0;
    }

    return mejorCol;
}


int main() {

    std::string msg, color, oponent_color, go_first;
    int columns, rows, c, p, move;

    while (true) {

        color = read_str();
        oponent_color = read_str();

        columns = read_int();
        rows = read_int();
        c = read_int();
        p = read_int();
    
    	vector<int> column(columns, 0);
	    Tablero tablero(rows, column);

        Fichas fichas(columns, 0);

        msg = read_str();
        if (msg == "vos") {
            int col = evaluarTableros(tablero, fichas, columns, rows, c, p, 1);
            tablero[0][col] = 1;
            fichas[col]++;
            send(col);
        }

        while (true) {
            msg = read_str();
            if (msg == "ganaste" || msg == "perdiste" || msg == "empataron") {
                break;
            }
            int colOponent = std::stoi(msg);
            tablero[fichas[colOponent]][colOponent] = 2;
            fichas[colOponent]++;
            
            
            int col = evaluarTableros(tablero, fichas, columns, rows, c, p, 1);
            tablero[fichas[col]][col] = 1;
            fichas[col]++;
            send(col);
        }
        
    }

    return 0;
}