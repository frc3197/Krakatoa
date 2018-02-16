#ifndef DRIVE_OUTSIDE_OPP_H
#define DRIVE_OUTSIDE_OPP_H

<<<<<<< HEAD
//#include <Commands/AutoCommands/AutoCalls.h>
=======
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897
#include "../../CommandBase.h"
#include "WPILib.h"

class DriveOutsideOpp: public CommandBase {
private:
	Timer timer;
	int state;
	bool finished;
	bool done;
	float turnAngle;
	int leftOrRight;

	float dist[4];

<<<<<<< HEAD
//	Claw* claw = new Claw();

=======
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897
	enum states {
		Startup, DriveForwardOne, //Dist 5
		TurnOne,
		DriveForwardTwo, //Dist 6
		TurnTwo,
		DriveForwardThree, //Dist 7
		TurnThree,
		DriveForwardFour, //Dist 8
		DropCube
	};

	void IncrementState();
	void Drive(float speed);
public:
	DriveOutsideOpp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
