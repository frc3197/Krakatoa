#ifndef NOTHING_H
#define NOTHING_H

#include "../../CommandBase.h"
#include "WPILib.h"

class Nothing: public CommandBase
{
public:
	Nothing();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
