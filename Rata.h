#pragma once
#include "Enemigo.h"
#include "Proyectil.h"
#include "matrices.h"
extern int (*mapaActual)[120];
class Rata : public Enemigo {
private:
    bool mirandoDerecha;
public:
	Rata();
	void dibujar() override;
	void borrar(int xAnterior, int yAnterior) override;
	void mover(int ancho, int alto);
    bool colision(Proyectil* proyectil);
};

Rata::Rata() : Enemigo() {

    Nombre = "Rata";
    Descripcion = "Una rata enemiga";

    vida = 30;
    danio = 10;
    mirandoDerecha=true;

    x = 70;
    y = 15;
}
void ponerColorDeCelda(int mapaX, int mapaY) {
    if (mapaX < 0 || mapaX >= 120 || mapaY < 0 || mapaY >= 40) {
        Console::BackgroundColor = ConsoleColor::Black;
        return;
    }
    switch (mapaActual[mapaY][mapaX]) {
    case VACIO: Console::BackgroundColor = ConsoleColor::Black; break;
    case PARED: Console::BackgroundColor = ConsoleColor::White; break;
    case PUERTA: Console::BackgroundColor = ConsoleColor::Cyan; break;
    default: Console::BackgroundColor = ConsoleColor::Black; break;
    }
}
void Rata::dibujar() {
    if (mirandoDerecha) {
        for (int i = 0; i < 1; i++) {
            for (int c = 0; c < (int)rataArtDer[i].length(); c++) {
                ponerColorDeCelda(x + c, y + i);
                Console::SetCursorPosition(x + c + OFFSET_X, y + i);
                cout << rataArtDer[i][c];
            }
        }
    }
    else {
        for (int i = 0; i < 1; i++) {
            for (int c = 0; c < (int)rataArt[i].length(); c++) {
                ponerColorDeCelda(x + c, y + i);
                Console::SetCursorPosition(x + c + OFFSET_X, y + i);
                cout << rataArt[i][c];
            }
        }
    }
    Console::BackgroundColor = ConsoleColor::Black;
}
void Rata::borrar(int xAnterior, int yAnterior) {
    for (int i = 0; i < 1; i++) {
        for (int c = 0; c < 8; c++) {
            ponerColorDeCelda(xAnterior + c, yAnterior + i);
            Console::SetCursorPosition(xAnterior + c + OFFSET_X, yAnterior + i);
            cout << " ";
        }
    }
    Console::BackgroundColor = ConsoleColor::Black;
}
bool areaLibreParaRataMovimiento(int x, int y) {
    for (int dy = 0; dy < 1; dy++) {    
        for (int dx = 0; dx < 8; dx++) { 
            int mx = x + dx;
            int my = y + dy;

            if (mx < 0 || mx >= 120 || my < 0 || my >= 40) return false;

            if (mapaActual[my][mx] == PARED) return false;
        }
    }
    return true;
}
void Rata::mover(int ancho, int alto) {
    int direccion = rand() % 4;

    if (direccion == 0 && x < ancho - 9) {
        if (areaLibreParaRataMovimiento(x + 1, y)) {
            x++;
            mirandoDerecha = true;
        }
    }

    if (direccion == 1 && x > 0) {
        if (areaLibreParaRataMovimiento(x - 1, y)) {
            x--;
            mirandoDerecha = false;
        }
    }

    if (direccion == 2 && y < alto - 3) {
        if (areaLibreParaRataMovimiento(x, y + 1)) {
            y++;
        }
    }

    if (direccion == 3 && y > 2) {
        if (areaLibreParaRataMovimiento(x, y - 1)) {
            y--;
        }
    }
}

bool Rata::colision(Proyectil* proyectil) {
    int px = proyectil->getX();
    int py = proyectil->getY();
    if (px >= x && px <= x + 8 &&
        py >= y && py <= y + 2) {

        return true;
    }
    return false;
}