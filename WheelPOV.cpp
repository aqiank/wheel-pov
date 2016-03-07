#include "WheelPOV.hpp"

#include <Arduino.h>

void WheelPOV::init() {
	pinMode(mHallPin, INPUT);
}

void WheelPOV::update() {
	updateAngle();
	if (mAngle != mPrevAngle && mRevolutionTime > 0) {
		updateLEDs();
	}
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
	const unsigned long now = millis();
	const bool bPrevActivated = bActivated;
	bActivated = isNearMagnet();
	
	if (bActivated != bPrevActivated) {
		if (bActivated) {
			mRevolutionTime = now - mLastActivateTime;
			mLastActivateTime = now;
		}
	}

	if (mRevolutionTime > 0) {
		const unsigned long angleTime = now - mLastActivateTime;
		mAngle = (360 * angleTime / mRevolutionTime) % 360;
		if (now - mLastActivateTime > mRevolutionTime) {
			mRevolutionTime = 0;
			clearLEDs();
		}
	}
}

bool WheelPOV::isNearMagnet() const {
	return digitalRead(mHallPin) == LOW;
}
