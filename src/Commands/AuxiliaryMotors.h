#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "../CommandBase.h"

class AuxiliaryMotors: public CommandBase {
public:
	AuxiliaryMotors();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif
