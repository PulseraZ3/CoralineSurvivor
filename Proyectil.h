#pragma once
#include "Entidad.h"
#include "matrices.h"

class Proyectil : public Entidad {
private:
	int dx;
	int dy;
    int velocidad;
    int distanciaRecorrida;
    int rangoMaximo;
    int (*mapaPtr)[120];
public:
	Proyectil(int x, int y, int dx, int dy);
<<<<<<< HEAD
    ~Proyectil();
=======
>>>>>>> eddf9ee44b0ae9ff3f44ce8e5975b4caa8d7dbd9
	void dibujar() override;
	void borrar(int xAnterior, int yAnterior) override;
	void mover() override;
    int getDistanciaRecorrida();
    int getRangoMaximo();
    void setMapa(int mapa[40][120]);
    void repintarCelda(int mapaX, int mapaY, int mapa[40][120]);
    void detener();
<<<<<<< HEAD
=======

>>>>>>> eddf9ee44b0ae9ff3f44ce8e5975b4caa8d7dbd9
};
Proyectil::Proyectil(int x, int y, int dx, int dy) {
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
    velocidad = 3;
    distanciaRecorrida = 7;
    rangoMaximo = 3;
    mapaPtr = nullptr;
}
<<<<<<< HEAD
Proyectil::~Proyectil() {
}
=======
>>>>>>> eddf9ee44b0ae9ff3f44ce8e5975b4caa8d7dbd9

void Proyectil::setMapa(int mapa[40][120]) {
    mapaPtr = mapa;
}
void Proyectil::dibujar() {
    Console::SetCursorPosition(x + OFFSET_X, y);
    cout << "(\")";
}

void Proyectil::borrar(int xAnterior, int yAnterior) {
    for (int i = 0; i < 3; i++) {
        int mapaX = xAnterior + i;

        if (mapaX < 0 || mapaX >= 120 || yAnterior < 0 || yAnterior >= 40) continue;

        if (mapaPtr != nullptr) {
            switch (mapaPtr[yAnterior][mapaX]) {
            case 0: Console::BackgroundColor = ConsoleColor::Black; break;
            case 1: Console::BackgroundColor = ConsoleColor::White; break;
            case 2: Console::BackgroundColor = ConsoleColor::Cyan; break;
            default: Console::BackgroundColor = ConsoleColor::Black; break;
            }
        }

        Console::SetCursorPosition(mapaX + OFFSET_X, yAnterior);
        cout << " ";
    }
    Console::BackgroundColor = ConsoleColor::Black;
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
void Proyectil::repintarCelda(int mapaX, int mapaY, int mapa[40][120]) {
    if (mapaX < 0 || mapaX >= 120 || mapaY < 0 || mapaY >= 40) return;

    switch (mapa[mapaY][mapaX]) {
    case 0: Console::BackgroundColor = ConsoleColor::Black; break;
    case 1: Console::BackgroundColor = ConsoleColor::White; break;
    case 2: Console::BackgroundColor = ConsoleColor::Cyan; break;
    default: Console::BackgroundColor = ConsoleColor::Black; break;
    }

    Console::SetCursorPosition(mapaX + OFFSET_X, mapaY);
    cout << " ";
    Console::BackgroundColor = ConsoleColor::Black;
}
void Proyectil::detener() {
    distanciaRecorrida = 0;
}