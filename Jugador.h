#pragma once
#include "Entidad.h"
class Jugador : public Entidad {
protected:
	float vida;
public:
	Jugador();
	float getVida();
	void recibirDanio(int danio);
};

Jugador::Jugador() : Entidad() {
	vida = 100;
}

float Jugador::getVida() {
	return vida;
}

void Jugador::recibirDanio(int danio) {
	vida -= danio;
}