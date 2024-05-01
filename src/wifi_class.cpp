#include "wifi_class.h"
#include <Arduino.h>
#include <ArduinoJson.h>



char* WiFi_Class::ssid = "iot"; //Usuario de WiFi
char* WiFi_Class::pass = "123456789"; //Contraseña WiFi  
String WiFi_Class::host = "http://10.42.0.1";
String WiFi_Class::port = "8123";
WiFiClient client;//Objeto de la clase client que le dice al servidor que el sistema embebido es el cliente


StaticJsonDocument<256> dat;
String JSON;
String body_Get;

void WiFi_Class::connect (){
  //Se conecta a WiFi
  WiFi.begin (ssid, pass);
  Serial.print("Conectando a WiFi \n");
  while(WiFi.status() != WL_CONNECTED) {//WiFi.status devuelve una variable tipo struct interna que tiene la librería WiFi
    Serial.print(".");
    delay(500);
  }   

  Serial.println( "WiFi Conectado \n");
}

void WiFi_Class::pub(uint8_t HR11, uint8_t HR22,float TEMPE, String VALEEST){
  //Se arma el JSON para subir información
  dat["humidity_1"] = HR11;
  dat["humidity_2"] = HR22;
  dat["temperature"] = TEMPE;
  dat["valve_status"] = VALEEST;
  dat["device_mac"] = get_Mac();
  serializeJson(dat,JSON);
  Serial.println(JSON);
  api_request(POST,"data",JSON);//Se realiza la publicación de los datos
  deserializeJson(dat,JSON);
  JSON="";
}

String WiFi_Class::api_request (request_type_t type, String path, String data){
  if (type == GET){
    Serial.println("GET Request");
    HTTPClient http; //Objeto de la clase HTTP que me permite usar las funcionalidades de HTTP
    String url = host + ":" + port + "/device/setpoint/" + path ;
    Serial.println(url);

    if (http.begin(client,url)){
      http.addHeader("Content-Type", "application/json");
      
      int httpcode = http.GET();
      Serial.println(httpcode);
      //Códigos de status HTTP:
      //200: OK / 400: Bad Request / 401: Unauthorized / 403: Forbidden / 402: Payment required / 404: Not Found 
      if (httpcode > 0){
        if(httpcode == HTTP_CODE_OK){
          Serial.println("GET request success, code 200");
          String body = http.getString(); //Respuesta del servidor a la petición GET
          Serial.println(body);
          body_Get = body;
          return body;//Regresa la respuesta del servidor
        }
      }
    }
  }else if (type == POST){
    Serial.println("POST Request");
    HTTPClient http; //Objeto de la clase HTTP que me permite usar las funcionalidades de HTTP
    String url = host + ":" + port + "/" + path + "/";
    if (http.begin(client,url)){
      http.addHeader("Content-Type", "application/json");
      
      int httpcode = http.POST(data);
      //Códigos de status HTTP:
      //200: OK / 400: Bad Request / 401: Unauthorized / 403: Forbidden / 402: Payment required / 404: Not Found
      Serial.println(httpcode);
      if (httpcode > 0){
        if(httpcode == HTTP_CODE_OK){
          Serial.println("GET request success, code 200");
          String body = http.getString(); //Respuesta del servidor a la petición POST
          Serial.println(body);
          return body;//Regresa la respuesta del servidor
          }
        }
      }
    }
  }

void WiFi_Class::set_credentials(char* ssid_1, char* pass_1){
  ssid = ssid_1;
  pass = pass_1;

}

String WiFi_Class::get_Mac(){
  return WiFi.macAddress();
}