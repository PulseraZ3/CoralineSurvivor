#pragma once
#include "Jugador.h"
#include "Arma.h"
#include "ArmaRange.h"
#include "Colisiones.h"
#include "matrices.h" 
class Gato: public Jugador {
private:
	Arma** arma;
	Proyectil** proyectiles;
    int cantidadProyectiles;
    int tiempoDisparo;
	bool jugado;
	short cantidadArmas;
	int direccionX;
	int direccionY;
public:
	Gato(bool jugado);
	void dibujar(int mapa[40][120]);
	void borrar(int xAnterior,
        int yAnterior,
        int mapa[40][120]);
    void mover(int mapa[40][120]);;
	bool getJugado();
	void setJugado(bool jugado);
    int getDanioArma();
    Proyectil** getProyectil();
    int getCantidadProyectiles();
    void disparar(int dx, int dy);
    string* getArt() override;
    int getArtAlto() override;
};



Gato::Gato(bool jugado): Jugador() {
	cantidadArmas = 1;
	arma = new Arma*[cantidadArmas];
	arma[0] = new ArmaRange();
    proyectiles = nullptr;
    cantidadProyectiles = 0;
    tiempoDisparo = 2000;
	x = 20;
	y = 10;
	direccionX = 1;
	direccionY = 0;
	this->jugado = jugado;
    Nombre = "Gato Negro";
    xp = 0;
    nivel = 1;
    xpParaSubir = 2;
}

bool Gato::getJugado() {
	return jugado;
}
Proyectil** Gato::getProyectil() {
	return proyectiles;
}

int Gato::getCantidadProyectiles() {
    return cantidadProyectiles;
}

void Gato::setJugado(bool jugado) {
	this->jugado = jugado;
}

string* Gato::getArt() {
    return gatoArtInterfaz;
}

int Gato::getArtAlto() {
    return 4;
}
int Gato::getDanioArma() {
    return arma[0]->getDanio();
}
void Gato::dibujar(int mapa[40][120]) {
    for (int fila = 0; fila < 3; fila++) {
        int longitud = gatoArt[fila].length();

        for (int columna = 0; columna < longitud; columna++) {
            if (gatoArt[fila][columna] == ' ') continue;

            int mapaX = x + columna;
            int mapaY = y + fila;

            if (mapaX >= 0 && mapaX < 120 && mapaY >= 0 && mapaY < 40) {
                if (mapa[mapaY][mapaX] == 0) {
                    Console::BackgroundColor = ConsoleColor::Black;
                }
                else if (mapa[mapaY][mapaX] == 1) {
                    Console::BackgroundColor = ConsoleColor::White;
                }
                else if (mapa[mapaY][mapaX] == 2) {
                    Console::BackgroundColor = ConsoleColor::Cyan;
                }

                Console::SetCursorPosition(mapaX + OFFSET_X, mapaY);
                cout << gatoArt[fila][columna];
            }
        }
    }
    Console::BackgroundColor = ConsoleColor::Black;
}
void Gato::borrar(int xAnterior, int yAnterior, int mapa[40][120]) {
    for (int fila = 0; fila < 3; fila++) {
        int longitud = gatoArt[fila].length();

        for (int columna = 0; columna < longitud; columna++) {
            int mapaX = xAnterior + columna;
            int mapaY = yAnterior + fila;

            if (mapaX >= 0 && mapaX < 120 && mapaY >= 0 && mapaY < 40) {
                if (mapa[mapaY][mapaX] == 0) {
                    Console::BackgroundColor = ConsoleColor::Black;
                }
                else if (mapa[mapaY][mapaX] == 1) {
                    Console::BackgroundColor = ConsoleColor::White;
                }
                else if (mapa[mapaY][mapaX] == 2) {
                    Console::BackgroundColor = ConsoleColor::Cyan;
                }

                Console::SetCursorPosition(mapaX + OFFSET_X, mapaY);
                cout << " ";
            }
        }
    }
    Console::BackgroundColor = ConsoleColor::Black;
}
void Gato::disparar(int dx, int dy) {

    if (tiempoDisparo >= 2000) {

        Proyectil* nuevoProyectil = arma[0]->atacar(
            x,
            y,
            dx,
            dy
        );

        Proyectil** nuevosProyectiles =
            new Proyectil * [cantidadProyectiles + 1];

        for (int i = 0; i < cantidadProyectiles; i++) {
            nuevosProyectiles[i] = proyectiles[i];
        }

        nuevosProyectiles[cantidadProyectiles] = nuevoProyectil;

        delete[] proyectiles;

        proyectiles = nuevosProyectiles;

        cantidadProyectiles++;

        tiempoDisparo = 0;
    }
}

void Gato::mover(int mapa[40][120]) {

    if (jugado == true) {

        if (_kbhit()) {

            int tecla = _getch();

            if (tecla == 'w') {
                if (puedeMoverGato(mapa, x, y - 1)) {
                    y--;

                }
            }

            if (tecla == 's') {
                if (puedeMoverGato(mapa, x, y + 1)) {
                    y++;

                }
              
            }

            if (tecla == 'a') {
                if (puedeMoverGato(mapa, x-1, y )) {
                    x--;    
                }
            }

            if (tecla == 'd') {
                if (puedeMoverGato(mapa, x + 1, y)) {
                    x++;
                }
            }

            if (tecla == 224) {

                tecla = _getch();

                if (tecla == 72) {
                    disparar(0, -1);
                }
                if (tecla == 80) {
                    disparar(0, 1);
                }
                if (tecla == 75) {
                    disparar(-1, 0);
                }
                if (tecla == 77) {
                    disparar(1, 0);
                }
            }
        }
    }
    tiempoDisparo += 100;
}
