#include <FastLED.h>

#define NUM_LEDS (36)
#define NUM_STEPS (360)
#define DATA_PIN (18)
#define CLOCK_PIN (13)
#define HALL_PIN (2)

static const unsigned int RADIUS = 24; // meters
static const unsigned int CIRCUMFERENCE = 2 * RADIUS * PI;
static const unsigned long MAX_REVOLUTION_TIME = 300;

static CRGB leds[NUM_LEDS];
static unsigned long lastActivateTime, revolutionTime;
static unsigned int angle;
static bool bActivated;

static void clearLEDs();
static void updateLEDs();
static void updateLastActivateTime();
static unsigned int currentAngle();
static bool isNearMagnet();

void setup() {
	Serial.begin(9600);

	FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	clearLEDs();

	pinMode(HALL_PIN, INPUT);
}

void loop() {
	updateLastActivateTime();
	updateLEDs();
}

static void updateLastActivateTime() {
	bool bPrevActivated = bActivated;
	bActivated = isNearMagnet();

	if (bActivated != bPrevActivated) {
		if (bActivated) {
			const unsigned long now = millis();

			if (now - lastActivateTime > MAX_REVOLUTION_TIME) {
				revolutionTime = now - lastActivateTime;
			} else {
				clearLEDs();
				revolutionTime = 0;
			}

			lastActivateTime = now;
		}
	}
}

static void clearLEDs() {
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB::Black;
	}
	FastLED.show();
}

static void updateLEDs() {
	unsigned int prevAngle = angle;
	angle = currentAngle();

	if (angle != prevAngle && revolutionTime > 0) {
		for (int i = 0; i < NUM_LEDS; i++) {
			if (angle >= 180) {
				leds[i] = CRGB::Blue;
			} else {
				leds[i] = CRGB::Red;
			}
		}

		FastLED.show();
	}
}

static unsigned int currentAngle() {
	unsigned int currentTime = millis() - lastActivateTime;

	currentTime -= (currentTime / 1000) * 1000;

	return 360 * currentTime / revolutionTime;
}

static bool isNearMagnet() {
	return digitalRead(HALL_PIN) == LOW;
}
