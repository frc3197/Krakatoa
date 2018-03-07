#ifndef DRIVE_INSIDE_H
#define DRIVE_INSIDE_H

#include <Commands/AutoCommands/AutoCalls.h>
#include "../../CommandBase.h"
#include "WPILib.h"


class DriveInside: public CommandBase {
private:
	Timer timer;
	int state;
	bool finished;
	bool done;
	float turnAngle;
	int leftOrRight;

	float dist[3];

	AutoCalls* claw = new AutoCalls();

	enum states {
		Startup, DriveForwardOne, //Dist 0
		TurnOne,
		DriveForwardTwo, //Dist 1
		TurnTwo,
		DriveForwardThree, //Dist 2
		DropCube
	};

	void IncrementState();
	void Drive(float speed);
public:
	DriveInside();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
