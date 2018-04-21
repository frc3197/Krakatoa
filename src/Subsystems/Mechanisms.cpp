#include "Mechanisms.h"

#include "../Commands/AuxiliaryMotors.h"

#include "../RobotMap.h"
#include <math.h>

#include "WPILib.h"

#include "ctre/Phoenix.h"

#define MAXRPM 534
#define LARGE_AMOUNT_OF_CURRENT 50
#define PEAK_CLAW_CURRENT 5

Mechanisms::Mechanisms() :
		Subsystem("AuxiliaryMotors") {

	winchA = new WPI_TalonSRX(5);
	winchB = new WPI_TalonSRX(6);
	claw = new WPI_TalonSRX(7);
	elevatorWinch = new WPI_TalonSRX(8);
	elevatorClawA = new WPI_TalonSRX(9);
	elevatorClawB = new WPI_TalonSRX(10);

	elevatorClawB->Follow(*elevatorClawA);
	elevatorClawB->SetInverted(true);

	winchB->Follow(*winchA);

}

void Mechanisms::InitDefaultCommand() {
	SetDefaultCommand(new AuxiliaryMotors());

	maxObservedClawCurrent = 0;
}

void Mechanisms::Winch(float speed) {
	winchA->Set(speed);
	SmartDashboard::PutNumber("Winch Current", winchA->GetOutputCurrent());
}

void Mechanisms::Claw(float speed) {
	claw->Set(speed);
	SmartDashboard::PutNumber("Claw Current", claw->GetOutputCurrent());
}

void Mechanisms::ElevatorWinch(float speed) {
	elevatorWinch->Set(speed);
//	SmartDashboard::PutNumber("Elevator Winch Encoder",
//			elevatorWinch->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Winch Current",
			elevatorWinch->GetOutputCurrent());
}

void Mechanisms::ElevatorClaw(float speed) {
	elevatorClawA->Set(speed);
	float currentA = elevatorClawA->GetOutputCurrent();
	float currentB = elevatorClawB->GetOutputCurrent();
	if (currentA > maxObservedClawCurrent)
		maxObservedClawCurrent = currentA;
	if(currentB > maxObservedClawCurrent)
		maxObservedClawCurrent =currentB;
	SmartDashboard::PutNumber("Max ElevatorClaw Current", maxObservedClawCurrent);
	SmartDashboard::PutNumber("ElevatorClawA Current", currentA);
	SmartDashboard::PutNumber("ElevatorClawB Current", currentB);


}

bool Mechanisms::ClawRetractLim() {
	bool trip = 0 != claw->GetSensorCollection().IsFwdLimitSwitchClosed();
//	SmartDashboard::PutBoolean("Claw Forward Limit (retract)", trip);
	return trip;

}

bool Mechanisms::ClawGrabLim() {
	bool trip = 0 != claw->GetSensorCollection().IsRevLimitSwitchClosed();
//	SmartDashboard::PutBoolean("Claw Reverse Limit (grab)", trip);
	return trip;
}

bool Mechanisms::ElevatorClawBotLim() {
	bool trip = 0
			!= elevatorClawA->GetSensorCollection().IsRevLimitSwitchClosed();
//	SmartDashboard::PutBoolean("Elevator Claw Forward Limit (bot)", trip);
	return trip;
}

bool Mechanisms::ElevatorClawTopLim() {
	bool trip = 0
			!= elevatorClawA->GetSensorCollection().IsFwdLimitSwitchClosed();
//	SmartDashboard::PutBoolean("Elevator Claw Reverse Limit (top)", trip);
	return trip;
}

bool Mechanisms::ElevatorWinchForwardLimit() {
	bool trip = 0
			!= elevatorWinch->GetSensorCollection().IsFwdLimitSwitchClosed();
//	SmartDashboard::PutBoolean("Elevator Winch Forward Limit (bot)", trip);
	return trip;
}

bool Mechanisms::ElevatorWinchReverseLimit() {
	bool trip = 0
			!= elevatorWinch->GetSensorCollection().IsRevLimitSwitchClosed();
//	SmartDashboard::PutBoolean("Elevator Winch Reverse Limit (top)", trip);
	return trip;
}

void Mechanisms::UpdateCurrent() {
	float clawCurrent = claw->GetOutputCurrent();
	SmartDashboard::PutNumber("Claw Current", clawCurrent);
	float winchCurrentA = winchA->GetOutputCurrent();
	SmartDashboard::PutNumber("Winch A Current", winchCurrentA);
	float winchCurrentB = winchB->GetOutputCurrent();
	SmartDashboard::PutNumber("Winch B Current", winchCurrentB);
	float eleClawCurrent = elevatorClawA->GetOutputCurrent();
	SmartDashboard::PutNumber("Ele Claw Current", eleClawCurrent);
	float eleWinchCurrent = elevatorWinch->GetOutputCurrent();
	SmartDashboard::PutNumber("Ele Winch Current", eleWinchCurrent);

}
