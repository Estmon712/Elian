#include <Arduino.h>
#include "pantalla.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_ST7565_ERC12864_ALT_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 27, /* data=*/ 26, /* cs=*/ 32, /* dc=*/ 25, /* reset=*/33); // ESTA ES

void Pantalla::init(){  
    u8g2.begin();
    u8g2.setContrast(75);
    u8g2.clearBuffer();      
    u8g2.setFont(u8g2_font_helvB10_tr);
    }

void Pantalla::estado(uint8_t HR, String BOMBA, uint8_t HR1, uint8_t HR2){
    u8g2.clearBuffer();

    u8g2.drawStr(7, 15, "Set Point:");
    u8g2.setCursor(90,15);
    u8g2.print(String(HR));

    u8g2.drawStr(7, 30, "Bomba:");
    u8g2.setCursor(90,30);
    u8g2.print(BOMBA);

    u8g2.drawStr(7, 45, "Hum prom:");
    u8g2.setCursor(90,45);
    u8g2.print((HR1+HR2)/2);

    u8g2.drawStr(7, 60, "Temperatura:");
    u8g2.setCursor(90,60);
    u8g2.print(HR2);

    u8g2.drawHLine(0,0,127); // Línea superior
    u8g2.drawHLine(0,63,127); // Línea inferior
    u8g2.drawVLine(0,0,63); // Línea izquierda
    u8g2.drawVLine(127,0,63); //Línea derecha


    u8g2.sendBuffer();
}