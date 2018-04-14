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
	float getDistance();
	float winch();
	float claw();
	float elevatorWinch();
	float elevatorClaw();
	float getTime();
	void rumbleWarning(float t);
	float lerp(float t, float a, float b, float c, float d);
	void cameraStream();
	void setInTele(bool TeleBool);
	bool getInTele();
<<<<<<< HEAD
	float encodersL();
	float encodersR();
	void encoders(float *l, float *r);
	void encoderReset();
=======
>>>>>>> parent of 0337635... added encoders

	enum buttons {
		JOYSTICK, A, B, X, Y, LB, RB, BACK, START, LSTICK, RSTICK
	};

private:
	float eleSpeedUp;
	float eleSpeedDown;

	//Counter lidar;
<<<<<<< HEAD
	frc::Encoder right, left;

=======
>>>>>>> parent of 0337635... added encoders

	PowerDistributionPanel PDP;

	Joystick stick;

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

	Joystick stick2;

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

	int gameSwitch;

//	float clawUpMult;
//	float clawDownMult;
//	float winchUpMult;
//	float winchDownMult;
//	float elevatorWinchUpMult;
//	float elevatorWinchDownMult;
//	float elevatorClawUpMult;
//	float elevatorClawDownMult;

	bool inTele;
};

#endif  // OI_H
