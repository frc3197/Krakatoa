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

	if (CommandBase::oi->getGamePrefs() == 1) {
		extraSpeed = CommandBase::prefs->GetFloat("swerveExtraSpeedRight",
				0);
		swerveAngle = CommandBase::prefs->GetFloat("swerveAngleRight", 0);
	} else {
		extraSpeed = CommandBase::prefs->GetFloat("swerveExtraSpeedLeft",
				0);
		swerveAngle = CommandBase::prefs->GetFloat("swerveAngleLeft", 0);
	}
	claw->ResetTimerPickup();

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
		l = baseSpeed;
		r = baseSpeed;
	case SwerveAway:
		if (gyroAngle < swerveAngle) {
			l += extraSpeed;
		} else {
			IncrementState();
		}
		break;
	case SwerveIn:
		if (gyroAngle > 5 && !timer.HasPeriodPassed(2)) {
			r += extraSpeed;
		} else {
			claw->ResetTimerDrop();
			IncrementState();
		}

		break;
	case Drop:
		if (claw->Drop()) {
			IncrementState();
			l = baseSpeed;
			r = baseSpeed;
		}
		break;

	default:
		End();
		}
	}
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
