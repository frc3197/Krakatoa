#ifndef ROBOT_DRIVE_JOYSTICK_H
#define ROBOT_DRIVE_JOYSTICK_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "C:\Users\Hexhounds\wpilib\user\cpp\include\ctre\phoenix\MotorControl\CAN\WPI_TalonSRX.h"

class RobotDriveWithJoystick: public frc::Subsystem {
public:
	RobotDriveWithJoystick();
	void InitDefaultCommand() override;
	void driveBot(float left, float right);
	void advancedDriveBot(float left, float right, float preferred);
	bool advancedTurnBot(float speed, float preferred);
	float gyroAngle();
	void gyroReset();
private:
	frc::DifferentialDrive *rDrive;
	ADXRS450_Gyro SPIGyro;
};

#endif
