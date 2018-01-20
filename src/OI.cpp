#include "OI.h"

#include <WPILib.h>

OI::OI() :
		// Process operator interface input here.
		gyro(0),
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

void OI::gyroReset() {
	gyro.Calibrate();
	gyro.Reset();
	gyro.SetSensitivity(.0064);
	SmartDashboard::PutNumber("calibrated", -1);
}

float OI::getAngle() {
	double raw = gyro.GetAngle();
	SmartDashboard::PutNumber("raw", raw);
	SmartDashboard::PutNumber("calibrated2", -1);
	return raw;
	return 2;
}
