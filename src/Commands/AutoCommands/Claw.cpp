#include <Commands/AutoCommands/Claw.h>

Claw::Claw() {
	leftOrRight = CommandBase::oi->getGamePrefs();
	pickupState = -1;
	dropState = -1;
	maxCurrent = CommandBase::robotDrive->prefs->GetFloat("Claw Max Current",
			10);
	IncrementPickupState();
	IncrementDropState();
}

bool Claw::Pickup() {
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

bool Claw::Drop() {
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

void Claw::IncrementPickupState() {
	pickupState++;
	timer.Reset();
	timer.Start();
}

void Claw::IncrementDropState() {
	dropState++;
	timer.Reset();
	timer.Start();
}
