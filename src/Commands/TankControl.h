#ifndef TANK_CONTROL_H
#define TANK_CONTROL_H

#include "../CommandBase.h"

class TankControl: public CommandBase {
public:
	TankControl();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif // TANK_CONTROL_H
