#include <Commands/AutoCommands/DriveInside.h>

#define DEFAULT_DIST 0
#define DISTANCE_OFFSET 0

DriveInside::DriveInside() {
	Requires(robotDrive);
	Requires(cubeMover);
	Initialize();
}

void DriveInside::Initialize() {
	for (int i = 0; i < 3; i++) {
		dist[i] = CommandBase::prefs->GetFloat(
				"distance" + (i + DISTANCE_OFFSET), DEFAULT_DIST);
	}
	leftOrRight = oi->getGamePrefs();
	turnAngle = leftOrRight * robotDrive->autoTurnAngle;
	state = -1;
	IncrementState();
}

void DriveInside::Execute() {
	switch (state) {
	case Startup:
		if (cubeMover->Pickup()) // returns true when finished
			IncrementState();
		break;
	case DriveForwardOne:
		if (robotDrive->encoderDistance() < dist[0]) {
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
		if (cubeMover->Drop())
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
