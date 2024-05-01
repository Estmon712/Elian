#ifndef _SENSOR_
#define _SENSOR_

#include <Arduino.h>
//Definición de variables
#define ADC_VREF_mV    5000.0 //Encontrado para el ESP utilizado
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       34 
#define HREL1   36
#define HREL2 39

class Sensor{//Definición de la clase
    public:
    float lecturas[3];
    void init();
    void lecturaSensor();
    private:
};

#endif 