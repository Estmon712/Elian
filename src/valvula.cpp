#include "valvula.h"

void Valv::init(){//Se inicializa el pin de activación de la bomba
    pinMode(21, OUTPUT);
}

void Valv::encendido(){
    digitalWrite(21, LOW);//Se enciende la bomba, se usa LOW por el tipo de MOSFET
}
void Valv::apagado(){
    digitalWrite(21,HIGH);//Se enciende la bomba, se usa HIGH por el tipo de MOSFET
}