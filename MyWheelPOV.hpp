#ifndef MY_WHEEL_POV_HPP
#define MY_WHEEL_POV_HPP

#include "WheelPOV.hpp"

class MyWheelPOV : public WheelPOV {
public:
	MyWheelPOV();

	void init();
	void update();
	void clear();

protected:
	void updateLEDs();
	void updateAngle();
};

#endif
