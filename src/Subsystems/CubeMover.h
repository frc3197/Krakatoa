#ifndef CUBE_MOVER_JOYSTICK_H
#define CUBE_MOVER_JOYSTICK_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "CommandBase.h"

class CubeMover: public frc::Subsystem {
public:
	CubeMover();
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
