#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#define NUM_LEDS 280
#define DATA_PIN 3

#define PIN 3

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);
//
CHSV hsvs[NUM_LEDS];
CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
    int kasten_position[] = {32, 61, 106, 149, 179, 280};
    uint16_t kasten_hue[] = {0, 0, 0, 0, 0, 0};
    int k = -1;
    int active_kasten = -1;
    uint16_t hue;
    FastLED.show();
    //hsvs[0].val = 255;
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i == 0 || i == kasten_position[0] || i == kasten_position[1] || i == kasten_position[2] || i == kasten_position[3] || i == kasten_position[4]) {
            hue = random(0, 256);
            k++;
        }
        kasten_hue[k] = hue;
        leds[i] = CHSV(hue, 255, 255);
        //hsvs[i].setHSV(hue, 255, 255);
    }
    FastLED.show();
    delay(1000);
    while (true) {
        k = -1;
        for (int i = 0; i < NUM_LEDS; i++) {
            if (i == 0 || i == kasten_position[0] || i == kasten_position[1] || i == kasten_position[2] || i == kasten_position[3] || i == kasten_position[4]) {
                k++;
                hue = kasten_hue[k];
                hue += random(0, 5);
                hue %= 256;
                kasten_hue[k] = hue;
            }
            if (active_kasten == -1 || active_kasten == k) {
                leds[i] = CHSV(hue, 255, 255);
            } else {
                leds[i] = CRGB(0, 0, 0);
            }
        }
        if (active_kasten > -1) {
            active_kasten = random(0, 7);
            if (active_kasten >= 6) {
                active_kasten = -1;
            }
            delay(200);
        } else {
            if (random(0, 1000) > 995) {
                active_kasten = random(0, 6);
            }
        }
        FastLED.show();
        delay(100);
    }
}
