#include "RobotDriveWithJoystick.h"

#include "../Commands/TankControl.h"

#include "../RobotMap.h"
#include <math.h>

#include "WPILib.h"

#include "ctre/Phoenix.h"

#define SPEED_MULTIPLIER 1
#define ANGLE_DEADZONE 1
#define TURN_ANGLE_DEADZONE 0
#define PERCENT_CHANGE_PER_DEGREE .0075
#define MIN_SPEED .55
#define ENCODER_CONVERSION (M_PI * 6 / 84) / 4

#define AUTO_SPEED .5
#define AUTO_TURN_SPEED .55

RobotDriveWithJoystick::RobotDriveWithJoystick() :
		Subsystem("RobotDriveWithJoystick") {

	frontRight = new WPI_TalonSRX(1);
	rearRight = new WPI_TalonSRX(2);
	frontLeft = new WPI_TalonSRX(3);
	rearLeft = new WPI_TalonSRX(4);

	rDrive = new DifferentialDrive(*frontLeft, *frontRight);

	rearLeft->Follow(*frontLeft);
	rearRight->Follow(*frontRight);

	rDrive->SetSafetyEnabled(false);

	frontRight->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,
			kTimeoutMs);
	frontRight->SetSensorPhase(true); //?

	frontRight->ConfigNominalOutputForward(0, kTimeoutMs);
	frontRight->ConfigNominalOutputReverse(0, kTimeoutMs);
	frontRight->ConfigPeakOutputForward(1, kTimeoutMs);
	frontRight->ConfigPeakOutputReverse(-1, kTimeoutMs);

	frontLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,
			kTimeoutMs);
	frontLeft->SetSensorPhase(true); //?

	frontLeft->ConfigNominalOutputForward(0, kTimeoutMs);
	frontLeft->ConfigNominalOutputReverse(0, kTimeoutMs);
	frontLeft->ConfigPeakOutputForward(1, kTimeoutMs);
	frontLeft->ConfigPeakOutputReverse(-1, kTimeoutMs);

	talonF = defaultF;
	talonP = defaultP;
	talonI = defaultI;
	talonD = defaultD;

	prefs = Preferences::GetInstance();
}

void RobotDriveWithJoystick::InitDefaultCommand() {
	SetDefaultCommand(new TankControl());
	SPIGyro.Calibrate();

	prefs = Preferences::GetInstance();

	autoDriveSpeed = prefs->GetFloat("autoDriveSpeed", 0);
	autoTurnSpeed = prefs->GetFloat("autoTurnSpeed", 0);
	autoTurnAngle = prefs->GetFloat("autoTurnAngle", 0);

	encoderReset();

	talonF = prefs->GetFloat("Drive F", defaultF);
	talonP = prefs->GetFloat("Drive P", defaultP);
	talonI = prefs->GetFloat("Drive I", defaultI);
	talonD = prefs->GetFloat("Drive D", defaultD);

	frontRight->Config_kF(kPIDLoopIdx, talonF, kTimeoutMs);
	frontRight->Config_kP(kPIDLoopIdx, talonP, kTimeoutMs);
	frontRight->Config_kI(kPIDLoopIdx, talonI, kTimeoutMs);
	frontRight->Config_kD(kPIDLoopIdx, talonD, kTimeoutMs);
//	frontRight->Set(ControlMode::PercentOutput, 0);

	frontLeft->Config_kF(kPIDLoopIdx, talonF, kTimeoutMs);
	frontLeft->Config_kP(kPIDLoopIdx, talonP, kTimeoutMs);
	frontLeft->Config_kI(kPIDLoopIdx, talonI, kTimeoutMs);
	frontLeft->Config_kD(kPIDLoopIdx, talonD, kTimeoutMs);
//	frontLeft->Set(ControlMode::PercentOutput, 0);

}

void RobotDriveWithJoystick::driveBot(float left, float right) {
	rDrive->TankDrive(left * SPEED_MULTIPLIER, right * SPEED_MULTIPLIER);
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
		if (deltaAngle < 0) {
			speed *= -1;
		}
	} else {
		speed = 0;
	}
	driveBot(speed, -speed);
	return !turn;
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
	float raw = frontLeft->GetSelectedSensorPosition(kPIDLoopIdx);
	SmartDashboard::PutNumber("Encoder", raw * ENCODER_CONVERSION);
	return raw * ENCODER_CONVERSION;
}
void RobotDriveWithJoystick::encoderReset() {
	frontLeft->SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
}
