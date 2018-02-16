//#ifndef CUBE_MANIPULATION_H
//#define CUBE_MANIPULATION_H
//
//#include <Commands/Subsystem.h>
//#include "WPILib.h"
//#include "ctre/Phoenix.h"
//#include "../Commands/AuxiliaryMotors.h"
//#include "../RobotMap.h"
//#include <math.h>
//
//class CubeManipulation: public frc::Subsystem {
//public:
//	CubeManipulation();
//	void InitDefaultCommand() override;
//	bool Pickup();
//	bool Drop();
//	void IncrementPickupState();
//	void IncrementDropState();
//
//private:
//	Timer timer;
//	int pickupState;
//	int dropState;
//
//	float maxCurrent;
//
//	enum pickupStates {
//		RaiseAndFall, LowerPickup, Close, RaiseWithCube
//	};
//
//	enum dropStates {
//		Open, LowerDrop
//	};
//
//};
//
//#endif
