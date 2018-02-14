#ifndef TESTER_H
#define TESTER_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h"
#include "ctre/Phoenix.h"

class Tester: public frc::Subsystem {
public:
	Tester();
	void InitDefaultCommand() override;
};

#endif
