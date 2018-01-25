#include <Commands/AutoCommands/DriveInside.h>

#define SPEED .5
#define TIME 5

#define TURN_ANGLE -45
#define TURN_SPEED .4

#define COMPLETED_TIMES 1

DriveInside::DriveInside() {
	Requires(robotDrive);
}

// Called just before this Command runs the first time
void DriveInside::Initialize() {
	firstRun = true;

	state = 0;
	finished = false;
	completed = 0;
	turnt = false;
}

// Called repeatedly when this Command is scheduled to run
void DriveInside::Execute() {
	if (firstRun)
	{
		firstRun = false;
		timer.Reset();
		timer.Start();

	}
	SmartDashboard::PutNumber("Time2", timer.Get());
	switch (state) {
	case 0:
		SmartDashboard::PutNumber("driveInsideState", state);
		if (!timer.HasPeriodPassed(TIME))
		{
			Drive(SPEED);
		}
		else
		{
			SmartDashboard::PutBoolean("periodPassed", true);
			state++;
		}
		break;
	case 1:
		SmartDashboard::PutNumber("driveInsideState", state);
//		if (robotDrive->gyroAngle() < 90)
//			robotDrive->driveBot(.3, -.3);
//		else {
//			robotDrive->driveBot(0, 0);
//			state++;
//		}
		if (completed < COMPLETED_TIMES) {
			Turn(90);
		}
		else {
			Drive(0);
			state++;
		}
		break;

	default:
		End();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveInside::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void DriveInside::End() {
	Drive(0);
	finished = true;
	timer.Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveInside::Interrupted() {

}

void DriveInside::Drive(float speed) {
	robotDrive->advancedDriveBot(speed, speed, 0);
}

bool DriveInside::Turn(float angle) {
//	float turnSpeed = TURN_SPEED;
////	if(angle < 0) turnSpeed *= -1;
//	bool done = false;
//	robotDrive->advancedTurnBot(turnSpeed, angle);
//	if (done)
//		completed++;
//	else
//		completed = 0;
//	if (completed >= COMPLETED_TIMES) {
//		completed = 0;
//		return true;
//	}
//	return false;
	float turnSpeed = TURN_SPEED;
	float actual = robotDrive->gyroAngle();
	float desiredAngle;
	bool turnLeft;
	if (turnLeft)
	{
		desiredAngle = -90;
		if(actual > desiredAngle)
		{
			robotDrive->driveBot(-turnSpeed, turnSpeed);
			return (false);
		}
	    else
	    {
			robotDrive->driveBot(0, 0);
			return (true);
		}
	}
	else
	{
		desiredAngle = 90;
		if(actual < desiredAngle)
		{
			robotDrive->driveBot(turnSpeed, -turnSpeed);
			return (false);
		}
	    else
	    {
			robotDrive->driveBot(0, 0);
			return (true);
		}
	}

}
