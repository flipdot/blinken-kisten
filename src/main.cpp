#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define NUM_LEDS 280
#define NUM_KASTEN 6
#define DATA_PIN D3
#define BAUDRATE 115200

#define PIN D3

#include <ESP8266WiFi.h>

const char* ssid     = "security-by-obscurity";
const char* password = "LOL DAS SCHREIB ICH DOCH NICHT AUF GITHUB";

const char prefix[] = {0x66, 0x6c, 0x70, 0x64, 0x74};
char buffer[sizeof(prefix)]; // buffer for receiving prefix data; needs to be at least 3 chars

WiFiServer server(42);
int state;
int currentLED;
#define STATE_WAITING   1    // - Waiting for prefix
#define STATE_DO_PREFIX 2    // - Processing prefix
#define STATE_DO_DATA   3    // - Handling incoming LED colors

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

void idle_animation() {
    animation_kasten_hue();
    if (random(0, 256) > 253) {
        white_random_kasten();
    }
    FastLED.show();
    delay(100);
}

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    Serial.begin(BAUDRATE);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
       would try to act as both a client and an access-point and could cause
       network-issues with your other WiFi-devices on your WiFi-network. */
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    server.begin();
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    state = STATE_WAITING;
}

void loop() {
    switch(state) {
        case STATE_WAITING:
            if (Serial.available() > 0) {
                if (Serial.read() == prefix[0]) {
                    state = STATE_DO_PREFIX;
                }
            }
            //idle_animation();
            break;
        case STATE_DO_PREFIX:
            if (Serial.available() > sizeof(prefix) - 2) {
                Serial.readBytes(buffer, sizeof(prefix) - 1);

                for (int i=0; i < sizeof(prefix) - 1; i++) {
                    if (buffer[i] == prefix[i+1]) {
                        state = STATE_DO_DATA;
                        currentLED = 0;
                    } else {
                        // something went wront, go back to waiting
                        state = STATE_WAITING;
                        break;
                    }
                }
            }
            break;
        case STATE_DO_DATA:
            if (Serial.available() > 2) {
                Serial.readBytes(buffer, 3);
                leds[currentLED] = CRGB(buffer[0], buffer[1], buffer[2]);
                currentLED++;
            }
            if (currentLED > NUM_LEDS) {
                FastLED.show();
                delay(10);
                state = STATE_WAITING;
                currentLED = 0;
            }
            break;
    }
}
