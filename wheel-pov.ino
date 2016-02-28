#include "MyWheelPOV.hpp"

static MyWheelPOV pov;

void setup() {
	pov.init();
}

void loop() {
	pov.update();
}
