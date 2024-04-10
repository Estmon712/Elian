#ifndef _SENSOR_
#define _SENSOR_

#include <Arduino.h>

class Sensor{
    public:
    int* lecturas[2];
    void init();
    void lecturaSensor();
    private:
};

#endif 