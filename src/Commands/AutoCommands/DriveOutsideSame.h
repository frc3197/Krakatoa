#ifndef DRIVE_OUTSIDE_SAME_H
#define DRIVE_OUTSIDE_SAME_H

<<<<<<< HEAD
#include <Commands/AutoCommands/Claw.h>
#include "../../CommandBase.h"
#include "WPILib.h"


=======
#include "../../CommandBase.h"
#include "WPILib.h"

>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
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
	Claw* claw = new Claw();

	enum states {
		Startup,
		DriveForwardOne, //Dist 3
=======
	enum states {
		Startup, DriveForwardOne, //Dist 3
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
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
