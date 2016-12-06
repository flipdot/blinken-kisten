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
    uint32_t c;
    c = strip.Color(5, 0, 0);
    for(uint16_t i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, c);
    }
    strip.show();
}
