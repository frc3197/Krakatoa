#include "None.h"

None::None() {
	// Use Requires() here to declare subsystem dependencies
	// eg.
	Requires(auxMotors);
}

// Called just before this Command runs the first time
void None::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void None::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool None::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void None::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void None::Interrupted() {

}
