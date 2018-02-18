#include <Commands/AutoCommands/DriveStraight.h>

#define TIME 15

DriveStraight::DriveStraight() {
	Requires(robotDrive);
}

void DriveStraight::Initialize() {
	timer.Reset();
	timer.Start();

	state = 0;
	finished = false;
}

void DriveStraight::Execute() {
	switch (state) {
	case 0:
		if (!timer.HasPeriodPassed(TIME))
			Drive(robotDrive->autoDriveSpeed);
		else
			state++;
		break;
	default:
	case 1:
		End();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void DriveStraight::End() {
	Drive(0);
	finished = true;
	timer.Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {

}

void DriveStraight::Drive(float speed) {
	robotDrive->advancedDriveBot(speed, speed, 0);
}
