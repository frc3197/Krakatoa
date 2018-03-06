#include <Commands/AutoCommands/DriveStraightDist.h>

DriveStraightDist::DriveStraightDist() {
	Requires(robotDrive);
}

// Called just before this Command runs the first time
void DriveStraightDist::Initialize() {
	timer.Reset();
	timer.Start();

	state = 0;
	finished = false;
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightDist::Execute() {
	switch (state) {
	case 0:
		if(robotDrive->claw->Pickup())
			state++;
		break;
	case 1:
		if (robotDrive->encoderDistance() < robotDrive->autoDriveDist) {
			Drive(robotDrive->autoDriveSpeed);
		} else
			state++;
		break;
	default:
		End();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightDist::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void DriveStraightDist::End() {
	Drive(0);
	finished = true;
	timer.Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightDist::Interrupted() {

}

void DriveStraightDist::Drive(float speed) {
	robotDrive->advancedDriveBot(speed, speed, 0);
}
