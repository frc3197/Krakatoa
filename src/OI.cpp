#include "OI.h"

#include <WPILib.h>
#include "CommandBase.h"

#define STICK_DEADZONE .09
#define RUMBLE_TIME 120
#define RUMBLE_DURATION 4

OI::OI() :
// Process operator interface input here.
		LIDARWrite(I2C::kOnboard, 0xC4), //LIDAR
		LIDARRead(I2C::kOnboard, 0xC5), //LIDAR
		PDP(0), //PDP
		stick(0), //Player1
		p1A(&stick, BUTTON1), //A
		p1B(&stick, BUTTON2), //B
		p1X(&stick, BUTTON3), //X
		p1Y(&stick, BUTTON4), //Y
		p1LB(&stick, BUTTON5), //LB
		p1RB(&stick, BUTTON6), //RB
		p1Back(&stick, BUTTON7), //Back
		p1Start(&stick, BUTTON8), //Start
		p1LStick(&stick, BUTTON9), //Left Stick
		p1RStick(&stick, BUTTON10), //Right Stick

		stick2(1), //Player2
		p2A(&stick2, BUTTON1), //A
		p2B(&stick2, BUTTON2), //B
		p2X(&stick2, BUTTON3), //X
		p2Y(&stick2, BUTTON4), //Y
		p2LB(&stick2, BUTTON5), //LB
		p2RB(&stick2, BUTTON6), //RB
		p2Back(&stick2, BUTTON7), //Back
		p2Start(&stick2, BUTTON8), //Start
		p2LStick(&stick2, BUTTON9), //Left Stick
		p2RStick(&stick2, BUTTON10) //Right Stick

{
	LIDARWrite.Write(0x00, 0x04);
	gameSwitch = 0;
}

void OI::updateSensors() {
	CommandBase::robotDrive->encoderDistance();
	getDistance();
//	SmartDashboard::PutData(PDP);
}

float OI::getDriveRight() {
	float raw = -stick.GetRawAxis(5);
//	float raw = -stick2.GetRawAxis(5);
	if (raw < STICK_DEADZONE && raw > -STICK_DEADZONE) {
		raw = 0;
	}
	return raw;
}

float OI::getDriveLeft() {
	float raw = -stick.GetRawAxis(1);
//	float raw = -stick2.GetRawAxis(1);
	if (raw < STICK_DEADZONE && raw > -STICK_DEADZONE) {
		raw = 0;
	}
	return raw;
}

bool OI::gyroReorientate() {
	return p1LB.Get();
}

void OI::setGamePrefs(int gameSwitch_) {
	gameSwitch = gameSwitch_;
}

int OI::getGamePrefs() {
	return gameSwitch;
}

int OI::getDistance() {

	return 0;
}

int OI::winch() {
	bool down = p2A.Get();
	bool up = p2B.Get();
	if (down && !up)
		return (-1);
	else if (up && !down)
		return (1);
	else
		return (0);
}

int OI::claw() {
	bool in = p1RB.Get();
	bool out = p1LB.Get();
	if (in && !out)
		return (-1);
	else if (out && !in)
		return (1);
	else
		return (0);
}

float OI::elevatorWinch() {
	float raw = stick2.GetRawAxis(1);
	if (raw < STICK_DEADZONE && raw > -STICK_DEADZONE)
		raw = 0;
	return raw;
}

float OI::elevatorClaw() {
	float raw = stick.GetRawAxis(2) - stick.GetRawAxis(3);
	if (raw < STICK_DEADZONE && raw > -STICK_DEADZONE)
		raw = 0;
	return raw;
}

void OI::rumbleWarning() {
	float time = DriverStation::GetInstance().GetMatchTime() - RUMBLE_TIME;
	float inMin = 0;
	float inMax = RUMBLE_DURATION;
	float outMin = 0;
	float outMax = 1;
	float timesRumble = 3;
	if (time > 0 && time < RUMBLE_DURATION /*&& time % (RUMBLE_TIME / timesRumble) < ((RUMBLE_TIME / timesRumble) / 2)*/) {
		float rumble = lerp(time, inMin, inMax, outMin, outMax);
		stick.SetRumble(GenericHID::RumbleType::kLeftRumble, rumble);
		stick.SetRumble(GenericHID::RumbleType::kRightRumble, rumble);
	}
}

float OI::lerp(float x, float x0, float x1, float y0, float y1) {
	return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
}
