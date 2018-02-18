#ifndef DRIVE_OUTSIDE_OPP_H
#define DRIVE_OUTSIDE_OPP_H

<<<<<<< HEAD
#include <Commands/AutoCommands/Claw.h>
#include "../../CommandBase.h"
#include "WPILib.h"


=======
#include "../../CommandBase.h"
#include "WPILib.h"

>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
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
	Claw* claw = new Claw();

	enum states {
			Startup,
			DriveForwardOne, //Dist 5
			TurnOne,
			DriveForwardTwo, //Dist 6
			TurnTwo,
			DriveForwardThree, //Dist 7
			TurnThree,
			DriveForwardFour, //Dist 8
			DropCube
		};
=======
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
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5

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
