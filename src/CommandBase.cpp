#include "CommandBase.h"

#include <Commands/Scheduler.h>

Preferences *CommandBase::prefs = NULL;

std::unique_ptr<OI> CommandBase::oi;
RobotDriveWithJoystick* CommandBase::robotDrive = NULL;
Mechanisms* CommandBase::auxMotors = NULL;

CommandBase::CommandBase(const std::string &name) :
		frc::Command(name) {
}

void CommandBase::init() {
	prefs = Preferences::GetInstance();

	CommandBase::oi = std::make_unique<OI>();
	oi.reset(new OI());
	robotDrive = new RobotDriveWithJoystick();
	auxMotors = new Mechanisms();
}
