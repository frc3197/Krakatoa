#ifndef ROBOT_DRIVE_JOYSTICK_H
#define ROBOT_DRIVE_JOYSTICK_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
<<<<<<< HEAD
#include "C:\Users\Hexhounds\wpilib\user\cpp\include\ctre\phoenix\MotorControl\CAN\WPI_TalonSRX.h"
=======
#include "ctre\phoenix\MotorControl\CAN\WPI_TalonSRX.h"
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
#include "ctre/Phoenix.h"

class RobotDriveWithJoystick: public frc::Subsystem {
public:
	RobotDriveWithJoystick();
	void InitDefaultCommand() override;
	void driveBot(float left, float right);
	void advancedDriveBot(float left, float right, float preferred);
	bool advancedTurnBot(float speed, float preferred);
	float gyroAngle();
	void gyroReset();
	float encoderDistance();
	void encoderReset();

<<<<<<< HEAD
	Preferences *prefs;

=======
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
	float autoDriveSpeed;
	float autoTurnSpeed;
	float autoTurnAngle;

	const int kTimeoutMs = 0;
	const int kPIDLoopIdx = 0;

	const float defaultF = 0.1097;
	const float defaultP = 0.22;
	const float defaultI = 0.0;
	const float defaultD = 0.0;
private:
	WPI_TalonSRX *frontRight;
	WPI_TalonSRX *rearRight;
	WPI_TalonSRX *frontLeft;
	WPI_TalonSRX *rearLeft;

	frc::DifferentialDrive *rDrive;
	ADXRS450_Gyro SPIGyro;


	float resetVal = 0;
	float talonF;
	float talonP;
	float talonI;
	float talonD;

};

#endif
