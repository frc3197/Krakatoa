#ifndef DRIVE_OUTSIDE_SAME_H
#define DRIVE_OUTSIDE_SAME_H

#include <Commands/AutoCommands/Claw.h>
#include "CommandBase.h"
#include "WPILib.h"

class DriveOutsideSame: public CommandBase {
private:
	Timer timer;
	int state;
	bool finished;
	bool done;
	float turnAngle;
	int leftOrRight;

	float dist[2];

	Claw* claw = new Claw();

	enum states {
		Startup,
		DriveForwardOne, //Dist 3
		TurnOne,
		DriveForwardTwo, //Dist 4
		DropCube
	};

	void IncrementState();
	void Drive(float speed);
public:
	DriveOutsideSame();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
