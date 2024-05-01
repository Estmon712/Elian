#include "sensor.h"

float tempTemp;

void Sensor::init(){//Se inicializan los pines de alimentación para el sensor de humedad
    pinMode(23, OUTPUT);
    pinMode(22, OUTPUT);
}

void Sensor::lecturaSensor(){
    //Se alimentan los sensores de humedad relativa
    digitalWrite(23, HIGH);
    digitalWrite(22, HIGH);
    
    delay(1000);
    //Se guardan las lecturas de humedad relativa
    lecturas[0] = map(analogRead(HREL1), 0, 4096, 100, 0);
    lecturas[1] = map(analogRead(HREL2), 0, 4096, 100, 0);
    //Se apagan los sensores de humedad relativa
    digitalWrite(23, LOW);
    digitalWrite(22, LOW);

    delay(1000);

    int adcVal = analogRead(PIN_LM35);//Toma la lectura del sensor de temperatura
    float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);//Se convierte la lectura a mV
    float tempTemp = milliVolt / 10;//Se hace la conversión de mV a temperatura

    for (uint8_t i = 0; i < 30; i++)//Se toman varias lecturas de temperatura
    {
        int adcVal = analogRead(PIN_LM35);
        float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
        float tempC = milliVolt / 10;
        tempTemp = tempTemp + tempC;
        delay(100);
    }
    tempTemp = tempTemp/30;//Se saca el promedio de las lecturas 
    lecturas[2] = tempTemp;//Se guarda la lectura de temperaturas


}