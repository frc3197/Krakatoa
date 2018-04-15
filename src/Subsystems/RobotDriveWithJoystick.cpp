#include "RobotDriveWithJoystick.h"

#include "../Commands/TankControl.h"

#include "../RobotMap.h"
#include <math.h>

#include "WPILib.h"

#include "ctre/Phoenix.h"

#define SPEED_MULTIPLIER 1
#define ANGLE_DEADZONE 1
#define TURN_ANGLE_DEADZONE 2
#define PERCENT_CHANGE_PER_DEGREE .0075
#define MIN_SPEED .55
#define ENCODER_CONVERSION (M_PI * 6.00 / 84)/4

#define AUTO_SPEED .5
#define AUTO_TURN_SPEED .55

#define DIST_DEADZONE 10

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

//	frontRight->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
//	frontRight->SetSensorPhase(false); // polarity of the rotation
//
//	frontLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
//	frontLeft->SetSensorPhase(false); // polarity of the rotation

	talonF = defaultF;
	talonP = defaultP;
	talonI = defaultI;
	talonD = defaultD;

	autoDriveSpeed = 0;
	autoTurnSpeed = 0;
	autoTurnAngle = 0;
	autoDriveDist = 0;
	autoDriveTime = 0;
}

void RobotDriveWithJoystick::InitDefaultCommand() {
	SetDefaultCommand(new TankControl());
//	SPIGyro.Calibrate();

	autoDriveSpeed = CommandBase::prefs->GetFloat("autoDriveSpeed", 0);
	autoTurnSpeed = CommandBase::prefs->GetFloat("autoTurnSpeed", 0);
	autoTurnAngle = CommandBase::prefs->GetFloat("autoTurnAngle", 0);
	autoDriveDist = CommandBase::prefs->GetFloat("autoDriveDist", 0);
	autoDriveTime = CommandBase::prefs->GetFloat("autoDriveTime", 0);

	encoderReset();

	talonF = CommandBase::prefs->GetFloat("Drive F", defaultF);
	talonP = CommandBase::prefs->GetFloat("Drive P", defaultP);
	talonI = CommandBase::prefs->GetFloat("Drive I", defaultI);
	talonD = CommandBase::prefs->GetFloat("Drive D", defaultD);

//	frontRight->Config_kF(kPIDLoopIdx, talonF, kTimeoutMs);
//	frontRight->Config_kP(kPIDLoopIdx, talonP, kTimeoutMs);
//	frontRight->Config_kI(kPIDLoopIdx, talonI, kTimeoutMs);
//	frontRight->Config_kD(kPIDLoopIdx, talonD, kTimeoutMs);
//	frontRight->Set(ControlMode::PercentOutput, 0);

//	frontLeft->Config_kF(kPIDLoopIdx, talonF, kTimeoutMs);
//	frontLeft->Config_kP(kPIDLoopIdx, talonP, kTimeoutMs);
//	frontLeft->Config_kI(kPIDLoopIdx, talonI, kTimeoutMs);
//	frontLeft->Config_kD(kPIDLoopIdx, talonD, kTimeoutMs);
//	frontLeft->Set(ControlMode::PercentOutput, 0);

}

void RobotDriveWithJoystick::driveBot(float left, float right) {
	rDrive->TankDrive(left * SPEED_MULTIPLIER, right * SPEED_MULTIPLIER, false);
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
		if (abs(speed) < MIN_SPEED) {
			speed = MIN_SPEED;

		}
//		if (deltaAngle < 0) {
//			speed *= -1;
//		}
	} else {
		speed = 0;
	}
	driveBot(speed, -speed);
	return !turn;
}

bool RobotDriveWithJoystick::gotoDistance(float distance, float speed,
		float preferred) {
	float current = encoderDistance();
	float deltaDistance = distance - current;
	SmartDashboard::PutNumber("deltaDistance", deltaDistance);
	SmartDashboard::PutNumber("distance", distance);
	SmartDashboard::PutNumber("current", current);
	if (deltaDistance > DIST_DEADZONE || deltaDistance < -DIST_DEADZONE) {;
		if (deltaDistance < 0)
			speed *= -1;
		advancedDriveBot(speed, speed, preferred);
		return false;
	}
	return true;
}

float RobotDriveWithJoystick::gyroAngle() {
	float raw = SPIGyro.GetAngle();

	while (raw < -180) {
		raw += 360;
	}
	while (raw > 180) {
		raw -= 360;
	}
	SmartDashboard::PutData("Gyro", &SPIGyro);
	return raw;
}

void RobotDriveWithJoystick::gyroReset() {
	SPIGyro.Reset();
}

float RobotDriveWithJoystick::encoderDistance() {
	float cm = (lidar->GetPeriod() * 100000) - 18;
	float in = cm / 2.54;
	SmartDashboard::PutNumber("in", in);
	return in;
}
void RobotDriveWithJoystick::encoderReset() {
	lidarDist = encoderDistance();
}
