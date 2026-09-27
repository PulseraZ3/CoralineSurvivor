#pragma once
#include "Entidad.h"
#include "Arma.h"
class  Padre : public Entidad {
private:
	float vida;
	Arma** arma;
public:
	Padre();
	virtual void dibujar() override;

};
Padre::Padre() {
	vida = 100;
	arma = nullptr;
}
void  Padre::dibujar() {

};
