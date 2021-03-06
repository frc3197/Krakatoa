#include "OI.h"

#include <WPILib.h>
#include <CameraServer.h>
#include "CommandBase.h"

#define STICK_DEADZONE .09
#define RUMBLE_TIME 120
#define RUMBLE_DURATION 4

#define ENCODER_CONVERSION (M_PI * 6 / 84)

OI::OI() :
		PDP(0), stick(0), p1A(&stick, A), p1B(&stick, B), p1X(&stick,
				X), p1Y(&stick, Y), p1LB(&stick, LB), p1RB(&stick, RB), p1Back(
				&stick, BACK), p1Start(&stick, START), p1LStick(&stick, LSTICK), p1RStick(
				&stick, RSTICK),

		stick2(1), p2A(&stick2, A), p2B(&stick2, B), p2X(&stick2, X), p2Y(
				&stick2, Y), p2LB(&stick2, LB), p2RB(&stick2, RB), p2Back(
				&stick2, BACK), p2Start(&stick2, START), p2LStick(&stick2,
				LSTICK), p2RStick(&stick2, RSTICK) {
	inTele = false;
	gameSwitch = 0;
	eleSpeedUp = CommandBase::prefs->GetFloat("eleSpeedUp", 0);
	eleSpeedDown = CommandBase::prefs->GetFloat("eleSpeedDown", 0);
}

void OI::updateSensors() {
	CommandBase::robotDrive->lidarDistance();
	CommandBase::robotDrive->gyroAngle();
	CommandBase::robotDrive->current();
	float timeRemaining = getTime();
	SmartDashboard::PutData(&PDP);
	SmartDashboard::PutNumber("TIME", timeRemaining);
}

float OI::getDriveRight() {
	float raw = -stick.GetRawAxis(5);
	if (raw < STICK_DEADZONE && raw > -STICK_DEADZONE) {
		raw = 0;
	}
	return raw;
}

float OI::getDriveLeft() {
	float raw = -stick.GetRawAxis(1);
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

float OI::winch() {
	bool down = p2A.Get();
	bool up = p2B.Get();
	if (down && !up)
		return (-1);
	else if (up && !down)
		return (1);
	else
		return (0);
}

float OI::claw() {
	bool in = p1RB.Get();
	bool out = p1LB.Get();
	if (in && !out) {
		return (-1);
	} else if (out && !in) {
		return (1);
	} else {
		return (0);
	}
}

float OI::elevatorWinch() {
	float raw = stick2.GetRawAxis(1);
	if (raw < STICK_DEADZONE && raw > -STICK_DEADZONE)
		raw = 0;
	return raw;
}

float OI::elevatorClaw() {
	float raw = stick.GetRawAxis(3) - stick.GetRawAxis(2);
	if (raw < 0)
		raw *= eleSpeedDown; //put on preference table
	else
		raw *= eleSpeedUp;

	if (raw < STICK_DEADZONE && raw > -STICK_DEADZONE)
		raw = 0;

	return raw;
}

float OI::getTime() {
	float t = DriverStation::GetInstance().GetMatchTime(); //counts down in current period?
	return t;
}

void OI::setInTele(bool TeleBool) {
	inTele = TeleBool;
	if (inTele) {
		CommandBase::auxMotors->Claw(0);
		CommandBase::auxMotors->Winch(0);
		CommandBase::auxMotors->ElevatorClaw(0);
		CommandBase::auxMotors->ElevatorWinch(0);
	}
}

bool OI::getInTele() {
	return inTele;
}
