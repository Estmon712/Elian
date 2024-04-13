#include "fsm_class.h"
#include <Arduino.h>
#include "pantalla.h"
#include "wifi_class.h"
#include "sensor.h"
#include <ArduinoJson.h>
#include "valvula.h"

Pantalla Pan;
WiFi_Class Wifi;
Sensor Sen;
Valv Valve;

int HumRelSP = 30;
float HumRelProm;

DynamicJsonDocument Last_data2(2048);

void FSM_Class::SET_STATE(int N){
  STATE_PRINCIPAL=N;
}

void FSM_Class::OPERATION(){
  switch(STATE_PRINCIPAL){
    case INIT:
      Serial.begin(115200);
      Pan.init();
      Sen.init();
      Valve.init();
      Wifi.connect();
      STATE_PRINCIPAL=READ_SP;
    break;

    case READ_SP:
      //Wifi.get_SP();
      //deserializeJson(Last_data2,Wifi.api_request(Wifi.GET,"GET",""));
      //HumRelSP = Last_data2["HumRelSP"];
      STATE_PRINCIPAL=READ_SENSORS;
    break;

    case READ_SENSORS:

      Sen.lecturaSensor();
      STATE_PRINCIPAL=ACT_PUMP;
    break;

    case ACT_PUMP:
    HumRelProm = (Sen.lecturas[0] + Sen.lecturas[1])/2;
    if (HumRelSP < HumRelProm){
      Valve.apagado();
    }
    else if (HumRelSP > HumRelProm){
      Valve.encendido();
    }
    
      STATE_PRINCIPAL=SHOW_SCREEN;
    break;

    case SHOW_SCREEN:
      Pan.estado(70, "ON", Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2]);
      STATE_PRINCIPAL = UPL_DATA;
    break;

    case UPL_DATA:
      //Wifi.pub(Sen.lecturas[0], Sen.lecturas[1]);
      STATE_PRINCIPAL=READ_SP;
    break;
  }
}
