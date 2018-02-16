#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <memory>
#include <string>

#include <Commands/Command.h>

#include "OI.h"
#include "Subsystems/RobotDriveWithJoystick.h"
#include "Subsystems/Mechanisms.h"
<<<<<<< HEAD
#include "Subsystems/Mechanisms.h"

=======
#include "Subsystems/CubeManipulator.h"
>>>>>>> 376806810cafbc6ffdabc693fa8e7790d88f7897

class CommandBase: public frc::Command {
public:
	CommandBase(const std::string& name);
	CommandBase() = default;
	static void init();

	static std::unique_ptr<OI> oi;
	static RobotDriveWithJoystick *robotDrive;
	static Mechanisms *auxMotors;
	static CubeManipulator *cube;
	static Preferences *prefs;
};

#endif
