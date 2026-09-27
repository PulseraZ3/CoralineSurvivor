#pragma once
#include <iostream>
#include <conio.h>
#include "matrices.h"
const int ANCHO = 120;
const int ALTO = 40;
using namespace std;
using namespace System;
#include <iostream>
#include <conio.h>

using namespace std;
using namespace System;


void imprimirLineaAnimadadeldiablo(int x, string sprite) {
    string linea = "";

    for (int i = 0; i < 120; i++) {
        int k = i - x;

        if (k >= 0 && k < sprite.length()) {
            linea += sprite[k];
        }
        else {
            linea += " ";
        }
    }
    cout << linea << "\n";
}

void mostrarMenuAnimado() {
    int opcionSeleccionada = 0;
    int frame = 0;
    bool enMenu = true;


    Console::CursorVisible = false;
    Console::Clear();


    string opciones[3] = { "Iniciar Juego", "Modificadores", "Creditos" };

    while (enMenu) {
        Console::SetCursorPosition(0, 0);

        int top_x = 150 - (frame % 170);

        int bot_x = -50 + (frame % 170);

        cout << "\n\n\n";


        Console::ForegroundColor = ConsoleColor::DarkGray;
        imprimirLineaAnimadadeldiablo(top_x, "   O/      <:3 )~  <:3 )~  <:3 )~");
        imprimirLineaAnimadadeldiablo(top_x, "  /|       <:3 )~  <:3 )~  <:3 )~");
        imprimirLineaAnimadadeldiablo(top_x, "  / \\     <:3 )~  <:3 )~  <:3 )~");


        for (int i = 0; i < 9; i++) cout << string(120, ' ') << "\n";

        Console::ForegroundColor = ConsoleColor::White;
        string titulo = "Carolina's Horror Adventure - Carolina Carolina, donde estas que no te veo";
        cout << string((120 - titulo.length()) / 2, ' ') << titulo << "\n\n";

        for (int i = 0; i < 3; i++) {
            string opt = opciones[i];
            int espacios = (120 - opt.length()) / 2;

            if (i == opcionSeleccionada) {
                Console::ForegroundColor = ConsoleColor::Cyan;
                cout << string(espacios - 3, ' ') << ">> " << opt << " <<\n";
            }
            else {
                Console::ForegroundColor = ConsoleColor::DarkGray;
                cout << string(espacios, ' ') << opt << string(espacios, ' ') << "\n";
            }
        }


        for (int i = 0; i < 10; i++) cout << string(120, ' ') << "\n";

        Console::ForegroundColor = ConsoleColor::DarkGray;
        imprimirLineaAnimadadeldiablo(bot_x, "~( E:>  ~( E:>  ~( E:>      \\O   ");
        imprimirLineaAnimadadeldiablo(bot_x, "~( E:>  ~( E:>  ~( E:>       |\\  ");
        imprimirLineaAnimadadeldiablo(bot_x, "~( E:>  ~( E:>  ~( E:>      / \\  ");

        for (int i = 0; i < 6; i++) cout << string(120, ' ') << "\n";

        if (_kbhit()) {
            char tecla = _getch();
            if ((tecla == 'w' || tecla == 'W') && opcionSeleccionada > 0) opcionSeleccionada--;
            if ((tecla == 's' || tecla == 'S') && opcionSeleccionada < 2) opcionSeleccionada++;
            if (tecla == '\r') enMenu = false;
        }

        frame++;
        _sleep(40);
    }
    Console::Clear();
    Console::ForegroundColor = ConsoleColor::Gray;
}