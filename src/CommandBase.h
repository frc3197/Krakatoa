#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <memory>
#include <string>

#include <Commands/Command.h>

#include "OI.h"
#include "Subsystems/RobotDriveWithJoystick.h"
#include "Subsystems/Mechanisms.h"
<<<<<<< HEAD
=======

#include "Subsystems/CubeManipulator.h"
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5

class CommandBase: public frc::Command {
public:
	CommandBase(const std::string& name);
	CommandBase() = default;
	static void init();

	static std::unique_ptr<OI> oi;
	static RobotDriveWithJoystick *robotDrive;
	static Mechanisms *auxMotors;
<<<<<<< HEAD
=======
	static CubeManipulator *cube;
	static Preferences *prefs;
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
};

#endif
