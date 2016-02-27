#include <FastLED.h>

#define NUM_LEDS (24)
#define NUM_STEPS (360)
#define DATA_PIN (18)
#define CLOCK_PIN (13)
#define HALL_PIN (2)

static const float RADIUS = 0.24; // meters
static const float CIRCUMFERENCE = 2 * RADIUS * PI;

static CRGB leds[NUM_LEDS];
static unsigned long lastActivateTime, revolutionTime;
static unsigned int kph;
static bool bActivated;

static void updateLastActivateTime();
static void updateLEDs();
static unsigned int currentAngle();
static bool isNearMagnet();

void setup() {
	FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);

	pinMode(HALL_PIN, INPUT);
}

void loop() {
	unsigned long long processingTime = micros();

	updateLastActivateTime();
	updateLEDs();

	processingTime = micros();
	delayMicroseconds((1000000 - processingTime) / NUM_STEPS);
}

static void updateLastActivateTime() {
	bool bPrevActivated = bActivated;
	bActivated = isNearMagnet();

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

static void updateLEDs() {
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

static unsigned int currentAngle() {
	if (revolutionTime == 0) {
		return 0;
	}

	unsigned int currentTime = millis() - lastActivateTime;
	if (currentTime > revolutionTime) {
		currentTime -= (currentTime / 1000) * 1000;
	}

	return PI * currentTime / revolutionTime;
}

static bool isNearMagnet() {
	return digitalRead(HALL_PIN) == LOW;
}
