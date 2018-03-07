#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include <Commands/AutoCommands/Nothing.h>
#include <Commands/AutoCommands/DriveInside.h>
#include <Commands/AutoCommands/DriveStraight.h>
#include <Commands/AutoCommands/DriveStraightDist.h>
#include <Commands/AutoCommands/DriveOutsideSame.h>
#include <Commands/AutoCommands/DriveOutsideOpp.h>
#include <Commands/AutoCommands/SwerveSwitch.h>
#include <Commands/AutoCommands/SwerveScaleSame.h>
#include <Commands/AutoCommands/SwerveScaleOpp.h>

#include "CommandBase.h"

class Robot: public frc::IterativeRobot {

private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<std::string> positionChooser;

public:
	void RobotInit() {
		CommandBase::init();
		positionChooser.AddDefault("Nothing", "N");
		positionChooser.AddObject("Straight", "S");
		positionChooser.AddObject("Straight Dist", "SD");
		positionChooser.AddObject("Left", "L");
		positionChooser.AddObject("Middle", "M");
		positionChooser.AddObject("Right", "R");
//		positionChooser.AddObject("Swerve Switch", "Switch");
//		positionChooser.AddObject("Swerve Scale Same", "Scale Same");
//		positionChooser.AddObject("Swerve Scale Opposite", "Scale Opposite");

		SmartDashboard::PutData("Position", &positionChooser);

	}

	void DisabledInit() override {

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() override {
		CommandBase::oi->setInTele(false);

		std::string position = positionChooser.GetSelected();
		std::string gameData =
				frc::DriverStation::GetInstance().GetGameSpecificMessage();
		bool sideRight = false;
		if (position.compare("S") == 0) {
			autonomousCommand.reset(new DriveStraight());
		} else if (position.compare("SD") == 0) {
			autonomousCommand.reset(new DriveStraightDist());
		} else if (position.compare("M") == 0) {
			sideRight = gameData.substr(0, 1).compare("R") == 0;
			autonomousCommand.reset(new SwerveSwitch());
		} else if (position.compare("R") == 0 || position.compare("L") == 0) {
			sideRight = gameData.substr(1, 2).compare("R") == 0;
			if (position.compare("R") == 0) {
				autonomousCommand.reset(new SwerveScaleSame());
			} else {
				autonomousCommand.reset(new SwerveScaleOpp());
			}
		} else {
			autonomousCommand.reset(new Nothing());
		}

		if (sideRight) {
			CommandBase::oi->setGamePrefs(1);
		} else {
			CommandBase::oi->setGamePrefs(-1);
		}
		if (autonomousCommand.get() != nullptr) {
			autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		RobotPeriodic();
	}

	void TeleopInit() override {
		CommandBase::oi->setInTele(true);

		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		RobotPeriodic();
	}

	void TestPeriodic() override {
		frc::LiveWindow::GetInstance()->Run();
	}

	void RobotPeriodic() {
		CommandBase::oi->updateSensors();
	}

};

START_ROBOT_CLASS(Robot)
