#include "CommandBase.h"

#include <Commands/Scheduler.h>

// Initialize a single static instance of all of your subsystems. The following
// line should be repeated for each subsystem in the project.


std::unique_ptr<OI> CommandBase::oi = std::make_unique<OI>();
RobotDriveWithJoystick* CommandBase::robotDrive = NULL;

CommandBase::CommandBase(const std::string &name) :
	frc::Command(name) {
}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
//	examplesubsystem.reset(new ExampleSubsystem());
	oi.reset(new OI());
	robotDrive = new RobotDriveWithJoystick();
}
