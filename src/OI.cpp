#include "OI.h"

#include <WPILib.h>
#include "CommandBase.h"

#define STICK_DEADZONE .09
#define RUMBLE_TIME 120
#define RUMBLE_DURATION 4

OI::OI() :
		PDP(0),

		stick(0), p1A(&stick, A), p1B(&stick, B), p1X(&stick, X), p1Y(&stick,
				Y), p1LB(&stick, LB), p1RB(&stick, RB), p1Back(&stick, BACK), p1Start(
				&stick, START), p1LStick(&stick, L_STICK), p1RStick(&stick,
				R_STICK),

		stick2(1), p2A(&stick2, A), p2B(&stick2, B), p2X(&stick2, X), p2Y(
				&stick2, Y), p2LB(&stick2, LB), p2RB(&stick2, RB), p2Back(
				&stick2, BACK), p2Start(&stick2, START), p2LStick(&stick2,
				L_STICK), p2RStick(&stick2, R_STICK) {
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
	bool down = p1LB.Get();
	bool up = p1RB.Get();
	if (down && !up)
		return (-1);
	else if (up && !down)
		return (1);
	else
		return (0);
}

int OI::claw() {
	bool in = p2A.Get();
	bool out = p2B.Get();
	if (in && !out)
		return (-1);
	else if (out && !in)
		return (1);
	else
		return (0);
}

float OI::elevatorWinch() {
	float raw = stick2.GetRawAxis(5);
//	float raw = 0;
	if (raw < STICK_DEADZONE && raw > -STICK_DEADZONE)
		raw = 0;
	return raw;
}

float OI::elevatorClaw() {
	float raw = stick2.GetRawAxis(1);
//	float raw = stick2.GetRawAxis(2) - stick2.GetRawAxis(3);
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
