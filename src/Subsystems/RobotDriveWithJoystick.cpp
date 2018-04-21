#include "RobotDriveWithJoystick.h"

#include "../Commands/TankControl.h"

#include "../RobotMap.h"
#include <math.h>

#include "WPILib.h"

#include "ctre/Phoenix.h"

#define ANGLE_DEADZONE 1
#define TURN_ANGLE_DEADZONE 2
#define DIST_DEADZONE 2

#define PERCENT_CHANGE_PER_DEGREE .0075

RobotDriveWithJoystick::RobotDriveWithJoystick() :
		Subsystem("RobotDriveWithJoystick") {

	lidar = new Counter(0);

	lidar->SetMaxPeriod(1);
	lidar->SetSemiPeriodMode(true);
	lidar->Reset();

	frontRight = new WPI_TalonSRX(1);
	rearRight = new WPI_TalonSRX(2);
	frontLeft = new WPI_TalonSRX(3);
	rearLeft = new WPI_TalonSRX(4);

	rDrive = new DifferentialDrive(*frontLeft, *frontRight);

	frontLeft->SetInverted(true);
	frontRight->SetInverted(true);
	rearLeft->SetInverted(true);
	rearRight->SetInverted(true);

	rearLeft->Follow(*frontLeft);
	rearRight->Follow(*frontRight);

	rDrive->SetSafetyEnabled(false);

	autoDriveSpeed = 0;
	autoTurnSpeed = 0;
	autoTurnAngle = 0;
	autoDriveDist = 0;
	autoDriveTime = 0;
}

void RobotDriveWithJoystick::InitDefaultCommand() {
	SetDefaultCommand(new TankControl());

	autoDriveSpeed = CommandBase::prefs->GetFloat("autoDriveSpeed", 0);
	autoTurnSpeed = CommandBase::prefs->GetFloat("autoTurnSpeed", 0);
	autoTurnAngle = CommandBase::prefs->GetFloat("autoTurnAngle", 0);
	autoDriveDist = CommandBase::prefs->GetFloat("autoDriveDist", 0);
	autoDriveTime = CommandBase::prefs->GetFloat("autoDriveTime", 0);
}

void RobotDriveWithJoystick::driveBot(float left, float right) {
	rDrive->TankDrive(left, right, false);
	SmartDashboard::PutData("Drive", rDrive);
}

void RobotDriveWithJoystick::advancedDriveBot(float left, float right,
		float preferred) {
	float actual = gyroAngle();
	float deltaAngle = (preferred - actual);
	if (abs(deltaAngle) > ANGLE_DEADZONE) {
		float speedChange = deltaAngle * PERCENT_CHANGE_PER_DEGREE;
		right -= speedChange;
		left += speedChange;
	}

	driveBot(left, right);
}

bool RobotDriveWithJoystick::advancedTurnBot(float speed, float preferred) {
	float actual = gyroAngle();
	float deltaAngle = (preferred - actual);
	bool turn = abs(deltaAngle) > TURN_ANGLE_DEADZONE;
	if (turn) {
		if (deltaAngle < 0) {
			speed *= -1;
		}
	} else {
		speed = 0;
	}
	driveBot(speed, -speed);
	return !turn;
}

bool RobotDriveWithJoystick::gotoDistance(float distance, float speed,
		float preferred) {
	float current = lidarDistance();
	float deltaDistance = distance - current;
	if (deltaDistance > DIST_DEADZONE || deltaDistance < -DIST_DEADZONE) {
		;
		if (deltaDistance < 0)
			speed *= -1;
		advancedDriveBot(speed, speed, preferred);
		return false;
	}
	speed = 0;
	advancedDriveBot(speed, speed, preferred);
	return true;
}

float RobotDriveWithJoystick::gyroAngle() {
	float raw = SPIGyro.GetAngle();

//	while (raw < -180) {
//		raw += 360;
//	}
//	while (raw > 180) {
//		raw -= 360;
//	}
	SmartDashboard::PutNumber("Gyro", raw);
	SmartDashboard::PutData("Gyro", &SPIGyro);
	return raw;
}

void RobotDriveWithJoystick::gyroReset() {
	SPIGyro.Reset();
}

float RobotDriveWithJoystick::lidarDistance() {
	float cm = (lidar->GetPeriod() * 100000) - 18;
	float in = cm / 2.54;
	SmartDashboard::PutNumber("Lidar", in);
	return in;
}

void RobotDriveWithJoystick::lidarReset() {
//	lidarDist = 0.0;
}

void RobotDriveWithJoystick::current(){
//	SmartDashboard::PutNumber("Front Right Current", frontRight->GetOutputCurrent());
//	SmartDashboard::PutNumber("Front Left Current", frontLeft->GetOutputCurrent());
//	SmartDashboard::PutNumber("Rear Right Current", rearRight->GetOutputCurrent());
//	SmartDashboard::PutNumber("Rear Left Current", rearLeft->GetOutputCurrent());
}
