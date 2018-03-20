#include "OI.h"

#include <WPILib.h>
#include <CameraServer.h>
#include "CommandBase.h"

#define STICK_DEADZONE .09
#define RUMBLE_TIME 120
#define RUMBLE_DURATION 4

#define ENCODER_CONVERSION (M_PI * 6 / 84)

OI::OI() :
//lidar(0),
//		digitalRightForward(1), //rf
//		digitalRightBackward(2), //rb
//		digitalLeftForward(3), //lf
//		digitalLeftBackward(4), //lb
		right(1, 2, false, frc::Encoder::k4X), //one is reversed idk
		left(3, 4, false, frc::Encoder::k4X),
		PDP(0), stick(0), p1A(&stick, A), p1B(&stick, B), p1X(
				&stick, X), p1Y(&stick, Y), p1LB(&stick, LB), p1RB(&stick, RB), p1Back(
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

//	frc::Encoder right(1, 2, false, Encoder::k4X);
//	frc::Encoder left(3, 4, false, Encoder::k4X);

	right.SetDistancePerPulse(ENCODER_CONVERSION);
	left.SetDistancePerPulse(ENCODER_CONVERSION);
	right.SetSamplesToAverage(5);
	left.SetSamplesToAverage(5);
	right.SetMinRate(1.0);
	left.SetMinRate(1.0);

//	elevatorWinchUpMult = CommandBase::prefs->GetFloat("Elevator Winch Up Mult",
//			1);
//	elevatorWinchDownMult = CommandBase::prefs->GetFloat(
//			"Elevator Winch Down Mult", 1);
//	elevatorClawUpMult = CommandBase::prefs->GetFloat("Elevator Claw Up Mult",
//			1);
//	elevatorClawDownMult = CommandBase::prefs->GetFloat(
//			"Elevator Claw Down Mult", 1);
}

void OI::updateSensors() {
	CommandBase::robotDrive->encoderDistance();
	CommandBase::robotDrive->gyroAngle();
	getDistance();
	float timeRemaining = getTime();
	rumbleWarning(timeRemaining);
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

float OI::getDistance() {
//	float cm = (counter->GetPeriod() * 100000) - 18;
//	float in = cm / 25
	return 0;
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

void OI::rumbleWarning(float t) {
//	float inMin = 0;
//	float inMax = RUMBLE_DURATION;
//	float outMin = 0;
//	float outMax = 1;
//	float timesRumble = 3;
//	if (time > 0 && time < RUMBLE_DURATION /*&& time % (RUMBLE_TIME / timesRumble) < ((RUMBLE_TIME / timesRumble) / 2)*/) {
//		float rumble = lerp(time, inMin, inMax, outMin, outMax);
//		stick.SetRumble(GenericHID::RumbleType::kLeftRumble, rumble);
//		stick.SetRumble(GenericHID::RumbleType::kRightRumble, rumble);
//	}
}

float OI::lerp(float x, float x0, float x1, float y0, float y1) {
	return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
}

//void OI::cameraStream() {
//}
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

float OI::encodersL() {
	float leftVal = left.GetDistance();
	SmartDashboard::PutNumber("Encoder left", leftVal);
	return leftVal;
}
float OI::encodersR() {
	float rightVal = right.GetDistance();
	SmartDashboard::PutNumber("Encoder right", rightVal);
	return rightVal;
}

void OI::encoders(float* l, float* r){
	*l = encodersL();
	*r = encodersR();
}

void OI::encoderReset() {
	left.Reset();
	right.Reset();
}
