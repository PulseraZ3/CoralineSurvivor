#pragma once
#include <iostream>
#include "misAsciiArt.h"
using namespace std;
using namespace System;
class Entidad {
protected:
	string Nombre;
	string Descripcion;
	int x;
	int y;

public:
	Entidad();
	virtual ~Entidad();
	string getNombre();
	string getDescripcion();
	int getX();
	int getY();
	void setNombre(string Nombre);
	void setDescripcion(string Descripcion);
	void setX(int x);
	void setY(int y);
	virtual void mover();
	virtual void borrar(int xAnterior, int yAnterior);
	virtual void dibujar();
};
Entidad::Entidad() {
	Nombre = "";
	Descripcion = "";
	x = 0;
	y = 0;
}
Entidad::~Entidad(){

}
string Entidad::getNombre(){
	return Nombre;
}
string Entidad::getDescripcion(){
	return Descripcion;
}
int Entidad::getX(){
	return x;
}
int Entidad::getY(){
	return y;
}
void Entidad::setNombre(string Nombre){
	this->Nombre = Nombre;
}
void Entidad::setDescripcion(string Descripcion){
	this->Descripcion = Descripcion;
}
void Entidad::setX(int x){
	this->x = x;
}
void Entidad::setY(int y){
	this->y = y;

}


void Entidad::mover(){


}
void Entidad::borrar(int xAnterior, int yAnterior) {

}
void Entidad::dibujar() {

}