#include "AuxiliaryMotors.h"
#define CLAW_SPEED .5
#define WINCH_SPEED 1
#define ELE_CLAW_SPEED 1
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

	auxMotors->ClawGrabLim();
	auxMotors->ClawRetractLim();
	auxMotors->ElevatorClawTopLim();
	auxMotors->ElevatorClawBotLim();
	auxMotors->ElevatorWinchForwardLimit();
	auxMotors->ElevatorWinchReverseLimit();

	float clawSpeed = clawMult * CLAW_SPEED;
	float winchSpeed = winchMult * WINCH_SPEED;

	float elevatorWinchSpeed = elevatorWinch * ELE_WINCH_SPEED;
	float elevatorClawSpeed= elevatorClaw * ELE_CLAW_SPEED;
	if (oi->getInTele()) {
		auxMotors->Claw(clawSpeed);
		auxMotors->Winch(winchSpeed);
		auxMotors->ElevatorClaw(elevatorClawSpeed);
		auxMotors->ElevatorWinch(elevatorWinchSpeed);
	}

}

bool AuxiliaryMotors::IsFinished() {
	return false;
}

void AuxiliaryMotors::End() {

}

void AuxiliaryMotors::Interrupted() {

}
