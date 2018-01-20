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
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	frc::DifferentialDrive *rDrive;
};

#endif //ROBOT_DRIVE_JOYSTICK_H
