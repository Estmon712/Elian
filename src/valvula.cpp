#include "valvula.h"

void Valv::init(){
    pinMode(21, OUTPUT);
}

void Valv::encendido(){
    digitalWrite(21, HIGH);
}
void Valv::apagado(){
    digitalWrite(21,LOW);
}