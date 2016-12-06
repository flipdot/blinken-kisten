#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 3

// LEDS is the led count and defined in platformio.ini
Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show();
}

void loop() {
    uint32_t red = strip.Color(10, 0, 0);
    uint32_t off = strip.Color(0, 0, 0);
    uint32_t yellow = strip.Color(25, 10, 0);


    for(uint16_t i=0; i < strip.numPixels(); i++) {
        if(i < 240-53 && i > 240 - 62) {
          // first candle flame
          strip.setPixelColor(i, yellow);
        } else if(i < 240-2 && i > 240 - 52) {
          // first candle wax
          strip.setPixelColor(i, red);
        } else if(i < 240-68 && i > 240 - 77) {
          // second candle flame
          strip.setPixelColor(i, yellow);
        } else if(i < 240-78 && i > 240 - 126) {
          // second candle wax
          strip.setPixelColor(i, red);
        } else {
          // the rest
          strip.setPixelColor(i, off);
        }
    }
    strip.show();
}
