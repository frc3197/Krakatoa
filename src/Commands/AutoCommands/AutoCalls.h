#ifndef AUTO_CALLS_H
#define AUTO_CALLS_H

#include "../../CommandBase.h"
#include "WPILib.h"

class AutoCalls
{
private:
	int leftOrRight;

	Timer timerPickup;
	Timer timerDrop;

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
	AutoCalls();
	bool Pickup(bool goUp);
	bool Drop();
	void Reset();
	void ResetTimerPickup();
	void ResetTimerDrop();

};

#endif
