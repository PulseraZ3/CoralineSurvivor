#pragma once
#include <iostream>
using namespace std;
class Proyectil;
class Arma {
protected:
	string nombre;
	int danio;
public:
	Arma();
	virtual ~Arma();
	string getNombre();
	int getDanio();
	virtual Proyectil* atacar(int x, int y, int dx, int dy);
};

Arma::Arma() {
	nombre = "";
	danio = 0;
}
Arma::~Arma() {

}
string Arma::getNombre(){
	return nombre;
}
int Arma::getDanio() {
	return danio;
}
Proyectil* Arma::atacar(int x, int y, int dx, int dy){
	return nullptr;
}