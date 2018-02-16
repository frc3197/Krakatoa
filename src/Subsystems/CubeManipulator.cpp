#include "CubeManipulator.h"

#include "../RobotMap.h"
#include <math.h>
#include "CommandBase.h"
#include "WPILib.h"

CubeManipulator::CubeManipulator() :
		Subsystem("CubeManipulator") {
	InitDefaultCommand();
}

void CubeManipulator::InitDefaultCommand() {
}
bool CubeManipulator::Pickup() {
	switch (pickupState) {
	case RaiseAndFall: //raise claw at speed for time (block falls)
		if (!timer.HasPeriodPassed(1)) {
			CommandBase::auxMotors->ElevatorClaw(.5);
		} else {
			IncrementPickupState();
		}
		break;
	case LowerPickup: //lower claw until lower limit or current
		if (true) {
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

bool CubeManipulator::Drop() {
	switch (dropState) {
	case Open: // opens the claw for allotted time
//		if (CommandBase::auxMotors->ClawCurrent() < maxCurrent) {
		if (!timer.HasPeriodPassed(1)) {
			CommandBase::auxMotors->Claw(-.5);
		} else {
			IncrementPickupState();
		}
		break;
	case LowerDrop: //lower the elevator claw
		if (true) {
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

void CubeManipulator::IncrementPickupState() {
	pickupState++;
	timer.Reset();
	timer.Start();
}

void CubeManipulator::IncrementDropState() {
	dropState++;
	timer.Reset();
	timer.Start();
}
