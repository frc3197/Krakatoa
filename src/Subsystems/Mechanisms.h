#ifndef MECHANISMS_H
#define MECHANISMS_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h"
#include "ctre/Phoenix.h"

class Mechanisms: public frc::Subsystem {
public:
	Mechanisms();
	void InitDefaultCommand() override;
	void Winch(float speed);
	bool Claw(float speed);
	void ElevatorWinch(float speed);
	void ElevatorClaw(float speed);
	float ClawCurrent();
	bool ClawForwardLimit();
	bool ClawReverseLimit();
private:
	WPI_TalonSRX *winchA;
	WPI_TalonSRX *winchB;
	WPI_TalonSRX *elevatorWinch;
	WPI_TalonSRX *elevatorClaw;
	WPI_TalonSRX *claw;

	float maxClawCurrent;
};

#endif
