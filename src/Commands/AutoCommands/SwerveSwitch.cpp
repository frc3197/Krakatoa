#include <Commands/AutoCommands/SwerveSwitch.h>

SwerveSwitch::SwerveSwitch() {
	Requires(robotDrive);
}

// Called just before this Command runs the first time
void SwerveSwitch::Initialize() {
	timer.Reset();
	timer.Start();

	state = 0;
	finished = false;

	baseSpeed = CommandBase::prefs->GetFloat("swerveBaseSpeed", 0);
	intoSwitchSpeed = CommandBase::prefs->GetFloat("switchIntoSwitchSpeed", 0);

	if (CommandBase::oi->getGamePrefs() == 1) {
		extraSpeed = CommandBase::prefs->GetFloat("switchExtraSpeedRight", 0);
		extraExtraSpeed = CommandBase::prefs->GetFloat(
				"switchExtraExtraSpeedRight", 0);
		swerveAngle = CommandBase::prefs->GetFloat("switchAngleRight", 0);
	} else {
		extraExtraSpeed = CommandBase::prefs->GetFloat(
				"switchExtraExtraSpeedLeft", 0);
		extraSpeed = CommandBase::prefs->GetFloat("switchExtraSpeedLeft", 0);
		swerveAngle = CommandBase::prefs->GetFloat("switchAngleLeft", 0);
	}
	claw->ResetTimerPickup();
	claw->Reset();
}

// Called repeatedly when this Command is scheduled to run
void SwerveSwitch::Execute() {
	bool up = claw->Pickup();
	float gyroAngle = robotDrive->gyroAngle();
	if (CommandBase::oi->getGamePrefs() == -1) {
		gyroAngle *= -1;
	}
	float l = 0;
	float r = 0;
	if (up) {
		switch (state) {
		case SwerveAway:
			if (gyroAngle < swerveAngle) {
				l = extraSpeed;
				r = baseSpeed;
			} else {
				IncrementState();
			}
			break;
		case SwerveIn:
			if (gyroAngle > 5 && !timer.HasPeriodPassed(2)) {
				l = baseSpeed;
				r = extraSpeed + extraExtraSpeed;
			} else {
				IncrementState();
			}
			break;
		case IntoSwitch:
			l = intoSwitchSpeed;
			r = intoSwitchSpeed;
			if (timer.HasPeriodPassed(1.5)) {
				claw->ResetTimerDrop();
				IncrementState();
			}
			break;
		case Drop:
			if (claw->Drop()) {
				IncrementState();
			}
			break;

		default:
			End();
		}
	}
//	if (up && !(state >= Drop)) {
//		auxMotors->Claw(-.4);
//	}

	if (CommandBase::oi->getGamePrefs() == 1)
		Drive(l, r);
	else
		Drive(r, l);

}

// Make this return true when this Command no longer needs to run execute()
bool SwerveSwitch::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void SwerveSwitch::End() {
	Drive(0, 0);
	finished = true;
	timer.Stop();
}

void SwerveSwitch::IncrementState() {
	state++;
	timer.Reset();
	timer.Start();
	robotDrive->encoderReset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SwerveSwitch::Interrupted() {

}

void SwerveSwitch::Drive(float l, float r) {
	robotDrive->driveBot(l, r);
}
