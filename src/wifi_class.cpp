#include "wifi_class.h"
#include <Arduino.h>
#include <ArduinoJson.h>


char* WiFi_Class::ssid = "Jorge"; //Usuario de WiFi
char* WiFi_Class::pass = "Lui$2022*"; //Contraseña WiFi 
String WiFi_Class::host = "http://192.168.82.33";
String WiFi_Class::port = "3000";
WiFiClient client;//Objeto de la clase client que le dice al servidor que el sistema embebido es el cliente
WiFiClientSecure sclient;

StaticJsonDocument<256> dat;
String JSON;
String body_Get;

// Certificado para realizar post con HTTPS
const char* test_root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFVzCCAz+gAwIBAgINAgPlk28xsBNJiGuiFzANBgkqhkiG9w0BAQwFADBHMQsw\n" \
"CQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEU\n" \
"MBIGA1UEAxMLR1RTIFJvb3QgUjEwHhcNMTYwNjIyMDAwMDAwWhcNMzYwNjIyMDAw\n" \
"MDAwWjBHMQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZp\n" \
"Y2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3QgUjEwggIiMA0GCSqGSIb3DQEBAQUA\n" \
"A4ICDwAwggIKAoICAQC2EQKLHuOhd5s73L+UPreVp0A8of2C+X0yBoJx9vaMf/vo\n" \
"27xqLpeXo4xL+Sv2sfnOhB2x+cWX3u+58qPpvBKJXqeqUqv4IyfLpLGcY9vXmX7w\n" \
"Cl7raKb0xlpHDU0QM+NOsROjyBhsS+z8CZDfnWQpJSMHobTSPS5g4M/SCYe7zUjw\n" \
"TcLCeoiKu7rPWRnWr4+wB7CeMfGCwcDfLqZtbBkOtdh+JhpFAz2weaSUKK0Pfybl\n" \
"qAj+lug8aJRT7oM6iCsVlgmy4HqMLnXWnOunVmSPlk9orj2XwoSPwLxAwAtcvfaH\n" \
"szVsrBhQf4TgTM2S0yDpM7xSma8ytSmzJSq0SPly4cpk9+aCEI3oncKKiPo4Zor8\n" \
"Y/kB+Xj9e1x3+naH+uzfsQ55lVe0vSbv1gHR6xYKu44LtcXFilWr06zqkUspzBmk\n" \
"MiVOKvFlRNACzqrOSbTqn3yDsEB750Orp2yjj32JgfpMpf/VjsPOS+C12LOORc92\n" \
"wO1AK/1TD7Cn1TsNsYqiA94xrcx36m97PtbfkSIS5r762DL8EGMUUXLeXdYWk70p\n" \
"aDPvOmbsB4om3xPXV2V4J95eSRQAogB/mqghtqmxlbCluQ0WEdrHbEg8QOB+DVrN\n" \
"VjzRlwW5y0vtOUucxD/SVRNuJLDWcfr0wbrM7Rv1/oFB2ACYPTrIrnqYNxgFlQID\n" \
"AQABo0IwQDAOBgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4E\n" \
"FgQU5K8rJnEaK0gnhS9SZizv8IkTcT4wDQYJKoZIhvcNAQEMBQADggIBAJ+qQibb\n" \
"C5u+/x6Wki4+omVKapi6Ist9wTrYggoGxval3sBOh2Z5ofmmWJyq+bXmYOfg6LEe\n" \
"QkEzCzc9zolwFcq1JKjPa7XSQCGYzyI0zzvFIoTgxQ6KfF2I5DUkzps+GlQebtuy\n" \
"h6f88/qBVRRiClmpIgUxPoLW7ttXNLwzldMXG+gnoot7TiYaelpkttGsN/H9oPM4\n" \
"7HLwEXWdyzRSjeZ2axfG34arJ45JK3VmgRAhpuo+9K4l/3wV3s6MJT/KYnAK9y8J\n" \
"ZgfIPxz88NtFMN9iiMG1D53Dn0reWVlHxYciNuaCp+0KueIHoI17eko8cdLiA6Ef\n" \
"MgfdG+RCzgwARWGAtQsgWSl4vflVy2PFPEz0tv/bal8xa5meLMFrUKTX5hgUvYU/\n" \
"Z6tGn6D/Qqc6f1zLXbBwHSs09dR2CQzreExZBfMzQsNhFRAbd03OIozUhfJFfbdT\n" \
"6u9AWpQKXCBfTkBdYiJ23//OYb2MI3jSNwLgjt7RETeJ9r/tSQdirpLsQBqvFAnZ\n" \
"0E6yove+7u7Y/9waLd64NnHi/Hm3lCXRSHNboTXns5lndcEZOitHTtNCjv0xyBZm\n" \
"2tIMPNuzjsmhDYAPexZ3FL//2wmUspO8IFgV6dtxQ/PeEMMA3KgqlbbC1j+Qa3bb\n" \
"bP6MvPJwNQzcmRk13NfIRmPVNnGuV/u3gm3c\n" \
"-----END CERTIFICATE-----\n"; // Sheets

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

void WiFi_Class::pub(uint8_t HR11, uint8_t HR22){
  //Se debe verificar la publicación de los datos
  dat["HR1"] = HR11;
  dat["HR2"] = HR22;
  dat["ID"] = get_Mac();
  serializeJson(dat,JSON);
  Serial.println(JSON);
  api_request(POST,"POST",JSON);
  deserializeJson(dat,JSON);
  JSON="";
}

String WiFi_Class::get_SP(){
  api_request(GET,"GET","1");
  StaticJsonDocument<300> doc;
  DeserializationError error = deserializeJson(doc, body_Get);
  if (error) { return; }
  HumRelSP = doc["HumRelSP"];
  body_Get = "";
}

void WiFi_Class::api_request (request_type_t type, String path, String data){
  sclient.setCACert(test_root_ca);
  if (type == GET){
    Serial.println("GET Request");
    HTTPClient http; //Objeto de la clase HTTP que me permite usar las funcionalidades de HTTP
    String url = host + ":" + port + "/" + path;
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
          //Interpretar respuesta
        }
      }
    }
  }else if (type == POST){
    Serial.println("POST Request");
    HTTPClient http; //Objeto de la clase HTTP que me permite usar las funcionalidades de HTTP
    //String url = host + ":" + port + "/" + path;
    // String url = "https://hook.us1.make.com/pb43xsx7dpiqphzcwm9eta4bmsrrxhjp";
    String url = "https://script.google.com/macros/s/AKfycbyz18qCYsyEs90Z72bH1B0-f2t2zi7vEcGuWXAhWV74zXO-3kV0YP9-DBW0jrKrzYOHHA/exec?gid=0";

    if (http.begin(sclient,url)){
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