#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
public:
	OI();
	void updateSensors();
	float getDriveRight();
	float getDriveLeft();
	bool gyroReorientate();
	void setGamePrefs(int gameSwitch_);
	int getGamePrefs();
	int getDistance();
	int winch();
	int claw();
	float elevatorWinch();
	float elevatorClaw();
	void rumbleWarning();
	float lerp(float t, float a, float b, float c, float d);

	enum Buttons {
		JOYSTICK, A, B, X, Y, LB, RB, BACK, START, L_STICK, R_STICK
	};

private:
	PowerDistributionPanel *PDP;

	Joystick stick;

	JoystickButton p1A;
	JoystickButton p1B;
	JoystickButton p1X;
	JoystickButton p1Y;
	JoystickButton p1LB;
	JoystickButton p1RB;
	JoystickButton p1Back;
	JoystickButton p1Start;
	JoystickButton p1LStick;
	JoystickButton p1RStick;

	Joystick stick2;

	JoystickButton p2A;
	JoystickButton p2B;
	JoystickButton p2X;
	JoystickButton p2Y;
	JoystickButton p2LB;
	JoystickButton p2RB;
	JoystickButton p2Back;
	JoystickButton p2Start;
	JoystickButton p2LStick;
	JoystickButton p2RStick;

	int gameSwitch;
};

#endif
