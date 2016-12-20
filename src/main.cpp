#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 3

// LEDS is the led count and defined in platformio.ini
Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show();
}

void loop() {
    uint32_t red = strip.Color(10, 0, 0);
    uint32_t off = strip.Color(0, 0, 0);
    uint32_t flash = strip.Color(255, 0, 142);
    uint32_t green = strip.Color(0, 4, 0);
    uint32_t green2 = strip.Color(0, 0, 6);
    uint32_t flame[4];

    for (size_t i = 0; i < 2; i++) {
        int ran = random(10, 30);
        flame[i] = strip.Color(ran, ran/2, 0);
    }

    for (size_t i = 2; i < 4; i++) {
        int ran = random(10, 30);
        flame[i] = strip.Color(ran, 0, ran/2);
    }

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        if (i < 115) {
            if (random(0, 200) == 42) {
                strip.setPixelColor(i, flash);
            } else {
                strip.setPixelColor(i, green);
            }
        } else if (i <= 240-53 && i >= 240 - 62) {
            // first candle flame
            strip.setPixelColor(i, flame[0]);
        } else if (i <= 240-2 && i >= 240 - 52) {
            // first candle wax
            strip.setPixelColor(i, red);
        } else if (i <= 240-68 && i >= 240 - 77) {
            // second candle flame
            strip.setPixelColor(i, flame[1]);
        } else if (i <= 240-78 && i > 240 - 126) {
            // second candle wax
            strip.setPixelColor(i, red);
        } else if (i >= 241 && i <= 250) {
            // third candle wax
            strip.setPixelColor(i, red);
        } else if (i >= 251 && i <= 252) {
            strip.setPixelColor(i, flame[2]);
        } else if (i >= 254 && i <= 266) {
            // fourth candle wax
            strip.setPixelColor(i, red);
        } else if (i > 266) {
            if (random(0, 100) == 42) {
                strip.setPixelColor(i, flash);
            } else {
                strip.setPixelColor(i, green2);
            }
        } else {
            // the rest
            strip.setPixelColor(i, off);
        }
    }

    strip.show();
    delay(random(75, 200));
}
