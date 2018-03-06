#ifndef DRIVE_STRAIGHT_DIST_H
#define DRIVE_STRAIGHT_DIST_H

#include "../../CommandBase.h"
#include "WPILib.h"

class DriveStraightDist: public CommandBase
{
private:
	Timer timer;
	int state;
	bool finished;

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
