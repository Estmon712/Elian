//Se importan los códigos que se van a utilizar

#include "fsm_class.h"
#include <Arduino.h>
#include "pantalla.h"
#include "wifi_class.h"
#include "sensor.h"
#include <ArduinoJson.h>
#include "valvula.h"

//Definición de  las clases importadas arriba
Pantalla Pan;
WiFi_Class Wifi;
Sensor Sen;
Valv Valve;

//Definición de variables utilizadas en el código
int HumRelSP = 60;
float HumRelProm;
uint8_t Valvu;
String Mac;
String Data;
int a; //minutos*segundos*milis

DynamicJsonDocument Last_data2(2048);

void FSM_Class::SET_STATE(int N){
  STATE_PRINCIPAL=N;
}

void FSM_Class::OPERATION(){
  switch(STATE_PRINCIPAL){
    case INIT: //Realiza la inicicialización de todas las clases
      Serial.begin(115200);
      Pan.init();
      Sen.init();
      Valve.init();
      Wifi.connect();
      Mac = Wifi.get_Mac();//Se obtiene la MAC para identificar el dispositivo
      Serial.println(Mac);
      STATE_PRINCIPAL=READ_SP;//Pasa a realizar lectura del Set Point de la humedad
    break;

    case READ_SP://Realiza el GET al servidor para traer el Set Point
      deserializeJson(Last_data2,Wifi.api_request(Wifi.GET,Mac,""));
      HumRelSP = Last_data2["setpoint"];
      Serial.print(HumRelSP);
      STATE_PRINCIPAL=READ_SENSORS;//Pasa a leer sensores
    break;

    case READ_SENSORS://Lee sensores
      Sen.lecturaSensor();
      STATE_PRINCIPAL=ACT_VALV;//Pasa a activar/desactivar la válvula
    break;

    case ACT_VALV://Activa o desactiva la válvula según Set Point
    HumRelProm = (Sen.lecturas[0] + Sen.lecturas[1])/2;//Realiza el promedio de la humedad relativa
    if (HumRelSP < HumRelProm){
      Valve.apagado();
      Valvu = 0;
    }
    else if (HumRelSP > HumRelProm){
      Valve.encendido();
      Valvu = 1;
    }
    STATE_PRINCIPAL=SHOW_SCREEN;//Pasa a mostrar pantalla
    break;

    case SHOW_SCREEN://Muestra la información en la pantalla
    if (Valvu == 1){
      Pan.estado(HumRelSP, "ON", Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2]);//Muestra que la válvula está abierta
    }
    else if (Valvu == 0){
      Pan.estado(HumRelSP, "OFF", Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2]);//Muestra que la válvula está cerrada
    }
    
      STATE_PRINCIPAL = UPL_DATA;//Sube datos al servidor
    break;

    case UPL_DATA://Sube datos al servidor y decide tiempo de espera
      if (Valvu == 1){//Si la válvula está abierta toma lecturas cada 5 minutos
      Wifi.pub(Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2], "ON");
      a = 5*60*1000; //minutos*segundos*milis
    }
    else if (Valvu == 0){//Si la válvula está cerrada toma lecturas cada 30 minutos
      Wifi.pub(Sen.lecturas[0], Sen.lecturas[1], Sen.lecturas[2], "OFF");
      a = 30*60*1000; //minutos*segundos*milis
    }
      STATE_PRINCIPAL=READ_SP;//Pasa a realizar lectura del Set Point de la humedad
      delay(a);
    break;
  }
}
