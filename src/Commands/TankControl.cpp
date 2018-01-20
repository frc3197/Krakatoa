#include "TankControl.h"

TankControl::TankControl() {
	// Use Requires() here to declare subsystem dependencies
	// eg.
	Requires(robotDrive);
}

// Called just before this Command runs the first time
void TankControl::Initialize() {
	oi->gyroReset();
}

// Called repeatedly when this Command is scheduled to run
void TankControl::Execute() {
	float left = oi->getDriveLeft();
	float right = oi->getDriveRight();
	SmartDashboard::PutNumber("left",left);
	SmartDashboard::PutNumber("right",right);

	float angle = oi->getAngle();
	SmartDashboard::PutNumber("angle",angle);

	robotDrive->driveBot(left, right);

}

// Make this return true when this Command no longer needs to run execute()
bool TankControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TankControl::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankControl::Interrupted() {

}
