#ifndef CUBE_MANIPULATOR_U
#define CUBE_MANIPULATOR_U

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h"
#include "ctre/Phoenix.h"

class CubeManipulator: public frc::Subsystem {
public:
	CubeManipulator();
	void InitDefaultCommand() override;
};

#endif
