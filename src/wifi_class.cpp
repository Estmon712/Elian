#include "wifi_class.h"
#include <Arduino.h>
#include <ArduinoJson.h>


char* WiFi_Class::ssid = "JHONIERM."; //Usuario de WiFi
char* WiFi_Class::pass = "Alcaldia2019"; //Contraseña WiFi 
String WiFi_Class::host = "http://192.168.1.12";
String WiFi_Class::port = "8123";
WiFiClient client;//Objeto de la clase client que le dice al servidor que el sistema embebido es el cliente


StaticJsonDocument<256> dat;
String JSON;
String body_Get;


void WiFi_Class::connect (){
  //Connect to WiFi

  WiFi.begin (ssid, pass);
   Serial.print("Conectando a WiFi \n");
  while(WiFi.status() != WL_CONNECTED) {//WiFi.status devuelve una variable tipo struct interna que tiene la librería WiFi
    Serial.print(".");
    delay(500);
  } 
  
  Serial.println( "WiFi Conectado \n");
  Serial.print( "IP: ");
  Serial.print( String(WiFi.localIP())); //Corresponde a la IP que le haya sido asignada al dispositivo al conectarse a la red WiFi
  Serial.print( "\n");
}

void WiFi_Class::pub(uint8_t HR11, uint8_t HR22,float TEMPE, String VALEEST){
  //Se debe verificar la publicación de los datos
  dat["humidity_1"] = HR11;
  dat["humidity_2"] = HR22;
  dat["temperature"] = TEMPE;
  dat["valve_satus"] = VALEEST;
  dat["device_mac"] = get_Mac();
  serializeJson(dat,JSON);
  Serial.println(JSON);
  api_request(POST,"data",JSON);
  deserializeJson(dat,JSON);
  JSON="";
}

/* String WiFi_Class::get_SP(){
  api_request(GET,"GET","1");
  StaticJsonDocument<300> doc;
  deserializeJson(doc, body_Get);
  HumRelSP = doc["HumRelSP"];
  body_Get = "";
} */

String WiFi_Class::api_request (request_type_t type, String path, String data){
  if (type == GET){
    Serial.println("GET Request");
    HTTPClient http; //Objeto de la clase HTTP que me permite usar las funcionalidades de HTTP
    String url = host + ":" + port + "/device/setpoint/" + path;
    Serial.println(url);
    //String url = "https://hook.us1.make.com/pb43xsx7dpiqphzcwm9eta4bmsrrxhjp";

    if (http.begin(client,url)){
      http.addHeader("Content-Type", "application/json");
      //http.addHeader("Content-Type", "text/plain")//Este es para decirle que el body es un texto
      //En internet hay tablas donde dice qué parámetros se puede enviar por content-type.

      int httpcode = http.GET();
      //Códigos de status HTTP:
      //200: OK / 400: Bad Request / 401: Unauthorized / 403: Forbidden / 402: Payment required / 404: Not Found 
      if (httpcode > 0){
        if(httpcode == HTTP_CODE_OK){
          Serial.println("GET request success, code 200");
          String body = http.getString(); //Respuesta del servidor a la petición GET
          Serial.println(body);
          body_Get = body;
          return body;
          //Interpretar respuesta
        }
      }
    }
  }else if (type == POST){
    Serial.println("POST Request");
    HTTPClient http; //Objeto de la clase HTTP que me permite usar las funcionalidades de HTTP
    //String url = host + ":" + port + "/" + path;
    // String url = "https://hook.us1.make.com/pb43xsx7dpiqphzcwm9eta4bmsrrxhjp";
    String url = host + ":" + port + "/" + path + "/";
    if (http.begin(client,url)){
      http.addHeader("Content-Type", "application/json");
      //http.addHeader("Content-Type", "text/plain")//Este es para decirle que el body es un texto
      //En internet hay tablas donde dice qué parámetros se puede enviar por content-type.

      int httpcode = http.POST(data);
      //Códigos de status HTTP:
      //200: OK / 400: Bad Request / 401: Unauthorized / 403: Forbidden / 402: Payment required / 404: Not Found
      Serial.println(httpcode);
      if (httpcode > 0){
        if(httpcode == HTTP_CODE_OK){
          Serial.println("GET request success, code 200");
          String body = http.getString(); //Respuesta del servidor a la petición GET
          Serial.println(body);
          return body;
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