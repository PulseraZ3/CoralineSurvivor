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
void Interfaz::dibujarMarco() {

    for (int i = 0; i < alto-1; i++) {

        Console::SetCursorPosition(ancho-(ancho-30), i);
        cout << "|";
    }

    Console::SetCursorPosition(ancho - (ancho - 30), alto-(alto));
    cout << "+";

    Console::SetCursorPosition(ancho - (ancho - 30), alto-1);
    cout << "+";
}
void Interfaz::dibujarHUD(Jugador* jugador) {

    Console::SetCursorPosition(ancho - (ancho - 10), 2);
    cout << "JUGADOR";

    Console::SetCursorPosition(ancho - (ancho - 10), 4);
    cout << "VIDA: "
        << jugador->getVida()
        << "/100";

}
void Interfaz::dibujarMapa(int mapa[40][120]) {
    for (int y = 0; y < 40; y++) {
        for (int x = 0; x < 120; x++) {

            switch (mapa[y][x]) {
            case 0:
                Console::BackgroundColor = ConsoleColor::Green;
                break;
            case 1:
                Console::BackgroundColor = ConsoleColor::Red;
                break;
            case 2:
                Console::BackgroundColor = ConsoleColor::Cyan;
                break;
            }
            cout << " ";
        }
        Console::BackgroundColor = ConsoleColor::Black;
        cout << "\n";
    }
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