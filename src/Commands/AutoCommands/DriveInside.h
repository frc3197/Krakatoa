#ifndef DRIVE_INSIDE_H
#define DRIVE_INSIDE_H

#include "../../CommandBase.h"
#include "WPILib.h"

class DriveInside: public CommandBase
{
private:
	Timer timer;
	int state;
	bool finished;
	bool turnt;
	int completed;
	bool firstRun;
	//CS
public:
	DriveInside();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void Drive(float speed);
	bool Turn(float angle);
};

#endif
