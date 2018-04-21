#include <Commands/AutoCommands/AutoCalls.h>

AutoCalls::AutoCalls() {
	Reset();
//	double rAndF = AutoTimings->GetDouble("RaiseAndFall (Time)", 0.5);
//	double rAndFSpeed = AutoTimings->GetDouble("RaiseAndFall (Speed)", -0.5);
//	double lPickup = AutoTimings->GetDouble("Lower Pickup (Speed)", 0.5);
//	double close = AutoTimings->GetDouble("Close (Speed)", -0.5);
}

bool AutoCalls::Pickup(bool goUp) {
	SmartDashboard::PutNumber("Pickup States", pickupState);

	float clawSpeed = 0;
	float eleClawSpeed = 0;

	switch (pickupState) {
	case RaiseAndFall: //raise claw at speed for time (block falls)
		if (!timerPickup.HasPeriodPassed(0.75)) {
			eleClawSpeed = (0.5);
		} else {
			IncrementPickupState();
		}
		break;
	case LowerPickup: //lower claw until lower limit
		if (!CommandBase::auxMotors->ElevatorClawBotLim()) {
			eleClawSpeed = (-0.5);
		} else {
			IncrementPickupState();
		}
		break;
	case Close: //close claw until current limit
		if (!timerPickup.HasPeriodPassed(1.0)) {
			clawSpeed = (-0.75);
		} else {
			IncrementPickupState();
		}
		break;
	case RaiseWithCube: //raise claw at speed for time (raise block)
		if (!timerPickup.HasPeriodPassed(.25)) {
			eleClawSpeed = (.85);
		} else {
			IncrementPickupState();
		}
		break;
	default:
		break;
	}
	CommandBase::auxMotors->Claw(clawSpeed);
	if (goUp || pickupState <= RaiseWithCube)
		CommandBase::auxMotors->ElevatorClaw(eleClawSpeed);

	return pickupState > Close;
}

bool AutoCalls::Drop() {
	switch (dropState) {
	case Open:

		if (!CommandBase::auxMotors->ClawRetractLim()) {
			CommandBase::auxMotors->Claw(0.65);
		} else {
			IncrementDropState();
		}
		break;
	default:
		return true;
	}
	return false;
}

void AutoCalls::Reset() {
	leftOrRight = CommandBase::oi->getGamePrefs();
	pickupState = LowerPickup;
	dropState = -1;
	IncrementPickupState();
	IncrementDropState();
}

void AutoCalls::IncrementPickupState() {
	pickupState++;
	ResetTimerPickup();
}

void AutoCalls::IncrementDropState() {
	dropState++;
	ResetTimerDrop();
}

void AutoCalls::ResetTimerDrop() {
	timerDrop.Reset();
	timerDrop.Start();

}

void AutoCalls::ResetTimerPickup() {
	timerPickup.Reset();
	timerPickup.Start();
}
