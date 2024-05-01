#include <Arduino.h>
#include "include.h"
FSM_Class FSM;

//Se realiza el void setup y el void loop con la clase FSM

void setup() {
  FSM.SET_STATE(FSM.INIT);
  FSM.OPERATION();
}

void loop() {
  FSM.OPERATION();
}

