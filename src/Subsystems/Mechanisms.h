#ifndef MECHANISMS_H
#define MECHANISMS_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
<<<<<<< HEAD
#include "C:\Users\Hexhounds\wpilib\user\cpp\include\ctre\phoenix\MotorControl\CAN\WPI_TalonSRX.h"
=======
#include "ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h"
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
#include "ctre/Phoenix.h"

class Mechanisms: public frc::Subsystem {
public:
	Mechanisms();
	void InitDefaultCommand() override;
	void Winch(float speed);
<<<<<<< HEAD
	void Claw(float speed);
	void ClimbVertical(float speed);
	void ElevatorClaw(float speed);
	bool ClawForwardLimit();
	bool ClawReverseLimit();
=======
	bool Claw(float speed);
	void ElevatorWinch(float speed);
	void ElevatorClaw(float speed);
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
	float ClawCurrent();
private:
	WPI_TalonSRX *winchA;
	WPI_TalonSRX *winchB;
	WPI_TalonSRX *elevatorWinch;
	WPI_TalonSRX *elevatorClaw;
	WPI_TalonSRX *claw;
<<<<<<< HEAD
=======

	float maxClawCurrent;
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
};

#endif
