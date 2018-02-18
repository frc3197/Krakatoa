#include "AuxiliaryMotors.h"
#define CLAW_SPEED .25
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

<<<<<<< HEAD
	bool forward = auxMotors->ClawForwardLimit();
	bool reverse = auxMotors->ClawReverseLimit();

=======
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
	float clawSpeed = clawMult * CLAW_SPEED;
	float winchSpeed = winchMult * WINCH_SPEED;

	auxMotors->Claw(clawSpeed);
	auxMotors->Winch(winchSpeed);
	auxMotors->ElevatorClaw(elevatorClawSpeed);
<<<<<<< HEAD
	auxMotors->ClimbVertical(elevatorWinchSpeed);
=======
	auxMotors->ElevatorWinch(elevatorWinchSpeed);
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
}

bool AuxiliaryMotors::IsFinished() {
	return false;
}

void AuxiliaryMotors::End() {

}

void AuxiliaryMotors::Interrupted() {

}
