#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 0

// LEDS is the led count and defined in platformio.ini
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show();
}

void loop() {
    uint32_t c;
    c = strip.Color(255, 0, 0);
    for(uint16_t i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, c);
    }
    strip.show();
}
