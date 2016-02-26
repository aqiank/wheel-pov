#include <FastLED.h>

#define NUM_LEDS (24)
#define NUM_STEPS (360)
#define DATA_PIN (6)
#define HALL_PIN (2)

static const float RADIUS = 0.24; // meters
static const float CIRCUMFERENCE = 2 * RADIUS * PI;

static CRGB leds[NUM_LEDS];
static unsigned long lastActivateTime, revolutionTime;
static unsigned int kph;
static bool bActivated;

void setup() {
	FastLED.addLeds<APA102>(leds, NUM_LEDS);

	pinMode(HALL_PIN, INPUT_PULLUP);
}

void loop() {
	unsigned long long processingTime = micros();

	updateLastActivateTime();
	updateLEDs();

	processingTime = micros();
	delayMicroseconds((1000000 - processingTime) / NUM_STEPS);
}

void updateLastActivateTime() {
	bool bPrevActivated = bActivated;
	bActivated = !digitalRead(HALL_PIN);

	if (bActivated != bPrevActivated) {
		if (bActivated) {
			unsigned long now = millis();
			revolutionTime = now - lastActivateTime;
			lastActivateTime = now;

			// Calculate linear speed
			const float mps = CIRCUMFERENCE * revolutionTime / 1000.0f;
			kph = mps * 3.6;
		}
	}
}

void updateLEDs() {
	unsigned int angle = currentAngle();

	for (int i = 0; i < NUM_LEDS; i++) {
		if (angle % 2 == 1) {
			leds[i] = CRGB::White;
		} else {
			leds[i] = CRGB::Black;
		}
	}

	FastLED.show();
}

unsigned int currentAngle() {
	if (revolutionTime == 0) {
		return 0;
	}

	unsigned int currentTime = millis() - lastActivateTime;
	if (currentTime > revolutionTime) {
		currentTime -= (currentTime / 1000) * 1000;
	}

	return PI * currentTime / revolutionTime;
}
