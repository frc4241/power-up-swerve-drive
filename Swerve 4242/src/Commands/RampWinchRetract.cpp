#include "RampWinchRetract.h"
#include "Robot.h"
RampWinchRetract::RampWinchRetract() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RampWinchRetract::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RampWinchRetract::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RampWinchRetract::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RampWinchRetract::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RampWinchRetract::Interrupted() {

}