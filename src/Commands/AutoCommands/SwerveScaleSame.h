#ifndef SWERVE_SCALE_SAME_H
#define SWERVE_SCALE_SAME_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "AutoCalls.h"

class SwerveScaleSame: public CommandBase {
private:
	Timer timer;
	int state;
	bool finished;

	float eleTime;
	float driveOverTime;
	float backupTime;

	float straightDistance;

	float eleSpeedUp;
	float eleSpeedDown;

	float baseSpeed;
	float backupSpeed;
	float extraSpeed;
	float extraExtraSpeed;

	float swerveAngle;
	float scaleAngle;

	enum states {
		Straight,
		SwerveIn,
		SwerveOut,
		RaiseFully,
		DriveOverScale,
		Drop,
		Backup,
		Turn
	};

	AutoCalls* claw = new AutoCalls();
	void IncrementState();

public:
	SwerveScaleSame();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void Drive(float l, float r);
};

#endif
