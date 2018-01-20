#include "RobotDriveWithJoystick.h"

#include "../Commands/TankControl.h"

#include "../RobotMap.h"

#include "WPILib.h"

#include "ctre/Phoenix.h"

#define SPEED_MULTIPLIER 1

RobotDriveWithJoystick::RobotDriveWithJoystick() :
		Subsystem("RobotDriveWithJoystick")
{
	WPI_TalonSRX *frontRight = new WPI_TalonSRX(1);
	WPI_TalonSRX *rearRight = new WPI_TalonSRX(2);
	WPI_TalonSRX *frontLeft = new WPI_TalonSRX(3);
	WPI_TalonSRX *rearLeft = new WPI_TalonSRX(4);

	rDrive = new DifferentialDrive(*frontLeft, *frontRight);
	rearLeft->Follow(*frontLeft);
	rearRight->Follow(*frontRight);
	rDrive->SetSafetyEnabled(false);
	frontRight->SetInverted(true);
	rearRight->SetInverted(true);
	frontLeft->SetInverted(true);
	rearLeft->SetInverted(false);


}


void RobotDriveWithJoystick::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new TankControl());
}

void RobotDriveWithJoystick::driveBot(float left, float right){
	rDrive->TankDrive(left * SPEED_MULTIPLIER, right * SPEED_MULTIPLIER);
}
