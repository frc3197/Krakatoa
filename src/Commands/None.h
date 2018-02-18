#ifndef NONE_H
#define NONE_H

#include "../CommandBase.h"

class None: public CommandBase {
public:
	None();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif
