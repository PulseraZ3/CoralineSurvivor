#pragma once
#include "Enemigo.h"
#include "Proyectil.h"
#include "matrices.h"
extern int (*mapaActual)[120];

// NORMAL: gris | ROJA: pega fuerte | AMARILLA: veloz y fragil | VERDE: resistente
enum class TipoRata { NORMAL, ROJA, AMARILLA, VERDE };

class Rata : public Enemigo {
private:
    bool mirandoDerecha;
    ConsoleColor color;
    int pasos;                 // casillas que avanza por tick
    void moverUnPaso(int ancho, int alto);
public:
    Rata(TipoRata tipo = TipoRata::NORMAL);
    void dibujar() override;
    void borrar(int xAnterior, int yAnterior) override;
    void mover(int ancho, int alto);
    bool colision(Proyectil* proyectil);
};

Rata::Rata(TipoRata tipo) : Enemigo() {
    Nombre = "Rata";
    Descripcion = "Una rata enemiga";
    mirandoDerecha = true;
    x = 70;
    y = 15;

    switch (tipo) {
    case TipoRata::ROJA:
        color = ConsoleColor::Red;
        vida = 30;  danio = 20;  pasos = 1;
        break;
    case TipoRata::AMARILLA:
        color = ConsoleColor::Yellow;
        vida = 20;  danio = 10;  pasos = 2;
        break;
    case TipoRata::VERDE:
        color = ConsoleColor::Green;
        vida = 60;  danio = 10;  pasos = 1;
        break;
    default: // NORMAL
        color = ConsoleColor::Gray;
        vida = 30;  danio = 10;  pasos = 1;
        break;
    }
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
    Console::ForegroundColor = color;

    string* sprite = mirandoDerecha ? rataArtDer : rataArt;
    for (int c = 0; c < (int)sprite[0].length(); c++) {
        ponerColorDeCelda(x + c, y);
        Console::SetCursorPosition(x + c + OFFSET_X, y);
        cout << sprite[0][c];
    }

    Console::ResetColor();
    Console::BackgroundColor = ConsoleColor::Black;
}

void Rata::borrar(int xAnterior, int yAnterior) {
    for (int c = 0; c < 8; c++) {
        ponerColorDeCelda(xAnterior + c, yAnterior);
        Console::SetCursorPosition(xAnterior + c + OFFSET_X, yAnterior);
        cout << " ";
    }
    Console::BackgroundColor = ConsoleColor::Black;
}

bool areaLibreParaRataMovimiento(int x, int y) {
    for (int dx = 0; dx < 8; dx++) {
        int mx = x + dx;
        if (mx < 0 || mx >= 120 || y < 0 || y >= 40) return false;
        if (mapaActual[y][mx] == PARED) return false;
    }
    return true;
}

void Rata::moverUnPaso(int ancho, int alto) {
    int direccion = rand() % 4;

    if (direccion == 0 && x < ancho - 9) {
        if (areaLibreParaRataMovimiento(x + 1, y)) { x++; mirandoDerecha = true; }
    }
    if (direccion == 1 && x > 0) {
        if (areaLibreParaRataMovimiento(x - 1, y)) { x--; mirandoDerecha = false; }
    }
    if (direccion == 2 && y < alto - 3) {
        if (areaLibreParaRataMovimiento(x, y + 1)) y++;
    }
    if (direccion == 3 && y > 2) {
        if (areaLibreParaRataMovimiento(x, y - 1)) y--;
    }
}

void Rata::mover(int ancho, int alto) {
    for (int i = 0; i < pasos; i++) moverUnPaso(ancho, alto);
}

// El proyectil mide 3x1 y la rata 8x1: solapan si coinciden en X y estan en la misma fila
bool Rata::colision(Proyectil* proyectil) {
    return proyectil->getX() < x + 8 &&
        proyectil->getX() + 3 > x &&
        proyectil->getY() == y;
}