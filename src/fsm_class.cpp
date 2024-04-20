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

int HumRelSP = 12;
float HumRelProm;
uint8_t Valvu;
String Mac;

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
      //Wifi.connect();
      Mac = Wifi.get_Mac();
      STATE_PRINCIPAL=READ_SP;
    break;

    case READ_SP:
      //deserializeJson(Last_data2,Wifi.api_request(Wifi.GET,Mac,""));
      //HumRelSP = Last_data2["setpoint"];
      //Serial.print(HumRelSP);
      STATE_PRINCIPAL=READ_SENSORS;
    break;

    case READ_SENSORS:
      Sen.lecturaSensor();
      STATE_PRINCIPAL=ACT_PUMP;
    break;

    case ACT_PUMP:
    Serial.print("HR1: ");
    Serial.println(Sen.lecturas[0]);
    Serial.print("HR2: ");
    Serial.println(Sen.lecturas[1]);
    HumRelProm = (Sen.lecturas[0] + Sen.lecturas[1])/2;
    Serial.print("HumRelProm: ");
    Serial.println(HumRelProm);
    if (HumRelSP < HumRelProm){
      Valve.apagado();
      Valvu = 0;
    }
    else if (HumRelSP > HumRelProm){
      Valve.encendido();
      Valvu = 1;
    }
    
      STATE_PRINCIPAL=SHOW_SCREEN;
    break;

    case SHOW_SCREEN:
    if (Valvu == 1){
      Pan.estado(HumRelSP, "ON", Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2]);
    }
    else if (Valvu == 0){
      Pan.estado(HumRelSP, "OFF", Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2]);
    }
    
      STATE_PRINCIPAL = UPL_DATA;
    break;

    case UPL_DATA:
 /*    if (Valvu == 1){
      Wifi.pub(Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2], "ON");
    }
    else if (Valvu == 0){
      Wifi.pub(Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2], "OFF");
    }
      STATE_PRINCIPAL=READ_SP; */
      STATE_PRINCIPAL=READ_SP;
      delay(5000);
    break;
  }
}
