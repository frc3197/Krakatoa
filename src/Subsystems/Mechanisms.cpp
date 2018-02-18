#include "Mechanisms.h"

#include "../Commands/AuxiliaryMotors.h"

#include "../RobotMap.h"
#include <math.h>

#include "WPILib.h"

#include "ctre/Phoenix.h"

#define MAXRPM 534
#define LARGE_AMOUNT_OF_CURRENT 50
#define SQUISH_SPEED .1
#define PEAK_CLAW_CURRENT 5

Mechanisms::Mechanisms() :
		Subsystem("AuxiliaryMotors") {

	winchA = new WPI_TalonSRX(5);
	winchB = new WPI_TalonSRX(6);
	claw = new WPI_TalonSRX(7);
	elevatorWinch = new WPI_TalonSRX(8);
	elevatorClaw = new WPI_TalonSRX(9);

	winchB->Follow(*winchA);

	claw->ConfigPeakCurrentLimit(PEAK_CLAW_CURRENT,
			CommandBase::robotDrive->kTimeoutMs);
	claw->ConfigPeakCurrentDuration(200, 0);
	claw->EnableCurrentLimit(true);

	elevatorClaw->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,
				CommandBase::robotDrive->kTimeoutMs);
	claw->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,
				CommandBase::robotDrive->kTimeoutMs);
//	claw->ConfigForwardLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_RemoteTalonSRX,
//			LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 5);
//	claw->ConfigReverseLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_RemoteTalonSRX,
//			LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 5);
}

void Mechanisms::InitDefaultCommand() {
	SetDefaultCommand(new AuxiliaryMotors());
//	elevatorWinch->Config_kF(CommandBase::robotDrive->kPIDLoopIdx,	//ID (0), data, timeout
//			CommandBase::robotDrive->prefs->GetFloat("ElevatorClaw F",
//					CommandBase::robotDrive->defaultF),
//			CommandBase::robotDrive->kTimeoutMs);
//
//	elevatorWinch->Config_kP(CommandBase::robotDrive->kPIDLoopIdx,	//ID (0), data, timeout
//			CommandBase::robotDrive->prefs->GetFloat("ElevatorClaw P",
//					CommandBase::robotDrive->defaultP),
//			CommandBase::robotDrive->kTimeoutMs);
//
//	elevatorWinch->Config_kI(CommandBase::robotDrive->kPIDLoopIdx,	//ID (0), data, timeout
//			CommandBase::robotDrive->prefs->GetFloat("ElevatorClaw I",
//					CommandBase::robotDrive->defaultI),
//			CommandBase::robotDrive->kTimeoutMs);
//
//	elevatorWinch->Config_kD(CommandBase::robotDrive->kPIDLoopIdx,	//ID (0), data, timeout
//			CommandBase::robotDrive->prefs->GetFloat("ElevatorClaw D",
//					CommandBase::robotDrive->defaultD),
//			CommandBase::robotDrive->kTimeoutMs);
}

void Mechanisms::Winch(float speed) {
	winchA->Set(speed);
	SmartDashboard::PutNumber("Winch speed",speed);
}

void Mechanisms::Claw(float speed) {
	float clawCurrent = claw->GetOutputCurrent();

	claw->Set(speed);
	SmartDashboard::PutNumber("Claw Current", claw->GetOutputCurrent());
	SmartDashboard::PutNumber("Claw Position",
			claw->GetSensorCollection().GetQuadraturePosition());

}

//NAMING CONVENTION REFORM
void Mechanisms::ClimbVertical(float speed) {
	//elevatorWinch->Set(ControlMode::Velocity, (speed * MAXRPM * 4096 * 600 );
	elevatorWinch->Set(speed);
//	SmartDashboard::PutNumber("Elevator winch speed",speed);
	SmartDashboard::PutNumber("Winch Current", elevatorWinch->GetOutputCurrent());
}

void Mechanisms::ElevatorClaw(float speed) {
	elevatorClaw->Set(speed);
	SmartDashboard::PutNumber("Elevator Claw Current",
			elevatorClaw->GetOutputCurrent());
//	SmartDashboard::PutNumber("Elevator claw speed",speed);
	SmartDashboard::PutNumber("Elevator Claw Position",
			elevatorClaw->GetSensorCollection().GetQuadraturePosition());
}

bool Mechanisms::ClawForwardLimit() {
	int raw = elevatorClaw->GetSensorCollection().IsFwdLimitSwitchClosed();
	SmartDashboard::PutBoolean("Lower Limit", (bool) raw);
	if (raw == 0)
		return false;
	return true;
}

//FAKE ERRORS REEEEEEEEEE
bool Mechanisms::ClawReverseLimit() {
	int raw = elevatorClaw->GetSensorCollection().IsRevLimitSwitchClosed();
	SmartDashboard::PutBoolean("Reverse Limit", (bool) raw);
	if (raw == 0)
		return false;
	return true;
}

float Mechanisms::ClawCurrent() {
	return claw->GetOutputCurrent();
}
