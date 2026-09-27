#include <iostream>
#include <conio.h>
#include <ctime>
#include "Gato.h"
#include "Rata.h"
#include "Interfaz.h"
#include "misfunciones.h"
using namespace std;
bool moverGatoMatriz(int mapa[40][120], int x,int y) {
    int ancho = 9;
    int alto = 3;
        for (int fila = 0; fila < alto; fila++) {
            for (int columna = 0; columna < ancho; columna++) {

                int mapaX = x + columna;
                int mapaY = y + fila;

                if (mapaX < 0 || mapaX >= 120 ||
                    mapaY < 0 || mapaY >= 40) {
                    return false;
                }

                if (mapa[mapaY][mapaX] == 1) {
                    return false;
                }
            }
        }

    return true;
}

Rata** crearRatas(int cantidad) {
    Rata** ratas = new Rata * [cantidad];
    for (int i = 0; i < cantidad; i++) {
        ratas[i] = new Rata();
        ratas[i]->setX(30 + rand() % 40);
        ratas[i]->setY(5 + rand() % 15);
        ratas[i]->dibujar();
    }
    return ratas;
}
void actualizarRatas(Rata** ratas, int cantidadRatas) {
    int ancho = Console::WindowWidth;
    int alto = Console::WindowHeight;
    for (int i = 0; i < cantidadRatas; i++) {
        if (ratas[i]->estaVivo()) {
            int xAnterior = ratas[i]->getX();
            int yAnterior = ratas[i]->getY();

            ratas[i]->mover(ancho, alto);

            ratas[i]->borrar(
                xAnterior,
                yAnterior
            );

            ratas[i]->dibujar();
        }

    }
}
void actualizarProyectiles(Gato* gato) {

    for (int i = 0;
        i < gato->getCantidadProyectiles();
        i++) {
        Proyectil* proyectil =
            gato->getProyectil()[i];

        int xAnterior =
            proyectil->getX();

        int yAnterior =
            proyectil->getY();

        proyectil->mover();

        proyectil->borrar(
            xAnterior,
            yAnterior
        );

        if (proyectil->getDistanciaRecorrida() > 0) {

            proyectil->dibujar();
        }
    }
}
void comprobarColisiones(
    Rata** ratas,
    int cantidadRatas,
    Gato* gato
) {
    for (int i = 0; i < cantidadRatas; i++) {

        if (ratas[i]->estaVivo()) {

            for (int j = 0;
                j < gato->getCantidadProyectiles();
                j++) {

                Proyectil* proyectil =
                    gato->getProyectil()[j];

                if (ratas[i]->colision(proyectil)) {

                    ratas[i]->recibirDanio(
                        gato->getDanioArma()
                    );

                    proyectil->borrar(
                        proyectil->getX(),
                        proyectil->getY()
                    );

                    if (!ratas[i]->estaVivo()) {

                        ratas[i]->borrar(
                            ratas[i]->getX(),
                            ratas[i]->getY()
                        );
                    }
                }
            }
        }
    }
}
int main() {

    Console::CursorVisible = false;
    Interfaz* interfaz = new Interfaz();
    interfaz->dibujarMarco();
    srand(time(NULL));

    Gato* gato = new Gato(true);
    interfaz->dibujarHUD(gato);
    int cantidadRatas = 5;

    Rata** ratas = crearRatas(cantidadRatas);

    gato->dibujar();

    while (true) {

        gato->borrar(gato->getX(),gato->getY());
        gato->mover();
        gato->dibujar();
        
        actualizarRatas(ratas,cantidadRatas);

        actualizarProyectiles(
            gato
        );

        comprobarColisiones(
            ratas,
            cantidadRatas,
            gato
        );

        _sleep(100);
    }

    return 0;
}