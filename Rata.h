#pragma once
#include "Enemigo.h"
#include "Proyectil.h"
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
void Rata::dibujar() {
    if (mirandoDerecha) {
        for (int i = 0; i < 1; i++) {
            Console::SetCursorPosition(x, y + i);
            cout << rataArtDer[i];
        }
    }
    else
        {
        for (int i = 0; i < 1; i++) {
            Console::SetCursorPosition(x, y + i);
            cout << rataArt[i];
        }
    }
}
void Rata::borrar(int xAnterior, int yAnterior) {

    for (int i = 0; i < 1; i++) {

        Console::SetCursorPosition(
            xAnterior,
            yAnterior + i
        );

        cout << "        ";
    }
}
void Rata::mover(int ancho, int alto) {
    int direccion = rand() % 4;

    if (direccion == 0 && x <ancho-9) {
        x++;
        mirandoDerecha =true;
    }

    if (direccion == 1 && x>0) {
        x--;
        mirandoDerecha = false;

    }

    if (direccion == 2 && y< alto -3) {
        y++;
    }

    if (direccion == 3 && y >2){
        y--;
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