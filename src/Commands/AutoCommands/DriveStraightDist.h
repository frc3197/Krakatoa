#ifndef DRIVE_STRAIGHT_DIST_H
#define DRIVE_STRAIGHT_DIST_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "AutoCalls.h"

class DriveStraightDist: public CommandBase
{
private:
	Timer timer;
	int state;
	bool finished;

	AutoCalls* claw = new AutoCalls();

public:
	DriveStraightDist();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void Drive(float speed);
};

#endif
