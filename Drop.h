#pragma once
#include "Entidad.h"
#include "matrices.h"

extern int (*mapaActual)[120];
class Drop : public Entidad{
public:
	Drop(int x, int y);
	void dibujar() override;
	void borrar(int xAnterior, int yAnterior) override;
};
Drop::Drop(int x, int y) {
    this->x = x;
    this->y = y;
}

void Drop::dibujar() {
    string sprite = "o.o";
    for (int c = 0; c < (int)sprite.length(); c++) {
        int mapaX = x + c;
        int mapaY = y;

        if (mapaX < 0 || mapaX >= 120 || mapaY < 0 || mapaY >= 40) continue;

        switch (mapaActual[mapaY][mapaX]) {
        case VACIO: Console::BackgroundColor = ConsoleColor::Black; break;
        case PARED: Console::BackgroundColor = ConsoleColor::White; break;
        case PUERTA: Console::BackgroundColor = ConsoleColor::Cyan; break;
        default: Console::BackgroundColor = ConsoleColor::Black; break;
        }

        Console::ForegroundColor = ConsoleColor::Yellow;
        Console::SetCursorPosition(mapaX + OFFSET_X, mapaY);
        cout << sprite[c];
    }
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::BackgroundColor = ConsoleColor::Black;
}

void Drop::borrar(int xAnterior, int yAnterior) {
    for (int c = 0; c < 3; c++) {
        int mapaX = xAnterior + c;
        int mapaY = yAnterior;

        if (mapaX < 0 || mapaX >= 120 || mapaY < 0 || mapaY >= 40) continue;

        switch (mapaActual[mapaY][mapaX]) {
        case VACIO: Console::BackgroundColor = ConsoleColor::Black; break;
        case PARED: Console::BackgroundColor = ConsoleColor::White; break;
        case PUERTA: Console::BackgroundColor = ConsoleColor::Cyan; break;
        default: Console::BackgroundColor = ConsoleColor::Black; break;
        }

        Console::SetCursorPosition(mapaX + OFFSET_X, mapaY);
        cout << " ";
    }
    Console::BackgroundColor = ConsoleColor::Black;
}

