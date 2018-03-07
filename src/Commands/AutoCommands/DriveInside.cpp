#include <Commands/AutoCommands/AutoCalls.h>
#include <Commands/AutoCommands/DriveInside.h>

#define DEFAULT_DIST 0
#define DISTANCE_OFFSET 0

DriveInside::DriveInside() {
	Requires(robotDrive);
}

// Called just before this Command runs the first time
void DriveInside::Initialize() {
//	for (int i = 0; i < 3; i++) {
//		dist[i] = CommandBase::prefs->GetFloat(
//				"distance" + (i + DISTANCE_OFFSET), DEFAULT_DIST);
//		SmartDashboard::PutNumber("Distance " + (std:str)i, dist[i]);
//
//	}
	dist[0] = CommandBase::prefs->GetFloat("distance0", DEFAULT_DIST);
	dist[1] = CommandBase::prefs->GetFloat("distance1", DEFAULT_DIST);
	dist[2] = CommandBase::prefs->GetFloat("distance2", DEFAULT_DIST);
	leftOrRight = oi->getGamePrefs();
	turnAngle = leftOrRight * robotDrive->autoTurnAngle;
	state = -1;
	IncrementState();
}

// Called repeatedly when this Command is scheduled to run
void DriveInside::Execute() {
	SmartDashboard::PutNumber("turnAngleReceived", turnAngle);
	switch (state) {
	case Startup:
		if (claw->Pickup()) // returns true when finished
			IncrementState();
		break;
	case DriveForwardOne:
		if (robotDrive->encoderDistance() < /*dist[0]*/35) {
			Drive(robotDrive->autoDriveSpeed);
		} else {
			IncrementState();
		}
		break;
	case TurnOne:
		done = robotDrive->advancedTurnBot(robotDrive->autoTurnSpeed,
				turnAngle);
		if (done) {
			IncrementState();
		}
		break;
	case DriveForwardTwo:
		if (robotDrive->encoderDistance() < dist[1]) {
			Drive(robotDrive->autoDriveSpeed);
		} else {
			IncrementState();
		}
		break;
	case TurnTwo:
		done = robotDrive->advancedTurnBot(robotDrive->autoTurnSpeed, 0);
		if (done) {
			IncrementState();
		}
		break;
	case DriveForwardThree:
		if (robotDrive->encoderDistance() < dist[2]) {
			Drive(robotDrive->autoDriveSpeed);
		} else {
			IncrementState();
		}
		break;
	case DropCube:
		if (claw->Drop())
			IncrementState();
		break;
	default:
		End();
	}
}

bool DriveInside::IsFinished() {
	return finished;
}

void DriveInside::End() {
	Drive(0);
	finished = true;
	timer.Stop();
}

void DriveInside::Interrupted() {

}

void DriveInside::IncrementState() {
	state++;
	timer.Reset();
	timer.Start();
	robotDrive->gyroReset();
	robotDrive->encoderReset();
}

void DriveInside::Drive(float speed) {
	robotDrive->advancedDriveBot(speed, speed, 0);
}
