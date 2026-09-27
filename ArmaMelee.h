#pragma once
#include "Arma.h"
#include <iostream>
using namespace std;
class ArmaMelee : public Arma {
public:
	ArmaMelee();
};
ArmaMelee::ArmaMelee() :Arma(){
	nombre = "espada";
	danio = 0;
}
