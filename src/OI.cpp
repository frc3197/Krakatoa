#include "OI.h"

#include <WPILib.h>

OI::OI() :
// Process operator interface input here.
//		gyro(0),
// SPIGyro(SPI::kOnboardCS0),
		stick(0), p1A(&stick, BUTTON1), //A
		p1B(&stick, BUTTON2), //B
		p1X(&stick, BUTTON3), //X
		p1Y(&stick, BUTTON4), //Y
		p1LB(&stick, BUTTON5), //LB
		p1RB(&stick, BUTTON6), //RB
		p1Back(&stick, BUTTON7), //Back
		p1Start(&stick, BUTTON8), //Start
		p1LStick(&stick, BUTTON9), //Left Stick
		p1RStick(&stick, BUTTON10) //Right Stick

{
//	SPIGyro.Calibrate();
//	SPIGyro.Reset();
}

float OI::getDriveRight() {
	float raw = -stick.GetRawAxis(5);
	if (raw < .115 && raw > -.115) {
		raw = 0;
	}
	return raw;
}

float OI::getDriveLeft() {
	float raw = -stick.GetRawAxis(1);
	if (raw < .115 && raw > -.115) {
		raw = 0;
	}
	return raw;
}

bool OI::gyroReorientate() {
	return p1LB.Get();
}
