#include "MyWheelPOV.hpp"

#include <FastLED.h>

static const int DATA_PIN = 18;
static const int CLOCK_PIN = 13;
static const int NUM_LEDS = 36;
static CRGB leds[NUM_LEDS];

MyWheelPOV::MyWheelPOV() {
}

void MyWheelPOV::init() {
	WheelPOV::init();

	FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	clear();
}

void MyWheelPOV::update() {
	WheelPOV::update();
}

void MyWheelPOV::clear() {
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB::Black;
	}
	FastLED.show();
}

void MyWheelPOV::updateLEDs() {
	unsigned int prevAngle = mAngle;

	if (mAngle != prevAngle && mRevolutionTime > 0) {
		for (int i = 0; i < NUM_LEDS; i++) {
			if (mAngle >= 180) {
				leds[i] = CRGB::Blue;
			} else {
				leds[i] = CRGB::Red;
			}
		}

		FastLED.show();
	}
}

void MyWheelPOV::updateAngle() {
	WheelPOV::updateAngle();
}
