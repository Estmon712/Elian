#ifndef _WIFI_CLASS_H_
#define _WIFI_CLASS_H_ //Siempre se coloca en el header de una clase por estructura de C++

#include <Arduino.h>
#include <HTTPClient.h>

class WiFi_Class{
  public: //Los elementos de una clase que se declaran públicos se pueden acceder desde otras partes del código.
  typedef enum{
    GET,
    POST
  }request_type_t;

  void connect ();
  String api_request (request_type_t type, String path, String data);
  bool ping ();
  void set_credentials(char* ssid_1, char* pass_1);
  String get_Mac();
  void pub(uint8_t HR11, uint8_t HR22, float TEMPE, String VALEEST);
  String get_SP();

  private:
  static char* ssid; //Static para que sea estática en una posición en memoria y no se modifique su valor. Char* es un tipo de variable que es una cadena de caracteres.
  static char* pass;
  static String host;
  static String port;
};

#endif