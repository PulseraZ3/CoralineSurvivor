#pragma once
#include "Arma.h"
#include "Proyectil.h"
#include <iostream>
using namespace std;
using namespace System;
class ArmaRange : public Arma {
private:
    short color;
public:
    ArmaRange();
    Proyectil* atacar(int x, int y, int dx, int dy) override;
	void define_color(short c);
};

ArmaRange::ArmaRange():Arma() {
    nombre = "Pistola";
    danio = 100;
	color = 1;
}
void ArmaRange::define_color(short c)
{
	switch (c)
	{
	case 1: Console::ForegroundColor = ConsoleColor::White; break;
	case 2: Console::ForegroundColor = ConsoleColor::Cyan; break;
	case 3: Console::ForegroundColor = ConsoleColor::DarkMagenta; break;
	case 4: Console::ForegroundColor = ConsoleColor::DarkRed; break;
	}
}

Proyectil* ArmaRange::atacar(int x, int y, int dx, int dy) {

    int inicioX = x;
    int inicioY = y;

    if (dx == 1) {
        inicioX = x + 9;
        inicioY = y + 1;
    }

    if (dx == -1) {
        inicioX = x - 3;
        inicioY = y + 1;
    }

    if (dy == -1) {
        inicioX = x + 4;
        inicioY = y - 1;
    }

    if (dy == 1) {
        inicioX = x + 4;
        inicioY = y + 3;
    }

    Proyectil* proyectil = new Proyectil(
        inicioX,
        inicioY,
        dx,
        dy
    );

    define_color(1);
    proyectil->dibujar();
    Console::ResetColor();

    return proyectil;
}