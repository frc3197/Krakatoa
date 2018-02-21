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
	void Claw(float speed);
	void ElevatorWinch(float speed);
	void ElevatorClaw(float speed);
	bool ClawGrabLim();
	bool ClawRetractLim();
	bool ElevatorClawTopLim();
	bool ElevatorClawBotLim();
	bool ElevatorWinchForwardLimit();
	bool ElevatorWinchReverseLimit();
	float ClawCurrent();

	void runTester();
private:
	WPI_TalonSRX *winchA;
	WPI_TalonSRX *winchB;
	WPI_TalonSRX *elevatorWinch;
	WPI_TalonSRX *elevatorClaw;
	WPI_TalonSRX *claw;

	float maxObservedClawCurrent;
	float elevatorDownMultiplier;
};

#endif
