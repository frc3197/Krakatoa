#ifndef SWERVE_SCALE_OPP_H
#define SWERVE_SCALE_OPP_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "AutoCalls.h"

class SwerveScale: public CommandBase
{
private:
	Timer timer;
	int state;
	bool finished;

	float eleTime;

	float driveOverDistance;
	float backupDistance;

	float eleSpeedUp;
	float eleSpeedDown;

	float baseSpeed;
	float backupSpeed;
	float extraSpeed;

	float straightDistance;
	float straightAcrossDistance;

	float swerveAngle;

	enum states {
		StraightToScale,
		SwerveIn,
		StraightAcross,
		SwerveTowardScale,
		RaiseFully,
		DriveOverScale,
		Drop,
		Backup,
		Lower
	};

	AutoCalls* claw = new AutoCalls();
	void IncrementState();

public:
	SwerveScale();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void Drive(float l, float r);
};

#endif
