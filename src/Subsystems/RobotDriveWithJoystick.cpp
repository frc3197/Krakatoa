#include "RobotDriveWithJoystick.h"

#include "../Commands/TankControl.h"

#include "../RobotMap.h"

#include "WPILib.h"

#include "ctre/Phoenix.h"

#define SPEED_MULTIPLIER 1
#define ANGLE_DEADZONE 2
#define TURN_ANGLE_DEADZONE 4
#define PERCENT_CHANGE_PER_DEGREE .0075

RobotDriveWithJoystick::RobotDriveWithJoystick() :
		Subsystem("RobotDriveWithJoystick") {
	WPI_TalonSRX *frontRight = new WPI_TalonSRX(1);
	WPI_TalonSRX *rearRight = new WPI_TalonSRX(2);
	WPI_TalonSRX *frontLeft = new WPI_TalonSRX(3);
	WPI_TalonSRX *rearLeft = new WPI_TalonSRX(4);

	rDrive = new DifferentialDrive(*frontLeft, *frontRight);
	rearLeft->Follow(*frontLeft);
	rearRight->Follow(*frontRight);
	rDrive->SetSafetyEnabled(false);
//	frontRight->SetInverted(true);
//	rearRight->SetInverted(true);
//	frontLeft->SetInverted(true);
	rearLeft->SetInverted(true);
}

void RobotDriveWithJoystick::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new TankControl());
	SPIGyro.Calibrate();
}

void RobotDriveWithJoystick::driveBot(float left, float right) {
	rDrive->TankDrive(-left * SPEED_MULTIPLIER, -right * SPEED_MULTIPLIER);
}

void RobotDriveWithJoystick::advancedDriveBot(float left, float right,
		float preferred) {
	float actual = gyroAngle();
	SmartDashboard::PutNumber("GyroAngle",actual);
	float deltaAngle = (actual - preferred);
	if (abs(deltaAngle) > ANGLE_DEADZONE) {
		float speedChange = abs(deltaAngle) * PERCENT_CHANGE_PER_DEGREE;
		if (deltaAngle > 0) //right side speed up
			right += speedChange;
		else
			//left side speed up
			left += speedChange;
	}
	driveBot(left, right);
	SmartDashboard::PutNumber("Left", right);
	SmartDashboard::PutNumber("Right", left);
}

bool RobotDriveWithJoystick::advancedTurnBot(float speed, float preferred) {
	float actual = gyroAngle();
	float deltaAngle = (actual - preferred);

	bool turn = abs(deltaAngle) > TURN_ANGLE_DEADZONE;
	if (turn) {
		speed *= deltaAngle * PERCENT_CHANGE_PER_DEGREE;
	} else {
		speed = 0;
	}
	SmartDashboard::PutNumber("speeeed", speed);
	SmartDashboard::PutNumber("deltaAngle", deltaAngle);
	SmartDashboard::PutBoolean("turnbool", turn);
	driveBot(speed, -speed);
	return turn;
}

float RobotDriveWithJoystick::gyroAngle() {
	float raw = SPIGyro.GetAngle();
	while (raw < -180) {
		raw += 360;
	}
	while (raw > 180) {
		raw -= 360;
	}
	SmartDashboard::PutNumber("angle", raw);
	return raw;
}

void RobotDriveWithJoystick::gyroReset() {
	SPIGyro.Reset();
}
