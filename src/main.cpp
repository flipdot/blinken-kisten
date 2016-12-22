#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show();
}

void loop() {
    uint32_t off = strip.Color(0, 0, 0);
    uint32_t red = strip.Color(10, 0, 0);
    uint32_t greenRgb = strip.Color(0, 5, 0);
    uint32_t greenGrb = strip.Color(0, 0, 5);
    uint32_t flash = strip.Color(255, 0, 142);
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
        if (i <= 240-125) {
			// strip start
            if (random(0, 200) == 42) {
                strip.setPixelColor(i, flash);
            } else {
                strip.setPixelColor(i, greenRgb);
            }
        } else if (i >= 240-126 && i <= 240-78) {
			// 2nd wax
            strip.setPixelColor(i, red);
        } else if (i >= 240-77 && i <= 240-68) {
			// 2nd flame
            strip.setPixelColor(i, flame[1]);
        } else if (i >= 240-62 && i <= 240-53) {
			// 1st flame
            strip.setPixelColor(i, flame[0]);
        } else if (i >= 240-52 && i <= 240-2) {
			// 1st wax
            strip.setPixelColor(i, red);
        } else if (i >= 240+1 && i <= 240+10) {
			// 3rd wax
            strip.setPixelColor(i, red);
        } else if (i >= 240+11 && i <= 240+12) {
			// 3rd flame
            strip.setPixelColor(i, flame[2]);
        } else if (i >= 240+14 && i <= 240+15) {
			// 4th flame
            strip.setPixelColor(i, flame[3]);
        } else if (i >= 240+16 && i <= 240+26) {
			// 4th wax
            strip.setPixelColor(i, red);
        } else if (i >= 240+27) {
			// strip end
            if (random(0, 100) == 42) {
                strip.setPixelColor(i, flash);
            } else {
                strip.setPixelColor(i, greenGrb);
            }
        } else {
            // fallback
            strip.setPixelColor(i, off);
        }
    }

    strip.show();
    delay(random(75, 200));
}
