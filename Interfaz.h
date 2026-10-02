#pragma once
#include "Jugador.h"
#include "matrices.h"

class Interfaz {
private:
    int ancho;
    int alto;

    // Dibuja una barra tipo [######....] en (x, y)
    void dibujarBarra(int x, int y, int valor, int maximo, int largo, ConsoleColor color);
    // Escribe texto en una posicion con un color
    void escribir(int x, int y, String^ texto, ConsoleColor color);
    // Dibuja una tecla tipo [W]
    void dibujarTecla(int x, int y, String^ tecla);

public:
    Interfaz();
    void configurarConsola();
    void dibujarMarco();
    void dibujarMapa(int mapa[40][120]);
    bool puedecaminar(int mapa[40][120], int x, int y);
    void dibujarHUD(Jugador* jugador);
    // Seccion 2 del panel: estado del objetivo (llamar cada tick)
    void dibujarObjetivo(int sala, int totalSalas, int ratasRestantes);

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
    Console::CursorVisible = false;
    Console::Title = "Coraline Survivors";
}

void Interfaz::escribir(int x, int y, String^ texto, ConsoleColor color) {
    Console::SetCursorPosition(x, y);
    Console::ForegroundColor = color;
    Console::Write(texto);
    Console::ResetColor();
}

void Interfaz::dibujarBarra(int x, int y, int valor, int maximo, int largo, ConsoleColor color) {
    if (maximo <= 0) maximo = 1;
    if (valor < 0) valor = 0;
    if (valor > maximo) valor = maximo;

    int llenos = valor * largo / maximo;

    Console::SetCursorPosition(x, y);
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::Write(L"[");
    Console::ForegroundColor = color;
    Console::Write(gcnew String(L'#', llenos));
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::Write(gcnew String(L'.', largo - llenos));
    Console::Write(L"]");
    Console::ResetColor();
}

void Interfaz::dibujarMarco() {
    int w = OFFSET_X; // ancho total del panel lateral (incluye el borde derecho)
    Console::ForegroundColor = ConsoleColor::DarkCyan;

    // Borde superior e inferior (ASCII puro, compatible con cualquier consola)
    Console::SetCursorPosition(0, 0);
    Console::Write(L"+" + gcnew String(L'-', w - 2) + L"+");
    Console::SetCursorPosition(0, 39);
    Console::Write(L"+" + gcnew String(L'-', w - 2) + L"+");

    // Lados
    for (int i = 1; i < 39; i++) {
        Console::SetCursorPosition(0, i);
        Console::Write(L"|");
        Console::SetCursorPosition(w - 1, i);
        Console::Write(L"|");
    }

    // Separadores internos del panel
    Console::SetCursorPosition(0, 15);
    Console::Write(L"+" + gcnew String(L'-', w - 2) + L"+");
    Console::SetCursorPosition(0, 30);
    Console::Write(L"+" + gcnew String(L'-', w - 2) + L"+");

    Console::ResetColor();

    // ---------- Seccion 1: titulo ----------
    escribir(2, 1, "SURVIVORS", ConsoleColor::Cyan);

    // ---------- Seccion 2: objetivo (texto fijo) ----------
    escribir(2, 16, "OBJETIVO", ConsoleColor::Yellow);
    escribir(2, 18, "Elimina a todas las", ConsoleColor::Gray);
    escribir(2, 19, "ratas de la sala.", ConsoleColor::Gray);
    escribir(2, 21, "Luego cruza la puerta", ConsoleColor::Gray);
    Console::SetCursorPosition(2, 22);
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::Write("de color ");
    Console::BackgroundColor = ConsoleColor::Cyan;
    Console::Write("   ");
    Console::ResetColor();
    escribir(2, 23, "Recoge los drops: dan XP", ConsoleColor::Gray);

    // ---------- Seccion 3: controles ----------
    escribir(2, 31, "CONTROLES", ConsoleColor::Yellow);

    escribir(2, 33, "MOVER", ConsoleColor::White);
    escribir(13, 33, "DISPARAR", ConsoleColor::White);

    dibujarTecla(4, 34, "W");
    dibujarTecla(2, 35, "A");
    dibujarTecla(5, 35, "S");
    dibujarTecla(8, 35, "D");

    dibujarTecla(15, 34, "^");
    dibujarTecla(13, 35, "<");
    dibujarTecla(16, 35, "v");
    dibujarTecla(19, 35, ">");

    escribir(2, 37, "Recarga del disparo: 2s", ConsoleColor::DarkGray);
}

void Interfaz::dibujarHUD(Jugador* jugador) {
    int w = OFFSET_X;
    int anchoBarra = w - 14;
    if (anchoBarra < 8) anchoBarra = 8;

    // Retrato
    string* art = jugador->getArt();
    int altoArt = jugador->getArtAlto();

    Console::ForegroundColor = ConsoleColor::Magenta;
    for (int fila = 0; fila < altoArt; fila++) {
        Console::SetCursorPosition(2, 3 + fila);
        cout << art[fila] << "        ";
    }
    Console::ResetColor();

    // Nombre
    int filaNombre = 4 + altoArt;
    Console::SetCursorPosition(2, filaNombre);
    Console::ForegroundColor = ConsoleColor::Yellow;
    cout << jugador->getNombre() << "          ";
    Console::ResetColor();

    // Vida: verde > 60%, amarillo > 30%, rojo el resto
    int vida = jugador->getVida();
    ConsoleColor colorVida = ConsoleColor::Green;
    if (vida <= 30)      colorVida = ConsoleColor::Red;
    else if (vida <= 60) colorVida = ConsoleColor::Yellow;

    int filaVida = filaNombre + 2;
    escribir(2, filaVida, "VIDA", ConsoleColor::Red);
    dibujarBarra(2, filaVida + 1, vida, 100, anchoBarra, colorVida);
    Console::SetCursorPosition(4 + anchoBarra, filaVida + 1);
    cout << vida << "/100  ";

    // Nivel y XP
    int filaXp = filaVida + 3;
    escribir(2, filaXp, String::Concat("NIVEL ", jugador->getNivel().ToString(), "   "), ConsoleColor::Cyan);
    dibujarBarra(2, filaXp + 1, jugador->getXp(), jugador->getXpParaSubir(), anchoBarra, ConsoleColor::Cyan);
    Console::SetCursorPosition(4 + anchoBarra, filaXp + 1);
    cout << jugador->getXp() << "/" << jugador->getXpParaSubir() << "  ";
}

void Interfaz::dibujarTecla(int x, int y, String^ tecla) {
    Console::SetCursorPosition(x, y);
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::Write("[");
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::Write(tecla);
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::Write("]");
    Console::ResetColor();
}

void Interfaz::dibujarObjetivo(int sala, int totalSalas, int ratasRestantes) {
    escribir(2, 25, String::Concat("SALA ", Convert::ToString(sala), "/",
        Convert::ToString(totalSalas), "     "),
        ConsoleColor::White);

    ConsoleColor colorRatas = (ratasRestantes > 0) ? ConsoleColor::Red : ConsoleColor::Green;
    escribir(2, 26, String::Concat("RATAS: ", Convert::ToString(ratasRestantes), "     "),
        colorRatas);

    if (ratasRestantes == 0)
        escribir(2, 28, "Puerta abierta! Avanza", ConsoleColor::Green);
    else
        escribir(2, 28, "                      ", ConsoleColor::Gray); // borra el aviso
}

void Interfaz::dibujarMapa(int mapa[40][120]) {
    for (int y = 0; y < 40; y++) {
        Console::SetCursorPosition(OFFSET_X, y);

        int x = 0;
        while (x < 120) {
            // Agrupa celdas consecutivas del mismo tipo para escribir menos y evitar parpadeo
            int tipo = mapa[y][x];
            int inicio = x;
            while (x < 120 && mapa[y][x] == tipo) x++;
            int cantidad = x - inicio;

            switch (tipo) {
            case 1: Console::BackgroundColor = ConsoleColor::White; break; // pared
            case 2: Console::BackgroundColor = ConsoleColor::Cyan; break; // agua / especial
            default: Console::BackgroundColor = ConsoleColor::Black; break;   // suelo
            }
            Console::Write(gcnew String(L' ', cantidad));
        }
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