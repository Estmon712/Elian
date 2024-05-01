#ifndef _PANTALLA_
#define _PANTALLA_

#include <Arduino.h>
#include "U8g2lib.h"

class Pantalla{//Definición de la clase
    public:

    enum{
        HOOME
    };
    void init();
    void estado(uint8_t HR, String VALVULA, uint8_t HR1, uint8_t HR2, float TEMP);
    private:
};

#endif
