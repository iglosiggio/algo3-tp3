#include <iostream>

#include "jugador.h"

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

struct scores greedy_conf {
	.posc3 = 5,
	.posc2 = 15,
	.posc1 = 20,
	.c3 = 150,
	.c2 = 400,
	.c1 = 10000,
	.bloqueos_c3 = 20,
	.bloqueos_c2 = 400,
	.bloqueos_c1 = 8000
};

int main() {

    std::string msg, color, oponent_color, go_first;
    int columns, rows, c, p;

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
            int col = evaluarTableros(tablero, fichas, c, p, 1, &greedy_conf);
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
            
            
            int col = evaluarTableros(tablero, fichas, c, p, 1, &greedy_conf);
            tablero[fichas[col]][col] = 1;
            fichas[col]++;
            send(col);
        }
        
    }

    return 0;
}
