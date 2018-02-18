#include "AuxiliaryMotors.h"
#define CLAW_SPEED .35
#define WINCH_SPEED 1
#define ELE_WINCH_SPEED .75

AuxiliaryMotors::AuxiliaryMotors() {
	Requires(auxMotors);
}

void AuxiliaryMotors::Initialize() {

}

void AuxiliaryMotors::Execute() {
	float clawMult = oi->claw();
	float winchMult = oi->winch();
	float elevatorClaw = oi->elevatorClaw();
	float elevatorWinch = oi->elevatorWinch();

	bool forward = auxMotors->ClawForwardLimit();
	bool reverse = auxMotors->ClawReverseLimit();

	float clawSpeed = clawMult * CLAW_SPEED;
	float winchSpeed = winchMult * WINCH_SPEED;

	float elevatorWinchSpeed = elevatorWinch * ELE_WINCH_SPEED;

	auxMotors->Claw(clawSpeed);
	auxMotors->Winch(winchSpeed);
	auxMotors->ElevatorClaw(elevatorClaw);
	auxMotors->ElevatorWinch(elevatorWinchSpeed);
}

bool AuxiliaryMotors::IsFinished() {
	return false;
}

void AuxiliaryMotors::End() {

}

void AuxiliaryMotors::Interrupted() {

}
