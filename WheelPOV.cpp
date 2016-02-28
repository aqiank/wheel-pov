#include "WheelPOV.hpp"

#include <Arduino.h>

void WheelPOV::init() {
	pinMode(mHallPin, INPUT);
}

void WheelPOV::update() {
	updateAngle();
	updateLEDs();
}

void WheelPOV::setHallPin(int hallPin) {
	mHallPin = hallPin;
}

void WheelPOV::setRadius(int radius) {
	mRadius = radius;
	mCircumference = 2 * PI * radius;
}

void WheelPOV::setMaxRevolutionTime(unsigned long maxRevolutionTime) {
	mMaxRevolutionTime = maxRevolutionTime;
}

int WheelPOV::hallPin() const {
	return mHallPin;
}

int WheelPOV::radius() const {
	return mRadius;
}

int WheelPOV::circumference() const {
	return mCircumference;
}

unsigned long WheelPOV::maxRevolutionTime() const {
	return mMaxRevolutionTime;
}

void WheelPOV::updateAngle() {
	const bool bPrevActivated = bActivated;
	bActivated = isNearMagnet();

	if (bActivated != bPrevActivated) {
		if (bActivated) {
			const unsigned long now = millis();

			if (now - mLastActivateTime > mMaxRevolutionTime) {
				unsigned int elapsedTime = now - mRevolutionTime;
				mRevolutionTime = elapsedTime;
				elapsedTime -= (elapsedTime / 1000) * 1000;
				mAngle = 360 * elapsedTime / mRevolutionTime;
			} else {
				clear();
				mRevolutionTime = 0;
			}

			mLastActivateTime = now;
		}
	}
}

bool WheelPOV::isNearMagnet() const {
	return digitalRead(mHallPin) == LOW;
}
