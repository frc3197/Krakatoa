#include "TankControl.h"

TankControl::TankControl() {
	Requires(robotDrive);
}

void TankControl::Initialize() {
	robotDrive->gyroReset();
}

void TankControl::Execute() {
	float left = oi->getDriveLeft();
	float right = oi->getDriveRight();
	oi->updateSensors();
	robotDrive->driveBot(left, right);
	bool resetGyro = oi->gyroReorientate();
	if (resetGyro){
		robotDrive->gyroReset();
	}
}

bool TankControl::IsFinished() {
	return false;
}

void TankControl::End() {

}

void TankControl::Interrupted() {

}
