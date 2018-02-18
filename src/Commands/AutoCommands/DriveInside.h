#ifndef DRIVE_INSIDE_H
#define DRIVE_INSIDE_H

<<<<<<< HEAD
#include <Commands/AutoCommands/Claw.h>
#include "../../CommandBase.h"
#include "WPILib.h"


=======

#include "CommandBase.h"
#include "WPILib.h"

>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
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
	Claw* claw = new Claw();

=======
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
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
