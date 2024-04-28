#include "sensor.h"

float tempTemp;

void Sensor::init(){
    pinMode(23, OUTPUT);
    pinMode(22, OUTPUT);
}

void Sensor::lecturaSensor(){
    //Se realiza la lectura del sensor
    digitalWrite(23, HIGH);
    digitalWrite(22, HIGH);
    
    delay(1000);

    lecturas[0] = map(analogRead(HREL1), 0, 4096, 100, 0);
    lecturas[1] = map(analogRead(HREL2), 0, 4096, 100, 0);

    digitalWrite(23, LOW);
    digitalWrite(22, LOW);

    delay(1000);

    // read the ADC value from the temperature sensor
    // convert the ADC value to voltage in millivolt
    // convert the voltage to the temperature in °C
    int adcVal = analogRead(PIN_LM35);
    float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
    float tempTemp = milliVolt / 10;

    for (uint8_t i = 0; i < 30; i++)
    {
        int adcVal = analogRead(PIN_LM35);
        float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
        float tempC = milliVolt / 10;
        tempTemp = tempTemp + tempC;
        delay(100);
    }
    tempTemp = tempTemp/30;
    lecturas[2] = tempTemp; 


}