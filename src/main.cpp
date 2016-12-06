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
    uint32_t yellow = strip.Color(20, 20, 0);


    for(uint16_t i=0; i < strip.numPixels(); i++) {
        if(i < 240-6 && i > 240 - 62) {
          // first candle
          strip.setPixelColor(i, red);
        } else if(i < 240-70 && i > 240 - 126) {
          // second candle
          strip.setPixelColor(i, red);
        } else {
          strip.setPixelColor(i, off);
        }
    }
    strip.show();
}
