#ifndef _SENSOR_
#define _SENSOR_

#include <Arduino.h>

#define ADC_VREF_mV    5000.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       34 // ESP32 pin GPIO36 (ADC0) connected to LM35
#define HREL1   36
#define HREL2 39

class Sensor{
    public:
    float lecturas[3];
    void init();
    void lecturaSensor();
    private:
};

#endif 