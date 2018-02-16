#ifndef DRIVE_INSIDE_H
#define DRIVE_INSIDE_H

<<<<<<< HEAD
//#include <Commands/AutoCommands/AutoCalls.h>
=======
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897
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

<<<<<<< HEAD
//	AutoCalls* claw = new AutoCalls();

=======
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897
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
