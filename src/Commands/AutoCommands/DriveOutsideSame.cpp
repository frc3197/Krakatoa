#include <Commands/AutoCommands/DriveOutsideSame.h>

#define DEFAULT_DIST 0
#define DISTANCE_OFFSET 3

DriveOutsideSame::DriveOutsideSame() {
	Requires(robotDrive);
	Requires(cubeMover);
	Initialize();
}

void DriveOutsideSame::Initialize() {
	for (int i = 0; i < 2; i++) {
		dist[i] =  CommandBase::prefs->GetFloat(
				"distance" + (i + DISTANCE_OFFSET), DEFAULT_DIST);
	}
	leftOrRight = oi->getGamePrefs();
	turnAngle = -leftOrRight * robotDrive->autoTurnAngle;
	state = -1;
	IncrementState();
}

void DriveOutsideSame::Execute() {
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
	case DropCube: //drop cube
		if (cubeMover->Drop())
			IncrementState();
		break;
	default:
		End();
	}
}

bool DriveOutsideSame::IsFinished() {
	return finished;
}

void DriveOutsideSame::End() {
	Drive(0);
	finished = true;
	timer.Stop();
}

void DriveOutsideSame::Interrupted() {

}

void DriveOutsideSame::IncrementState() {
	state++;
	timer.Reset();
	timer.Start();
	robotDrive->gyroReset();
	robotDrive->encoderReset();
}

void DriveOutsideSame::Drive(float speed) {
	robotDrive->advancedDriveBot(speed, speed, 0);
}
