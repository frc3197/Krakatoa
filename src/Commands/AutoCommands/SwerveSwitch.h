#ifndef SWERVE_SWITCH_H
#define SWERVE_SWITCH_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "AutoCalls.h"

class SwerveSwitch: public CommandBase
{
private:
	Timer timer;
	int state;
	bool finished;

	float baseSpeed;
	float extraSpeed;
	float extraExtraSpeed;
	float intoSwitchSpeed;
	float swerveAngle;

	enum states {
		SwerveAway,
		SwerveIn,
		IntoSwitch,
		Drop
	};

	AutoCalls* claw = new AutoCalls();
	void IncrementState();

public:
	SwerveSwitch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void Drive(float l, float r);
};

#endif
