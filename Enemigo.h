#pragma once
#include "Entidad.h"
class Enemigo : public Entidad {
protected:
	int vida;
	int danio;
public:
	Enemigo();

    void dibujar() override;
    void borrar(int xAnterior, int yAnterior) override;
    void mover() override;

    int getVida();
    int getDanio();
    bool estaVivo();
    void recibirDanio(int danio);
};
Enemigo::Enemigo() {
    vida = 30;
    danio = 10;

    x = 60;
    y = 10;
}
void Enemigo::dibujar() {
}

void Enemigo::borrar(int xAnterior, int yAnterior) {
}

void Enemigo::mover() {
}

int Enemigo::getVida() {
    return vida;
}

int Enemigo::getDanio() {
    return danio;
}

void Enemigo::recibirDanio(int danio) {
    vida -= danio;
}
bool Enemigo::estaVivo() {
    return vida > 0;
}
