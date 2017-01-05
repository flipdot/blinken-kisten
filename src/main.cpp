#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define NUM_LEDS 280
#define NUM_KASTEN 6
#define DATA_PIN 3
#define PIN 3

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);
CHSV hsvs[NUM_LEDS];
CRGB leds[NUM_LEDS];

uint8_t kasten_position[] = {0, 32, 61, 106, 149, 179}; //, 280};
uint8_t kasten_sat[] = {255, 255, 255, 255, 255, 255};
uint8_t kasten_hue[] = {
    (uint8_t) random(0, 256),
    (uint8_t) random(0, 256),
    (uint8_t) random(0, 256),
    (uint8_t) random(0, 256),
    (uint8_t) random(0, 256),
    (uint8_t) random(0, 256)
};

void animation_rainbow() {
    static uint8_t k = 0;

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV((i + k) % 256, 255, 255);
    }

    k++;
}

void animation_kasten_hue() {
    uint8_t hue;
    uint8_t sat;
    uint8_t k = 0;

    for (int i = 0; i < NUM_LEDS; i++) {
        if (k < NUM_KASTEN && i == kasten_position[k]) {
            hue = kasten_hue[k];
            sat = kasten_sat[k];

            if (sat < 255) {
                if (sat < 250) {
                    sat += 3;
                } else {
                    sat = 255;
                }
            }

            hue += random(0, 2);
            kasten_hue[k] = hue;
            kasten_sat[k] = sat;
            k++;
        }

        leds[i] = CHSV(hue, sat, 255);
    }
}

//void animation_kasten_blink() {
//    uint8_t hue = 0;
//    uint8_t k = 0;
//    for (int i = 0; i < NUM_LEDS; i++) {
//        if (i == 0 || (k >= 0 && k < (int) sizeof(kasten_position) && i == kasten_position[k])) {
//            hue = random(0, 256);
//            kasten_hue[k] = hue;
//            k++;
//            // this might be faster compared to modulo
//            if (k > sizeof(kasten_hue)) {
//                k = 0;
//            }
//        }
//        leds[i] = CHSV(hue, 255, 255);
//    }
//    delay(1000);
//}

void white_random_kasten() {
    uint8_t k = random(0, NUM_KASTEN);
    kasten_sat[k] = 0;
}

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
    while (true) {
        animation_kasten_hue();

        if (random(0, 256) > 253) {
            white_random_kasten();
        }

        FastLED.show();
        delay(100);
    }
}
