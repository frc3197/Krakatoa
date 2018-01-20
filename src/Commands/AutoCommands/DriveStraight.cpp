#include <Commands/AutoCommands/DriveStraight.h>

#define SPEED .5
#define TIME .25

DriveStraight::DriveStraight() {
	Requires(robotDrive);
}

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
	timer.Reset();
	timer.Start();

	state = 0;
	finished = false;
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {
	switch (state) {
	case 0:
		if (!timer.HasPeriodPassed(TIME))
			Drive(SPEED);
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
	robotDrive->driveBot(speed, speed);
}
