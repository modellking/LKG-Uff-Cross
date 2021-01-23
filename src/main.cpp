#include <Arduino.h>
#include "sk.h"

#define LED_COUNT 36

auto strip = sk();

void fill_rgbw(byte r, byte g, byte b, byte w) {
    for (int i = 0; i < LED_COUNT; i++) {
        strip.color(i,r,g,b,w);
    }
}

void setup() {
    strip.begin(4,LED_COUNT); // pin, LED_count
}

void loop() {
    // put your main code here, to run repeatedly:
    byte r = 0;
    fill_rgbw(r,0,0,0);
    strip.show();
}