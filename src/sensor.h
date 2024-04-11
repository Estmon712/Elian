#ifndef _SENSOR_
#define _SENSOR_

#include <Arduino.h>

#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       26 // ESP32 pin GPIO36 (ADC0) connected to LM35

class Sensor{
    public:
    float lecturas[3];
    void init();
    void lecturaSensor();
    private:
};

#endif 