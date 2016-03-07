#include "MyWheelPOV.hpp"
#include "image.h"

#include <FastLED.h>

static const int DATA_PIN = 18;
static const int CLOCK_PIN = 13;
static const int NUM_LEDS = 36;
static CRGB leds[NUM_LEDS];

MyWheelPOV::MyWheelPOV() {
	mHallPin = 2;
	mRadius = 26;
	mPrevAngle = 0;
	mAngle = 0;
	mMaxRevolutionTime = 1000;
	mLastActivateTime = 0;
}

void MyWheelPOV::init() {
	WheelPOV::init();

	FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	clearLEDs();
}

void MyWheelPOV::update() {
	WheelPOV::update();
}

void MyWheelPOV::clearLEDs() {
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB::Black;
	}
	FastLED.show();
}

void MyWheelPOV::updateLEDs() {
	for (int i = 0; i < NUM_LEDS; i++) {
		const size_t offset = mAngle * NUM_LEDS * 3;
		const uint8_t r = image[offset + (i * 3) + 0];
		const uint8_t g = image[offset + (i * 3) + 1];
		const uint8_t b = image[offset + (i * 3) + 2];
		leds[i] = CRGB(r, g, b);
	}

	FastLED.show();
}

void MyWheelPOV::updateAngle() {
	WheelPOV::updateAngle();
}
