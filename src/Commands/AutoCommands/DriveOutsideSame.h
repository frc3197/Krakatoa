#ifndef DRIVE_OUTSIDE_SAME_H
#define DRIVE_OUTSIDE_SAME_H

<<<<<<< HEAD
//#include <Commands/AutoCommands/AutoCalls.h>
=======
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897
#include "../../CommandBase.h"
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

<<<<<<< HEAD
//	Claw* claw = new Claw();

=======
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897
	enum states {
		Startup, DriveForwardOne, //Dist 3
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
