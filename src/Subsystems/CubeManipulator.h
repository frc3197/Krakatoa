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
	bool Pickup();
	bool Drop();
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
};

#endif
