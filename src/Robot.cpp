#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include <Commands/AutoCommands/Nothing.h>
#include <Commands/AutoCommands/DriveStraight.h>
#include <Commands/AutoCommands/DriveInside.h>

#include "CommandBase.h"

class Robot: public frc::IterativeRobot {

private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;
//	frc::AnalogGyro m_gyro { 0 };
//	ADXRS450_Gyro SPIGyro;
public:
	void RobotInit() {
		CommandBase::init();
		chooser.AddDefault("Nothing", new Nothing());
		chooser.AddObject("Drive Straight", new DriveStraight());
		chooser.AddObject("Drive Inside", new DriveInside());
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override {

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() override {
		autonomousCommand.reset(chooser.GetSelected());

		if (autonomousCommand.get() != nullptr) {
			autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override {
//		frc::LiveWindow::GetInstance()->Run();
	}

};

START_ROBOT_CLASS(Robot)
