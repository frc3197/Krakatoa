#include "AuxiliaryMotors.h"
#define CLAW_SPEED 1
#define WINCH_SPEED 1

AuxiliaryMotors::AuxiliaryMotors() {
	Requires(auxMotors);
}

void AuxiliaryMotors::Initialize() {

}

void AuxiliaryMotors::Execute() {
	float clawMult = oi->claw();
	float winchMult = oi->winch();
	float elevatorClawSpeed = oi->elevatorClaw();
	float elevatorWinchSpeed = oi->elevatorWinch();

	bool forward = auxMotors->ClawForwardLimit();
	bool reverse = auxMotors->ClawReverseLimit();

	float clawSpeed = clawMult * CLAW_SPEED;
	float winchSpeed = winchMult * WINCH_SPEED;

	auxMotors->Claw(clawSpeed);
	auxMotors->Winch(winchSpeed);
	auxMotors->ElevatorClaw(elevatorClawSpeed);
	auxMotors->ElevatorWinch(elevatorWinchSpeed);
}

bool AuxiliaryMotors::IsFinished() {
	return false;
}

void AuxiliaryMotors::End() {

}

void AuxiliaryMotors::Interrupted() {

}
