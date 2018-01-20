#include <Commands/AutoCommands/Nothing.h>

Nothing::Nothing()
{
}

// Called just before this Command runs the first time
void Nothing::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void Nothing::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool Nothing::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void Nothing::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Nothing::Interrupted()
{

}
