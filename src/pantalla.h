#ifndef _PANTALLA_
#define _PANTALLA_

#include <Arduino.h>
#include "U8g2lib.h"

class Pantalla{
    public:

    enum{
        HOOME
    };
    void init();
    void estado(uint8_t HR, String BOMBA, uint8_t HR1, uint8_t HR2);
    int* arr = new int[3];
    private:
};

#endif
