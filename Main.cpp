#include <iostream>
#include <conio.h>
#include <ctime>
#include "GameManager.h"
#include "misfunciones.h"
#include "matrices.h"
#include "lore.h"
#include "loreMayumi.h"

using namespace std;

int main() {
    Console::CursorVisible = false;
    srand(time(NULL));

    while (true) {
        float expExtra = 1.0;
        int danoExtra = 0;
        int vidaJugador = 100;
        bool verEscenas = true;

        int opc = mostrarMenuAnimado(expExtra, danoExtra, vidaJugador, verEscenas);

        if (opc == 3) return 0;

        GameManager juego;   
        juego.jugar();      
    }

    return 0;
}