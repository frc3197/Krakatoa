#ifndef CLAW_H
#define CLAW_H

#include "../../CommandBase.h"
#include "WPILib.h"

class Claw
{
private:
	int leftOrRight;

	Timer timer;
	int pickupState;
	int dropState;

	float maxCurrent;

	enum pickupStates {
		RaiseAndFall,
		LowerPickup,
		Close,
		RaiseWithCube
	};

	enum dropStates {
		Open,
		LowerDrop
	};


	void IncrementPickupState();
	void IncrementDropState();
public:
	Claw();
	bool Pickup();
	bool Drop();
};

#endif
