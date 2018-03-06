#ifndef AUTO_CLAW_H
#define AUTO_CLAW_H

#include "../../CommandBase.h"
#include "WPILib.h"

class AutoClaw {
private:
	int leftOrRight;

	Timer timerPickup;
	Timer timerDrop;

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
	AutoClaw();
	bool Pickup();
	bool Drop();
	void Reset();
	void ResetTimerPickup();
	void ResetTimerDrop();

};

#endif
