#pragma once
#include "Entidad.h"

class Proyectil : public Entidad {
private:
	int dx;
	int dy;
    int velocidad;
    int distanciaRecorrida;
    int rangoMaximo;
public:
	Proyectil(int x, int y, int dx, int dy);
	void dibujar() override;
	void borrar(int xAnterior, int yAnterior) override;
	void mover() override;
    int getDistanciaRecorrida();
    int getRangoMaximo();
};
Proyectil::Proyectil(int x, int y, int dx, int dy) {
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
    velocidad = 3;
    distanciaRecorrida = 7;
    rangoMaximo = 3;
}

void Proyectil::dibujar() {
    Console::SetCursorPosition(x, y);
    cout << ".O.";
}

void Proyectil::borrar(int xAnterior, int yAnterior) {
    Console::SetCursorPosition(xAnterior, yAnterior);
    cout << "   ";
}

void Proyectil::mover() {
    if (distanciaRecorrida > 0) {
        x += dx*velocidad;
        y += dy*velocidad;
        distanciaRecorrida--;

    }
}
int Proyectil::getDistanciaRecorrida() {
    return distanciaRecorrida;
}

int Proyectil::getRangoMaximo() {
    return rangoMaximo;
}