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

<<<<<<< HEAD
	static const int JOYSTICK = 0;
	static const int BUTTON1 = 1;
	static const int BUTTON2 = 2;
	static const int BUTTON3 = 3;
	static const int BUTTON4 = 4;
	static const int BUTTON5 = 5;
	static const int BUTTON6 = 6;
	static const int BUTTON7 = 7;
	static const int BUTTON8 = 8;
	static const int BUTTON9 = 9;
	static const int BUTTON10 = 10;

private:
	I2C LIDARWrite;
	I2C LIDARRead;

=======
	enum Buttons {
		JOYSTICK, A, B, X, Y, LB, RB, BACK, START, L_STICK, R_STICK
	};

private:
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
	PowerDistributionPanel *PDP;

	Joystick stick;
	Joystick stick2;

<<<<<<< HEAD
	JoystickButton p1A; //A
	JoystickButton p1B; //B
	JoystickButton p1X; //X
	JoystickButton p1Y; //Y
	JoystickButton p1LB; //LB
	JoystickButton p1RB; //RB
	JoystickButton p1Back; //Back
	JoystickButton p1Start; //Start
	JoystickButton p1LStick; //Left Stick Click
	JoystickButton p1RStick; //Right Stick Click

	JoystickButton p2A; //A
	JoystickButton p2B; //B
	JoystickButton p2X; //X
	JoystickButton p2Y; //Y
	JoystickButton p2LB; //LB
	JoystickButton p2RB; //RB
	JoystickButton p2Back; //Back
	JoystickButton p2Start; //Start
	JoystickButton p2LStick; //Left Stick Click
	JoystickButton p2RStick; //Right Stick Click
=======
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
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5

	int gameSwitch;
};

#endif  // OI_H
