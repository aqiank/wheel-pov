#ifndef WHEEL_POV_HPP
#define WHEEL_POV_HPP

class WheelPOV {
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void clearLEDs() = 0;

	void setHallPin(int hallPin);
	void setRadius(int radius);
	void setMaxRevolutionTime(unsigned long maxRevolutionTime);

	int hallPin() const;
	int radius() const;
	int circumference() const;
	unsigned long maxRevolutionTime() const;

protected:
	virtual bool isNearMagnet() const;
	virtual void updateLEDs() = 0;
	virtual void updateAngle() = 0;

	int mHallPin;
	int mRadius;
	int mCircumference;
	unsigned long mMaxRevolutionTime;

	unsigned int mAngle, mPrevAngle;
	unsigned long mLastActivateTime;
	unsigned long mRevolutionTime;

	bool bActivated;
};

#endif
