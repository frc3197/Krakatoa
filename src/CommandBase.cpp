#include "CommandBase.h"

#include <Commands/Scheduler.h>

std::unique_ptr<OI> CommandBase::oi = std::make_unique<OI>();
RobotDriveWithJoystick* CommandBase::robotDrive = NULL;
Mechanisms* CommandBase::auxMotors = NULL;
<<<<<<< HEAD
=======
//CubeManipulator* CommandBase::cube = NULL;
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5

Preferences* CommandBase::prefs = NULL;
CommandBase::CommandBase(const std::string &name) :
		frc::Command(name) {
}

void CommandBase::init() {
	oi.reset(new OI());
	robotDrive = new RobotDriveWithJoystick();
	auxMotors = new Mechanisms();
<<<<<<< HEAD
=======
//	cube = new CubeManipulator();
	prefs = Preferences::GetInstance();
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
}
