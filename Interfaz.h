#pragma once
#include "Jugador.h"
#include "matrices.h"
class Interfaz {
private:
    int ancho;
    int alto;
public:
	Interfaz();
	void configurarConsola();
	void dibujarMarco();
    void dibujarMapa(int mapa[40][120]);
    bool puedecaminar(int mapa[40][120], int x, int y);
	void dibujarHUD(Jugador* jugador);
};

Interfaz::Interfaz() {
    ancho = Console::WindowWidth;
    alto = Console::WindowHeight;
}

void Interfaz::configurarConsola() {
    int anchoDeseado = OFFSET_X + 120;
    int altoDeseado = 40;

    Console::SetWindowSize(1, 1);
    Console::SetBufferSize(anchoDeseado, altoDeseado);
    Console::SetWindowSize(anchoDeseado, altoDeseado);
}

void Interfaz::dibujarMarco() {
    for (int i = 0; i < 40; i++) {
        Console::SetCursorPosition(OFFSET_X - 1, i);
        cout << "|";
    }
}
void Interfaz::dibujarHUD(Jugador* jugador) {
    string* art = jugador->getArt();
    int alto = jugador->getArtAlto();

    for (int fila = 0; fila < alto; fila++) {
        Console::SetCursorPosition(2, 3 + fila);
        cout << art[fila] << "        ";
    }
    Console::SetCursorPosition(4, 8);
    cout <<jugador->getNombre();

    Console::SetCursorPosition(2, 10);
    cout << "VIDA: " << jugador->getVida() << "/100   ";

    Console::SetCursorPosition(2, 12);
    cout<<"lvl "<< jugador->getNivel() << "\tXP: " << jugador->getXp() << "/2   ";
}
void Interfaz::dibujarMapa(int mapa[40][120]) {
    for (int y = 0; y < 40; y++) {
        Console::SetCursorPosition(OFFSET_X, y);

        for (int x = 0; x < 120; x++) {
            switch (mapa[y][x]) {
            case 0: Console::BackgroundColor = ConsoleColor::Black; break;
            case 1: Console::BackgroundColor = ConsoleColor::White; break;
            case 2: Console::BackgroundColor = ConsoleColor::Cyan; break;
            default: Console::BackgroundColor = ConsoleColor::Black; break;
            }
            cout << " ";
        }
    }
    Console::BackgroundColor = ConsoleColor::Black;
    Console::ResetColor();
}
bool Interfaz::puedecaminar(int mapa[40][120], int x, int y) {
    if (x < 0 || x >= 120 ||
        y < 0 || y >= 40) {
        return false;
    }
    if (mapa[y][x] == 1) {
        return false;
    }
    return true;
}
