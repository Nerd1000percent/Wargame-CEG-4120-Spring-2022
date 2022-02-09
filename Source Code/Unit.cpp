///Implementation of Unit
#include "Unit.h"
//Constructor
Terrain::Terrain() {
   this->attackPower = 0;
   this->defensePower= 0;
   this->movement=0;
   this->id=0;
   this->activeFlag=0;
}
//Getter
int Unit::attackPowerGetter () {
   return attackPower;
}
int Unit::defensePowerGetter() {
   return defensePower;
}
int Unit::movementGetter() {
   return defensePower;
}
int Unit::idGetter() {
   return id;
}
int Unit::activeFlagGetter() {
   return activeFlag;
}

//functions

int decreaseDefensePower(){
//math
}

int decreaseAttackPower(){
//math
}