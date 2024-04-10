#include "fsm_class.h"
#include <Arduino.h>
#include "pantalla.h"
#include "wifi_class.h"
#include "sensor.h"

Pantalla Pan;
WiFi_Class Wifi;
Sensor Sen;

void FSM_Class::SET_STATE(int N){
  STATE_PRINCIPAL=N;
}

void FSM_Class::OPERATION(){
  switch(STATE_PRINCIPAL){
    case INIT:
      Serial.begin(115200);
      Serial.print("Holis");
      Pan.init();
      Sen.init();
      //Wifi.connect();
      Serial.print("Pase");
      STATE_PRINCIPAL=READ_SP;
    break;

    case READ_SP:
      Wifi.get_SP();
      STATE_PRINCIPAL=READ_SENSORS;
    break;

    case READ_SENSORS:
      Sen.lecturaSensor();
      STATE_PRINCIPAL=ACT_PUMP;
    break;

    case ACT_PUMP:
    if (Wifi.HumRelSP < Sen.lecturas[0])
    {
      /* code */
    }
    
      STATE_PRINCIPAL=SHOW_SCREEN;
    break;

    case SHOW_SCREEN:
      Pan.estado(70, "ON", Sen.lecturas[0], Sen.lecturas[1]);
      STATE_PRINCIPAL = UPL_DATA;
    break;

    case UPL_DATA:
      //Wifi.pub(Sen.lecturas[0], Sen.lecturas[1]);
      STATE_PRINCIPAL=READ_SP;
    break;
  }
}