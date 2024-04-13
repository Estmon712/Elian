#include "sensor.h"

void Sensor::init(){
    pinMode(23, OUTPUT);
    pinMode(22, OUTPUT);
}

void Sensor::lecturaSensor(){
    //Se realiza la lectura del sensor
    digitalWrite(23, HIGH);
    digitalWrite(22, HIGH);
    
    delay(1000);

    lecturas[0] = map(analogRead(39), 0, 4096, 100, 0);
    lecturas[1] = map(analogRead(34), 0, 4096, 100, 0);

    digitalWrite(23, LOW);
    digitalWrite(22, LOW);

    delay(1000);

    // read the ADC value from the temperature sensor
    int adcVal = analogRead(PIN_LM35);
    // convert the ADC value to voltage in millivolt
    float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
    // convert the voltage to the temperature in °C
    float tempC = milliVolt / 10;
    Serial.println(tempC);
    lecturas[2] = tempC;
}