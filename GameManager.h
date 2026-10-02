#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include "Gato.h"
#include "Rata.h"
#include "Drop.h"
#include "Interfaz.h"
#include "matrices.h"
#include "derrota-victoria.h"

// Rata.h declara "extern int (*mapaActual)[120];", por eso se define aqui (global).
// Cuando Rata reciba el mapa por parametro, se podra volver miembro de la clase.
int (*mapaActual)[120] = mapa1;

class GameManager {
private:
    Interfaz* interfaz;
    Gato* gato;

    Rata** ratas;
    int cantidadRatas;

    Drop** drops;
    int cantidadDrops;

    static const int TOTAL_SALAS = 6;
    int mapaIndice;
    int invulnerable;     // ticks restantes sin recibir danio
    bool jugadorMurio;

    // --- drops ---
    void agregarDrop(int x, int y);
    bool gatoTocaDrop(Drop* drop);
    void actualizarDrops();
    void liberarDrops();

    // --- ratas ---
    bool areaLibreParaRata(int mapa[40][120], int x, int y);
    void crearRatasEnSala(int cantidad);
    int ratasVivas();
    void liberarRatas();
    void actualizarRatas();

    // --- colisiones y danio ---
    void actualizarProyectiles();
    void comprobarColisiones();
    void comprobarDanioAlGato();

    // --- salas ---
    bool tocaPuerta();
    bool avanzarSala();          // true si ya no hay mas salas
    void redibujarTodo();

public:
    GameManager();
    ~GameManager();

    // Corre una partida completa. Devuelve true si el jugador gano.
    bool jugar();
};

// ===================== Ciclo de vida =====================

GameManager::GameManager() {
    interfaz = new Interfaz();
    gato = new Gato(true);

    ratas = nullptr;
    cantidadRatas = 0;
    drops = nullptr;
    cantidadDrops = 0;

    mapaIndice = 0;
    invulnerable = 0;
    jugadorMurio = false;

    mapaActual = mapas[0];
    gato->setX(spawnX[0]);
    gato->setY(spawnY[0]);
}

GameManager::~GameManager() {
    liberarRatas();
    liberarDrops();
    delete gato;
    delete interfaz;
}

// ===================== Drops =====================

void GameManager::agregarDrop(int x, int y) {
    Drop** nuevos = new Drop * [cantidadDrops + 1];
    for (int i = 0; i < cantidadDrops; i++) nuevos[i] = drops[i];
    nuevos[cantidadDrops] = new Drop(x, y);
    delete[] drops;
    drops = nuevos;
    cantidadDrops++;
    drops[cantidadDrops - 1]->dibujar();
}

bool GameManager::gatoTocaDrop(Drop* drop) {
    int gx = gato->getX();
    int gy = gato->getY();
    bool solapaX = gx < drop->getX() + 3 && gx + 5 > drop->getX();
    bool solapaY = gy < drop->getY() + 1 && gy + 3 > drop->getY();
    return solapaX && solapaY;
}

void GameManager::actualizarDrops() {
    for (int i = 0; i < cantidadDrops; i++) {
        if (drops[i] == nullptr) continue;

        if (gatoTocaDrop(drops[i])) {
            drops[i]->borrar(drops[i]->getX(), drops[i]->getY());
            gato->sumarXp(1);
            delete drops[i];
            drops[i] = nullptr;
        }
    }
}

void GameManager::liberarDrops() {
    for (int i = 0; i < cantidadDrops; i++) delete drops[i]; // delete nullptr es seguro
    delete[] drops;
    drops = nullptr;
    cantidadDrops = 0;
}

// ===================== Ratas =====================

bool GameManager::areaLibreParaRata(int mapa[40][120], int x, int y) {
    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 9; dx++) {
            int mx = x + dx, my = y + dy;
            if (mx < 0 || mx >= 120 || my < 0 || my >= 40) return false;
            if (mapa[my][mx] != VACIO) return false;
        }
    }
    return true;
}

void GameManager::crearRatasEnSala(int cantidad) {
    cantidadRatas = cantidad;
    ratas = new Rata * [cantidad];

    for (int i = 0; i < cantidad; i++) {
        // Mas tipos de rata a medida que avanzas: sala 1 solo normales, sala 4+ los cuatro
        int tiposDisponibles = mapaIndice + 1;
        if (tiposDisponibles > 4) tiposDisponibles = 4;
        ratas[i] = new Rata((TipoRata)(rand() % tiposDisponibles));

        int rx = 0, ry = 0, intentos = 0;
        bool ok = false;
        while (!ok && intentos < 1000) {
            rx = rand() % 111;
            ry = rand() % 38;
            ok = areaLibreParaRata(mapaActual, rx, ry);
            intentos++;
        }

        ratas[i]->setX(rx);
        ratas[i]->setY(ry);
        ratas[i]->dibujar();
    }
}

int GameManager::ratasVivas() {
    int vivas = 0;
    for (int i = 0; i < cantidadRatas; i++) {
        if (ratas[i]->estaVivo()) vivas++;
    }
    return vivas;
}

void GameManager::liberarRatas() {
    if (ratas == nullptr) return;
    for (int i = 0; i < cantidadRatas; i++) delete ratas[i];
    delete[] ratas;
    ratas = nullptr;
    cantidadRatas = 0;
}

void GameManager::actualizarRatas() {
    for (int i = 0; i < cantidadRatas; i++) {
        if (!ratas[i]->estaVivo()) continue;

        int xAnterior = ratas[i]->getX();
        int yAnterior = ratas[i]->getY();

        ratas[i]->mover(120, 40);
        ratas[i]->borrar(xAnterior, yAnterior);
        ratas[i]->dibujar();
    }
}

// ===================== Proyectiles, colisiones y danio =====================

void GameManager::actualizarProyectiles() {
    for (int i = 0; i < gato->getCantidadProyectiles(); i++) {
        Proyectil* proyectil = gato->getProyectil()[i];

        int xAnterior = proyectil->getX();
        int yAnterior = proyectil->getY();

        proyectil->mover();

        for (int k = 0; k < 3; k++) {
            proyectil->repintarCelda(xAnterior + k, yAnterior, mapaActual);
        }

        if (proyectil->getDistanciaRecorrida() <= 0) continue;

        int mapaX = proyectil->getX();
        int mapaY = proyectil->getY();

        bool fueraDeLimites = (mapaX < 0 || mapaX + 2 >= 120 ||
            mapaY < 0 || mapaY >= 40);
        bool chocoPared = false;

        if (!fueraDeLimites) {
            for (int k = 0; k < 3; k++) {
                if (mapaActual[mapaY][mapaX + k] == PARED) {
                    chocoPared = true;
                    break;
                }
            }
        }

        if (fueraDeLimites || chocoPared) {
            proyectil->detener();
        }
        else {
            proyectil->dibujar();
            Console::BackgroundColor = ConsoleColor::Black;
        }
    }
}

void GameManager::comprobarColisiones() {
    for (int i = 0; i < cantidadRatas; i++) {
        if (!ratas[i]->estaVivo()) continue;

        for (int j = 0; j < gato->getCantidadProyectiles(); j++) {
            Proyectil* proyectil = gato->getProyectil()[j];

            if (proyectil->getDistanciaRecorrida() <= 0) continue; // ya detenido

            if (ratas[i]->colision(proyectil)) {
                ratas[i]->recibirDanio(gato->getDanioArma());

                proyectil->borrar(proyectil->getX(), proyectil->getY());
                proyectil->detener();            // desaparece al impactar

                if (!ratas[i]->estaVivo()) {
                    ratas[i]->borrar(ratas[i]->getX(), ratas[i]->getY());
                    agregarDrop(ratas[i]->getX(), ratas[i]->getY());
                }
                break;                           // este proyectil ya no golpea mas ratas
            }
        }
    }
}

void GameManager::comprobarDanioAlGato() {
    if (invulnerable > 0) {
        invulnerable--;
        return;
    }

    for (int i = 0; i < cantidadRatas; i++) {
        if (!ratas[i]->estaVivo()) continue;

        // gato: 5 x 3 | rata: 8 x 1
        bool solapaX = gato->getX() < ratas[i]->getX() + 8 &&
            gato->getX() + 5 > ratas[i]->getX();
        bool solapaY = gato->getY() < ratas[i]->getY() + 1 &&
            gato->getY() + 3 > ratas[i]->getY();

        if (solapaX && solapaY) {
            gato->recibirDanio(ratas[i]->getDanio());
            invulnerable = 20;   // 20 ticks x 50 ms = 1 segundo
            break;
        }
    }
}

// ===================== Salas =====================

bool GameManager::tocaPuerta() {
    for (int fila = 0; fila < 3; fila++) {
        for (int columna = 0; columna < 5; columna++) {
            int mapaX = gato->getX() + columna;
            int mapaY = gato->getY() + fila;

            if (mapaX < 0 || mapaX >= 120 || mapaY < 0 || mapaY >= 40) continue;

            if (mapaActual[mapaY][mapaX] == PUERTA) return true;
        }
    }
    return false;
}

void GameManager::redibujarTodo() {
    Console::Clear();
    interfaz->dibujarMapa(mapaActual);
    interfaz->dibujarMarco();
    interfaz->dibujarHUD(gato);
    gato->dibujar(mapaActual);
}

bool GameManager::avanzarSala() {
    liberarRatas();
    liberarDrops();

    mapaIndice++;
    if (mapaIndice >= TOTAL_SALAS) return true;

    mapaActual = mapas[mapaIndice];
    gato->setX(spawnX[mapaIndice]);
    gato->setY(spawnY[mapaIndice]);
    invulnerable = 0;

    redibujarTodo();
    crearRatasEnSala(ratasPorSala[mapaIndice]);
    return false;
}

// ===================== Bucle principal =====================

bool GameManager::jugar() {
    interfaz->configurarConsola();
    redibujarTodo();
    crearRatasEnSala(ratasPorSala[0]);

    while (true) {
        int xAnterior = gato->getX();
        int yAnterior = gato->getY();

        gato->mover(mapaActual);
        gato->borrar(xAnterior, yAnterior, mapaActual);

        if (gato->getVida() <= 0) {
            jugadorMurio = true;
            break;
        }

        if (tocaPuerta() && ratasVivas() == 0) {
            if (avanzarSala()) break;   // no quedan mas salas: victoria
            continue;
        }

        // Mientras es invulnerable el gato parpadea (se salta el dibujado cada 3 ticks)
        bool gatoVisible = (invulnerable == 0) || ((invulnerable / 3) % 2 == 0);
        if (gatoVisible) gato->dibujar(mapaActual);

        actualizarRatas();
        comprobarDanioAlGato();
        actualizarProyectiles();
        comprobarColisiones();
        actualizarDrops();
        gato->limpiarProyectiles();

        interfaz->dibujarHUD(gato);
        interfaz->dibujarObjetivo(mapaIndice + 1, TOTAL_SALAS, ratasVivas());
        _sleep(50);
    }

    if (jugadorMurio) {
        // aqui va tu pantalla de derrota (revisa derrota-victoria.h)
        return false;
    }

    pantallaNivelSuperado(true);
    pantallaVictoria();
    return true;
}