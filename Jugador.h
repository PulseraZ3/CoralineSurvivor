#pragma once
#include "Entidad.h"
class Jugador : public Entidad {
protected:
	float vida;
	int xp;
	int nivel;
	int xpParaSubir;
public:
	Jugador();
	float getVida();
	void recibirDanio(int danio);
	virtual string* getArt() = 0;
	virtual int getArtAlto() = 0;
	int getXp();
	int getNivel();
	void sumarXp(int cantidad);
	int getXpParaSubir();

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
int Jugador::getXpParaSubir() { return xpParaSubir; }
int Jugador::getXp() { return xp; }
int Jugador::getNivel() { return nivel; }

void Jugador::sumarXp(int cantidad) {
	xp += cantidad;
	if (xp >= xpParaSubir) {
		xp -= xpParaSubir;
		nivel++;
		
	}
}