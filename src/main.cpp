#include <Arduino.h>
#include "include.h"
#include <Wire.h>

FSM_Class FSM;

void setup() {
  FSM.SET_STATE(FSM.INIT);
  FSM.OPERATION();
}

void loop() {
  FSM.OPERATION();
}

