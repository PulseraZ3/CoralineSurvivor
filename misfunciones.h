#include <iostream>
#include <conio.h>
#include <string>

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


int mostrarMenuAnimado(float& multXP, int& modDano, int& modVida, bool& escenasActivas) {

    int estadoActual = 0;
    int opcionPrincipal = 0;
    int opcionMod = 0;
    int frame = 0;
    bool enMenu = true;

    Console::CursorVisible = false;
    Console::Clear();

    while (enMenu) {
        Console::SetCursorPosition(0, 0);

        int top_x = 120 - (frame % 170);
        int bot_x = -50 + (frame % 170);

        cout << "\n\n\n";

        Console::ForegroundColor = ConsoleColor::DarkGray;
        imprimirLineaAnimadadeldiablo(top_x, "   O/      <:3 )~  <:3 )~  <:3 )~");
        imprimirLineaAnimadadeldiablo(top_x, "  /|       <:3 )~  <:3 )~  <:3 )~");
        imprimirLineaAnimadadeldiablo(top_x, "  / \\     <:3 )~  <:3 )~  <:3 )~");

        for (int i = 0; i < 10; i++) cout << string(120, ' ') << "\n";

        Console::ForegroundColor = ConsoleColor::White;
        string titulo = "Carolina's Horror Adventure - Carolina Carolina, donde estas que no te veo";
        cout << string((120 - titulo.length()) / 2, ' ') << titulo << "\n\n";

        if (estadoActual == 0) {

            string opcionesPrincipal[4] = { "Iniciar Juego", "Modificadores", "Creditos", "Salir" };

            for (int i = 0; i < 4; i++) {
                string opt = opcionesPrincipal[i];
                int espacios = (120 - opt.length()) / 2;

                if (i == opcionPrincipal) {
                    Console::ForegroundColor = ConsoleColor::Cyan;
                    cout << string(espacios - 3, ' ') << ">> " << opt << " <<\n";
                }
                else {
                    Console::ForegroundColor = ConsoleColor::DarkGray;
                    cout << string(espacios, ' ') << opt << string(espacios, ' ') << "\n";
                }
            }
            for (int i = 0; i < 6; i++) cout << string(120, ' ') << "\n";
        }
        else if (estadoActual == 1) {

            string strXP = to_string(multXP);
            strXP = strXP.substr(0, 3);

            string textoEscenas = "< Escenas: Desactivadas >";
            if (escenasActivas == true) {
                textoEscenas = "< Escenas: Activadas >";
            }

            string opcionesModificadores[5] = {
                "< Multiplicador XP: " + strXP + "x >",
                "< Bono de Dano: +" + to_string(modDano) + " >",
                "< Vida Maxima: " + to_string(modVida) + " >",
                textoEscenas,
                "Volver al Menu Principal"
            };

            for (int i = 0; i < 5; i++) {
                string opt = opcionesModificadores[i];
                int espacios = (120 - opt.length()) / 2;

                if (i == opcionMod) {
                    Console::ForegroundColor = ConsoleColor::Cyan;
                    cout << string(espacios - 3, ' ') << ">> " << opt << " <<\n";
                }
                else {
                    Console::ForegroundColor = ConsoleColor::DarkGray;
                    cout << string(espacios, ' ') << opt << string(espacios, ' ') << "\n";
                }
            }
            for (int i = 0; i < 5; i++) cout << string(120, ' ') << "\n";
        }
        else if (estadoActual == 2) {
            string nombres[4] = { "Leonardo Jimenez", "Mayumi Casas", "  Camilo Lino ","              " };

            Console::ForegroundColor = ConsoleColor::White;
            for (int i = 0; i < 4; i++) {
                string nombre = nombres[i];
                int espacios = (120 - nombre.length()) / 2;
                cout << string(espacios, ' ') << nombre << "\n";
            }

            cout << "\n";


            string opt = "Volver al Menu Principal";
            int espacios = (120 - opt.length()) / 2;
            Console::ForegroundColor = ConsoleColor::Cyan;
            cout << string(espacios - 3, ' ') << ">> " << opt << " <<\n";


            for (int i = 0; i < 5; i++) cout << string(120, ' ') << "\n";
        }

        Console::ForegroundColor = ConsoleColor::DarkGray;
        imprimirLineaAnimadadeldiablo(bot_x, "~( E:>  ~( E:>  ~( E:>      \\O   ");
        imprimirLineaAnimadadeldiablo(bot_x, "~( E:>  ~( E:>  ~( E:>       |\\  ");
        imprimirLineaAnimadadeldiablo(bot_x, "~( E:>  ~( E:>  ~( E:>      / \\  ");

        for (int i = 0; i < 6; i++) cout << string(120, ' ') << "\n";


        if (_kbhit()) {
            char tecla = _getch();


            if (tecla == 'w' || tecla == 'W') {
                if (estadoActual == 0) {
                    if (opcionPrincipal > 0) opcionPrincipal--;
                }
                else if (estadoActual == 1) {
                    if (opcionMod > 0) opcionMod--;
                }
            }

            if (tecla == 's' || tecla == 'S') {
                if (estadoActual == 0) {
                    if (opcionPrincipal < 3) opcionPrincipal++;
                }
                else if (estadoActual == 1) {
                    if (opcionMod < 4) opcionMod++;
                }
            }

            if (estadoActual == 1) {
                bool incrementar = false;
                bool decrementar = false;

                if (tecla == 'd' || tecla == 'D' || tecla == '\r') incrementar = true;
                if (tecla == 'a' || tecla == 'A') decrementar = true;

                if (incrementar || decrementar) {
                    if (opcionMod == 0) {
                        if (incrementar) multXP += 0.5f;
                        if (decrementar) multXP -= 0.5f;

                        if (multXP > 3.0f) multXP = 3.0f;
                        if (multXP < 0.5f) multXP = 0.5f;
                    }
                    else if (opcionMod == 1) {
                        if (incrementar) modDano += 5;
                        if (decrementar) modDano -= 5;

                        if (modDano > 50) modDano = 50;
                        if (modDano < 0) modDano = 0;
                    }
                    else if (opcionMod == 2) {
                        if (incrementar) modVida += 25;
                        if (decrementar) modVida -= 25;

                        if (modVida > 300) modVida = 300;
                        if (modVida < 50) modVida = 50;
                    }
                    else if (opcionMod == 3) {
                        if (escenasActivas == true) escenasActivas = false;
                        else escenasActivas = true;
                    }
                }
            }

            if (tecla == '\r') {
                if (estadoActual == 0) {
                    if (opcionPrincipal == 0) enMenu = false;
                    else if (opcionPrincipal == 1) estadoActual = 1;
                    else if (opcionPrincipal == 2) estadoActual = 2;
                    else if (opcionPrincipal == 3) enMenu = false;
                }
                else if (estadoActual == 1) {
                    if (opcionMod == 4) estadoActual = 0;
                }
                else if (estadoActual == 2) {
                    estadoActual = 0;
                }
            }
        }

        frame++;
        _sleep(40);
    }

    Console::Clear();
    Console::ForegroundColor = ConsoleColor::Gray;

    return opcionPrincipal;
}