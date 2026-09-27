#pragma once
#include "Jugador.h"
#include "Arma.h"
#include "ArmaRange.h"
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
	void dibujar() override;
	void borrar(int xAnterior, int yAnterior) override;
	void mover() override;
	bool getJugado();
	void setJugado(bool jugado);
    int getDanioArma();
    Proyectil** getProyectil();
    int getCantidadProyectiles();
    void disparar(int dx, int dy);

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
int Gato::getDanioArma() {
    return arma[0]->getDanio();
}

void Gato::dibujar() {
	for (int i = 0;i < 3;i++) {
		Console::SetCursorPosition(x, y + i);
		cout <<gatoArt[i];
	}
}
void Gato::borrar(int xAnterior, int yAnterior) {
	for (int i = 0;i < 3;i++) {
		Console::SetCursorPosition(xAnterior, yAnterior + i);
		cout << "     ";
	}
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

void Gato::mover() {

    if (jugado == true) {

        if (_kbhit()) {

            int tecla = _getch();

            if (tecla == 'w') {
                y--;
            }

            if (tecla == 's') {
                y++;
            }

            if (tecla == 'a') {
                x--;
            }

            if (tecla == 'd') {
                x++;
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