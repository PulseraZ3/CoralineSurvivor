#include <iostream>
#include <conio.h>
#include <ctime>
#include "Gato.h"
#include "Rata.h"
#include "Interfaz.h"
#include "misfunciones.h"
#include "matrices.h"
using namespace std;

int (*mapaActual)[120] = mapa1; 
int mapaIndiceActual = 0;
bool tocaPuerta(int mapa[40][120], int x, int y) {
    for (int fila = 0; fila < 3; fila++) {
        for (int columna = 0; columna < 5; columna++) {
            int mapaX = x + columna;
            int mapaY = y + fila;

            if (mapaX < 0 || mapaX >= 120 || mapaY < 0 || mapaY >= 40) continue;

            if (mapa[mapaY][mapaX] == PUERTA) {
                return true;
            }
        }
    }
    return false;
}
void cambiarMapaAleatorio(Interfaz* interfaz, Gato* gato) {
    int nuevoIndice = rand() % 6;
    mapaActual = mapas[nuevoIndice];

    gato->setX(spawnX[nuevoIndice]);
    gato->setY(spawnY[nuevoIndice]);

    Console::Clear();
    interfaz->dibujarMapa(mapaActual);
    interfaz->dibujarMarco();
    interfaz->dibujarHUD(gato);
    gato->dibujar(mapaActual);
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
void actualizarProyectiles(Gato* gato, int mapa[40][120]) {

    for (int i = 0; i < gato->getCantidadProyectiles(); i++) {
        Proyectil* proyectil = gato->getProyectil()[i];

        int xAnterior = proyectil->getX();
        int yAnterior = proyectil->getY();

        proyectil->mover();

        for (int k = 0; k < 3; k++) {
            proyectil->repintarCelda(xAnterior + k, yAnterior, mapa);
        }

        if (proyectil->getDistanciaRecorrida() > 0) {

            int mapaX = proyectil->getX();
            int mapaY = proyectil->getY();

            bool fueraDeLimites = (mapaX < 0 || mapaX + 2 >= 120 ||
                mapaY < 0 || mapaY >= 40);
            bool chocoPared = false;

            if (!fueraDeLimites) {
                for (int k = 0; k < 3; k++) {
                    if (mapa[mapaY][mapaX + k] == 1) {
                        chocoPared = true;
                        break;
                    }
                }
            }

            if (fueraDeLimites || chocoPared) {
                proyectil->detener(); 
            }
            else {
                switch (mapa[mapaY][mapaX]) {
                case 0: Console::BackgroundColor = ConsoleColor::Black; break;
                case 2: Console::BackgroundColor = ConsoleColor::Cyan; break;
                default: Console::BackgroundColor = ConsoleColor::Black; break;
                }

                proyectil->dibujar();
                Console::BackgroundColor = ConsoleColor::Black;
            }
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
    mostrarMenuAnimado();
    Console::CursorVisible = false;
    srand(time(NULL));
    Interfaz* interfaz = new Interfaz();

    Gato* gato = new Gato(true);
    gato->setX(spawnX[mapaIndiceActual]);
    gato->setY(spawnY[mapaIndiceActual]);
    int cantidadRatas = 5;

    // Rata** ratas = crearRatas(cantidadRatas);
    interfaz->configurarConsola();
    Console::Clear();
    interfaz->dibujarMapa(mapaActual);
    interfaz->dibujarMarco();
    interfaz->dibujarHUD(gato);
    gato->dibujar(mapaActual);

    while (true) {
        int xAnterior = gato->getX();
        int yAnterior = gato->getY();
        gato->mover(mapaActual);
        gato->borrar(xAnterior, yAnterior, mapaActual);

        if (tocaPuerta(mapaActual, gato->getX(), gato->getY())) {
            cambiarMapaAleatorio(interfaz, gato);
            continue;
        }

        gato->dibujar(mapaActual);

        //actualizarRatas(ratas,cantidadRatas);

        actualizarProyectiles(gato, mapaActual);

        // comprobarColisiones(ratas,cantidadRatas, gato);
        interfaz->dibujarHUD(gato);
        _sleep(100);
    }

    return 0;
}