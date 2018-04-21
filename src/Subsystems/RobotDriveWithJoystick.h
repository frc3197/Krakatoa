#ifndef ROBOT_DRIVE_JOYSTICK_H
#define ROBOT_DRIVE_JOYSTICK_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre\phoenix\MotorControl\CAN\WPI_TalonSRX.h"
#include "ctre/Phoenix.h"

class RobotDriveWithJoystick: public frc::Subsystem {
public:
	RobotDriveWithJoystick();
	void InitDefaultCommand() override;
	void driveBot(float left, float right);
	void advancedDriveBot(float left, float right, float preferred);
	bool advancedTurnBot(float speed, float preferred);
	bool gotoDistance(float distance, float speed, float preferred);
	float gyroAngle();
	void gyroReset();
	float lidarDistance();
	void lidarReset();
	void current();

	float autoDriveSpeed;
	float autoTurnSpeed;
	float autoTurnAngle;
	float autoDriveDist;
	float autoDriveTime;

	const int kTimeoutMs = 0;
	const int kPIDLoopIdx = 0;

	float lidarDist = 0;
	Counter* lidar;
private:
	WPI_TalonSRX *frontRight;
	WPI_TalonSRX *rearRight;
	WPI_TalonSRX *frontLeft;
	WPI_TalonSRX *rearLeft;

	frc::DifferentialDrive *rDrive;
	ADXRS450_Gyro SPIGyro;
};

#endif
