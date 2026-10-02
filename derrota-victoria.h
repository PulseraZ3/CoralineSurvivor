#include <iostream>
#include <conio.h>

using namespace std;
using namespace System;




void escribirTexto(string texto, int x, int y, ConsoleColor color) {
    Console::SetCursorPosition(x, y);
    Console::ForegroundColor = color;
    for (char c : texto) {
        cout << c;
        _sleep(40);
    }
}

void pantallaDerrota() {
    Console::Clear();
    Console::CursorVisible = false;

    string cara[9] = {
        "                          ",
        "        /\\   /\\           ",
        "       .-\"\"\"\"-.       ",
        "      /        \\      ",
        "     |          |     ",
        "     |    \\/    |     ",
        "     |    __    |     ",
        "      \\        /      ",
        "       `\"\"\"\"\"\"`       "
    };

    Console::ForegroundColor = ConsoleColor::DarkGray;
    for (int i = 0; i < 9; i++) {
        Console::SetCursorPosition(48, 10 + i);
        cout << cara[i];
    }
    _sleep(1000);

    Console::ForegroundColor = ConsoleColor::DarkRed;
    Console::SetCursorPosition(55, 14); cout << "X";
    _sleep(800);
    Console::SetCursorPosition(62, 14); cout << "X";
    _sleep(1000);

    Console::ForegroundColor = ConsoleColor::Red;
    escribirTexto("G A M E   O V E R", 51, 20, ConsoleColor::Red);
    escribirTexto("Te quedas en su mundo para siempre, con ojos de boton...", 32, 22, ConsoleColor::DarkGray);

    bool parpadeo = true;
    while (!_kbhit()) {
        Console::SetCursorPosition(55, 14);
        if (parpadeo) {
            Console::ForegroundColor = ConsoleColor::DarkRed;
        }
        else {
            Console::ForegroundColor = ConsoleColor::Black;
        }
        cout << "X";
        Console::SetCursorPosition(62, 14);
        cout << "X";

        Console::SetCursorPosition(43, 25);
        Console::ForegroundColor = ConsoleColor::Gray;
        cout << "[ Presiona cualquier tecla para salir ]";

        parpadeo = !parpadeo;
        _sleep(400);
    }
    _getch();
    Console::Clear();
}
void pantallaNivelSuperado(int nivelCompletado) {
    Console::Clear();
    Console::CursorVisible = false;

    string puertaCerrada[6] = {
        "  ______  ",
        " |      | ",
        " |     0| ",
        " |      | ",
        " |______| ",
        "          "
    };

    string puertaAbierta[6] = {
        "  ______  ",
        " |  \\   | ",
        " |   \\  | ",
        " |    \\ | ",
        " |_____\\| ",
        "          "
    };

    Console::ForegroundColor = ConsoleColor::Yellow;
    for (int i = 0; i < 6; i++) {
        Console::SetCursorPosition(55, 10 + i);
        cout << puertaCerrada[i];
    }
    _sleep(1300);

    for (int i = 0; i < 6; i++) {
        Console::SetCursorPosition(55, 10 + i);
        cout << puertaAbierta[i];
    }

    Console::BackgroundColor = ConsoleColor::White;
    Console::SetCursorPosition(57, 11); cout << "   ";
    Console::SetCursorPosition(57, 12); cout << "    ";
    Console::SetCursorPosition(57, 13); cout << "     ";
    Console::BackgroundColor = ConsoleColor::Black;

    Console::ForegroundColor = ConsoleColor::Cyan;
    escribirTexto("M A R A V I L L A   S U P E R A D A", 42, 20, ConsoleColor::Cyan);

    if (nivelCompletado == 1) {
        escribirTexto("Crees que cruzaste la puerta de regreso, pero el terror solo continua...", 20, 22, ConsoleColor::Gray);
    }
    else if (nivelCompletado == 2) {

        //esto ya seria para el nivel dos... 
        escribirTexto("ps para el nive dos... para añadir a los otros solo con un else if mas", 30, 22, ConsoleColor::Gray);
    }

    _sleep(1000);
    escribirTexto("[ Presiona ENTER para continuar ]", 42, 25, ConsoleColor::DarkGray);
    while (_getch() != '\r');
    Console::Clear();
}

void pantallaVictoria() {
    int frame = 0;
    Console::Clear();
    Console::CursorVisible = false;

    string gato[3] = { " /\\_/\\ ",
                        "( o.o )",
                        " > ^ < " };
    string papa[3] = { "  _O_  ",
                       " |   | ",
                       "  / \\  " };
    string coraline[3] = { "   O   ",
                           "  /|\\  ",
                           "  / \\  " };

    escribirTexto("Y A   N O   Q U E D A N   P U E R T A S   F A L S A S", 33, 5, ConsoleColor::Yellow);
    escribirTexto("Los tres cruzan juntos la puerta hacia el mundo real...", 32, 7, ConsoleColor::White);

    while (!_kbhit()) {
        Console::SetCursorPosition(0, 15);

        for (int i = 0; i < 3; i++) {
            Console::SetCursorPosition(40, 12 + i);
            Console::ForegroundColor = ConsoleColor::DarkGray;
            cout << gato[i]; // gato

            Console::SetCursorPosition(55, 12 + i);
            Console::ForegroundColor = ConsoleColor::White;
            cout << papa[i]; // Charlie Jones / el padre

            Console::SetCursorPosition(70, 12 + i);
            Console::ForegroundColor = ConsoleColor::Blue;
            cout << coraline[i]; // carolina
        }

        Console::ForegroundColor = ConsoleColor::Magenta;
        if (frame % 2 == 0) {
            Console::SetCursorPosition(30, 10); cout << "*   .    *    . ";
            Console::SetCursorPosition(65, 18); cout << "  .    *    .   ";
        }
        else {
            Console::SetCursorPosition(30, 10); cout << "  .   *    .   *";
            Console::SetCursorPosition(65, 18); cout << "*    .   *    . ";
        }

        Console::ForegroundColor = ConsoleColor::Green;
        Console::SetCursorPosition(45, 25);
        cout << "[ Presiona ENTER para finalizar ]";

        frame++;
        _sleep(300);
    }
    Console::Clear();
}