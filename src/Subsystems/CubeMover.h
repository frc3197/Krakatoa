#ifndef CUBE_MOVER_JOYSTICK_H
#define CUBE_MOVER_JOYSTICK_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "CommandBase.h"
#include "ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h"
#include "ctre/Phoenix.h"

class CubeMover: public frc::Subsystem {
private:
	Timer timer;
	int pickupState;
	int dropState;

	float maxCurrent;

	enum pickupStates {
		RaiseAndFall, LowerPickup, Close, RaiseWithCube
	};

	enum dropStates {
		Open, LowerDrop
	};
	void IncrementPickupState();
	void IncrementDropState();
public:
	CubeMover();
	void InitDefaultCommand() override;
	bool Pickup();
	bool Drop();
};

#endif
