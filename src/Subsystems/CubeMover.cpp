#include "CubeMover.h"

#include "../Commands/TankControl.h"

#include "../RobotMap.h"
#include <math.h>

#include "WPILib.h"

#include "ctre/Phoenix.h"

#define SPEED_MULTIPLIER 1
#define ANGLE_DEADZONE 1
#define TURN_ANGLE_DEADZONE 0
#define PERCENT_CHANGE_PER_DEGREE .0075
#define MIN_SPEED .55
#define ENCODER_CONVERSION (M_PI * 6 / 84) / 4

#define AUTO_SPEED .5
#define AUTO_TURN_SPEED .55

CubeMover::CubeMover() :
		Subsystem("CubeMover") {

}

void CubeMover::InitDefaultCommand() {
//	SetDefaultCommand());

}

bool CubeMover::Pickup() {
	switch (pickupState) {
	case RaiseAndFall: //raise claw at speed for time (block falls)
		if (!timer.HasPeriodPassed(1)) {
			CommandBase::auxMotors->ElevatorClaw(.5);
		} else {
			IncrementPickupState();
		}
		break;
	case LowerPickup: //lower claw until lower limit
		if (!CommandBase::auxMotors->ClawForwardLimit()) {
			CommandBase::auxMotors->ElevatorClaw(-.5);
		} else {
			IncrementPickupState();
		}
		break;
	case Close: //close claw until current limit
		if (CommandBase::auxMotors->ClawCurrent() < maxCurrent) {
			CommandBase::auxMotors->Claw(.5);
		} else {
			IncrementPickupState();
		}
		break;
	case RaiseWithCube: //raise claw at speed for time (raise block)
		if (!timer.HasPeriodPassed(1)) {
			CommandBase::auxMotors->ElevatorClaw(0);
		} else {
			IncrementPickupState();
		}
		break;
	default:
		return true;
	}
	return false;
}

bool CubeMover::Drop() {
	switch (dropState) {
	case Open:
//		if (CommandBase::auxMotors->ClawCurrent() < maxCurrent) {
		if (!timer.HasPeriodPassed(1)) {
			CommandBase::auxMotors->Claw(-.5);
		} else {
			IncrementPickupState();
		}
		break;
	case LowerDrop:
		if (!CommandBase::auxMotors->ClawForwardLimit()) {
			CommandBase::auxMotors->ElevatorClaw(-.5);
		} else {
			IncrementPickupState();
		}
		break;
	default:
		return true;
	}
	return false;
}

void CubeMover::IncrementPickupState() {
	pickupState++;
	timer.Reset();
	timer.Start();
}

void CubeMover::IncrementDropState() {
	dropState++;
	timer.Reset();
	timer.Start();
}
