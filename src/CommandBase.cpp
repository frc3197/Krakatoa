#include "CommandBase.h"

#include <Commands/Scheduler.h>

std::unique_ptr<OI> CommandBase::oi = std::make_unique<OI>();
RobotDriveWithJoystick* CommandBase::robotDrive = NULL;
Mechanisms* CommandBase::auxMotors = NULL;
//CubeManipulation* CommandBase::cubeManip = NULL;

CommandBase::CommandBase(const std::string &name) :
		frc::Command(name) {
}

void CommandBase::init() {
	oi.reset(new OI());
	robotDrive = new RobotDriveWithJoystick();
	auxMotors = new Mechanisms();
//	cubeManip = new CubeManipulation();
}
