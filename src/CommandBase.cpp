#include "CommandBase.h"

#include <Commands/Scheduler.h>

std::unique_ptr<OI> CommandBase::oi = std::make_unique<OI>();
RobotDriveWithJoystick* CommandBase::robotDrive = NULL;
Mechanisms* CommandBase::auxMotors = NULL;
<<<<<<< HEAD
//CubeManipulation* CommandBase::cubeManip = NULL;
=======
CubeManipulator * CommandBase::cube = NULL;

Preferences* CommandBase::prefs = NULL;
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897

CommandBase::CommandBase(const std::string &name) :
		frc::Command(name) {
}

void CommandBase::init() {
	oi.reset(new OI());
	robotDrive = new RobotDriveWithJoystick();
	auxMotors = new Mechanisms();
<<<<<<< HEAD
//	cubeManip = new CubeManipulation();
=======
	cube = new CubeManipulator();
	prefs = Preferences::GetInstance();
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897
}
