#include "sensor.h"

void Sensor::init(){
    //Aquí se realiza la inicialización de los pines del sensor
    //Se debe definir que sensores se van a utilizar
}

void Sensor::lecturaSensor(){
    //Se realiza la lectura del sensor
    lecturas[0] = 50;
    lecturas[1] = 60;

    // read the ADC value from the temperature sensor
    int adcVal = analogRead(PIN_LM35);
    // convert the ADC value to voltage in millivolt
    float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
    // convert the voltage to the temperature in °C
    float tempC = milliVolt / 10;
    lecturas[2] = tempC;
}