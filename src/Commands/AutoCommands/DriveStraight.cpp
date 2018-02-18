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

bool DriveStraight::IsFinished() {
	return finished;
}

void DriveStraight::End() {
	Drive(0);
	finished = true;
	timer.Stop();
}

void DriveStraight::Interrupted() {

}

void DriveStraight::Drive(float speed) {
	robotDrive->advancedDriveBot(speed, speed, 0);
}
