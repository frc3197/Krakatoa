#include <Commands/AutoCommands/SwerveScaleOpp.h>

SwerveScaleOpp::SwerveScaleOpp() {
	Requires(robotDrive);
}

// Called just before this Command runs the first time
void SwerveScaleOpp::Initialize() {
	timer.Reset();
	timer.Start();

	state = 0;
	finished = false;

	eleTime = CommandBase::prefs->GetFloat("scaleEleTime", 0);

	eleSpeedUp = CommandBase::prefs->GetFloat("eleSpeedUp", 0);
	eleSpeedDown = -CommandBase::prefs->GetFloat("eleSpeedDown", 0);

	baseSpeed = CommandBase::prefs->GetFloat("scaleOppBaseSpeed", 0);
	backupSpeed = CommandBase::prefs->GetFloat("scaleOppBackupSpeed", 0);

	straightDistance = CommandBase::prefs->GetFloat("scaleOppStraightDistance",
			0);
	straightAcrossDistance = CommandBase::prefs->GetFloat(
			"scaleOppStraightAcrossDistance", 0);

	driveOverTime = CommandBase::prefs->GetFloat("scaleDriveOverTime", 0);
	backupTime = CommandBase::prefs->GetFloat("scaleBackupTime", 0);

	if (CommandBase::oi->getGamePrefs() == 1) {
		extraSpeed = CommandBase::prefs->GetFloat("scaleOppExtraSpeedRight", 0);
		extraExtraSpeed = CommandBase::prefs->GetFloat(
				"scaleOppExtraExtraSpeedRight", 0);
		swerveAngle = CommandBase::prefs->GetFloat("scaleOppAngleRight", 0);
		swerveBackAngle = CommandBase::prefs->GetFloat("scaleOppBackAngleRight",
				0);
	} else {
		extraSpeed = CommandBase::prefs->GetFloat("scaleOppExtraSpeedLeft", 0);
		extraExtraSpeed = CommandBase::prefs->GetFloat(
				"scaleOppExtraExtraSpeedLeft", 0);
		swerveAngle = CommandBase::prefs->GetFloat("scaleOppAngleLeft", 0);
		swerveBackAngle = CommandBase::prefs->GetFloat("scaleOppBackAngleLeft",
				0);

	}
	claw->ResetTimerPickup();
}

// Called repeatedly when this Command is scheduled to run
void SwerveScaleOpp::Execute() {
	SmartDashboard::PutNumber("Scale State", state);

	bool up = claw->Pickup(true);
	float gyroAngle = robotDrive->gyroAngle();
	if (CommandBase::oi->getGamePrefs() == -1) {
		gyroAngle *= -1;
	}
	float l = 0;
	float r = 0;
	float eleSpeed = 0;
	if (up) {
		switch (state) {
		case StraightToScale: //drive straight distance using encoders
			if (robotDrive->gotoDistance(straightDistance, extraSpeed, 0))
				IncrementState();
			break;
		case SwerveIn:
			if (gyroAngle > swerveAngle) {
				l = baseSpeed;
				r = baseSpeed + extraSpeed + extraExtraSpeed;
			} else {
				IncrementState();
			}
			break;
		case StraightAcross:
			if (robotDrive->gotoDistance(straightAcrossDistance,
					baseSpeed + extraSpeed, swerveAngle))
				IncrementState();
			break;
		case SwerveTowardScale:
			if (gyroAngle < swerveBackAngle) {
				l = baseSpeed + extraSpeed + extraExtraSpeed;
				r = -baseSpeed;
			} else {
				IncrementState();
			}
			break;
		case RaiseFully:
			IncrementState();
			break;
		case DriveOverScale:
			l = -backupSpeed;
			r = -backupSpeed;
			if (timer.HasPeriodPassed(backupTime)) {
				IncrementState();
				claw->ResetTimerDrop();
			}
			break;
		case Drop:
			if (claw->Drop()) {
				IncrementState();
			}
			break;
		case Backup:
			l = backupSpeed;
			r = backupSpeed;
			if (timer.HasPeriodPassed(driveOverTime)) {
				IncrementState();
				claw->ResetTimerDrop();
			}
			break;
		case Lower:
			if (!timer.HasPeriodPassed(eleTime)) {
				eleSpeed = eleSpeedDown;
			} else {
				IncrementState();
			}
			break;
		default:
			l = 0;
			r = 0;
			End();
		}

		if (state >= SwerveTowardScale && state <= Drop) {
			eleSpeed = eleSpeedUp;
		}
		if (eleSpeed != 0)
			auxMotors->ElevatorClaw(eleSpeed);
		if (!(state >= Drop))
			auxMotors->Claw(-.4);
	}
	if (l != 0 && r != 0) {
		if (CommandBase::oi->getGamePrefs() == 1)
			Drive(l, r);
		else
			Drive(r, l);
	}
}

bool SwerveScaleOpp::IsFinished() {
	return finished;
}

void SwerveScaleOpp::End() {
	Drive(0, 0);
	finished = true;
	timer.Stop();
}

void SwerveScaleOpp::IncrementState() {
	state++;
	timer.Reset();
	timer.Start();
}

void SwerveScaleOpp::Interrupted() {

}

void SwerveScaleOpp::Drive(float l, float r) {
	robotDrive->driveBot(l, r);
}
