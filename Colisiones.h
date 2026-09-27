#pragma once
bool puedeMoverGato(int mapa[40][120], int x, int y);

bool puedeMoverGato(int mapa[40][120], int x, int y) {

    for (int fila = 0; fila < 3; fila++) {
        int ancho = gatoArt[fila].length();

        for (int columna = 0; columna < ancho; columna++) {

            int mapaX = x + columna;
            int mapaY = y + fila;

            if (mapaX < 0 || mapaX >= 120 ||
                mapaY < 0 || mapaY >= 40) {
                return false;
            }

            if (gatoArt[fila][columna] != ' ' &&
        mapa[mapaY][mapaX] == 1) {
        return false;
}
        }
    }

    return true;
}