#ifndef DRIVE_STRAIGHT_H
#define DRIVE_STRAIGHT_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "AutoCalls.h"

class DriveStraight: public CommandBase
{
private:
	Timer timer;
	int state;
	bool finished;

	AutoCalls* claw = new AutoCalls();
public:
	DriveStraight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void Drive(float speed);
};

#endif
