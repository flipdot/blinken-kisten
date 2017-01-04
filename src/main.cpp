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

int kasten_position[] = {32, 61, 106, 149, 179, 280};
uint8_t kasten_hue[] = {0, 0, 0, 0, 0, 0};

void animation_rainbow() {
    static uint8_t k = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV((i + k) % 256, 255, 255);
    }
    k++;
}

void animation_kasten_hue() {
    uint8_t hue = 0;
    uint8_t k = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i == 0 || (k >= 0 && k < (int) sizeof(kasten_position) && i == kasten_position[k])) {
            hue = kasten_hue[k];
            hue += random(0, 4);
            kasten_hue[k] = hue;
            k++;
            // this might be faster compared to modulo
            if (k > sizeof(kasten_hue)) {
                k = 0;
            }
        }
        leds[i] = CHSV(hue, 255, 255);
    }
    delay(50);
}

void animation_kasten_blink() {
    uint8_t hue = 0;
    uint8_t k = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i == 0 || (k >= 0 && k < (int) sizeof(kasten_position) && i == kasten_position[k])) {
            hue = random(0, 256);
            kasten_hue[k] = hue;
            k++;
            // this might be faster compared to modulo
            if (k > sizeof(kasten_hue)) {
                k = 0;
            }
        }
        leds[i] = CHSV(hue, 255, 255);
    }
    delay(1000);
}

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
    // uses way too much space...
    //uint8_t next_animation_counter = 100;
    //void (*animations[3]) (void) = {
    //    animation_rainbow,
    //    animation_kasten_hue,
    //    animation_kasten_blink,
    //};
    //uint8_t current_animation = random(0, sizeof(animations));
    //current_animation = 0;
    while (true) {
        //next_animation_counter--;
        //if (next_animation_counter == 0) {
        //    current_animation = random(0, sizeof(animations));
        //    next_animation_counter = random(100, 500);
        //}
        //current_animation = 0;
        //animations[current_animation]();
        animation_kasten_blink();
        FastLED.show();
        delay(10);
    }
}
