#include "ResetPigeonYaw.h"
#include "Robot.h"
<<<<<<< HEAD
ResetPigeonYaw::ResetPigeonYaw() {
	Requires(Robot::pigeon);
=======
ResetPigeonYaw::ResetPigeonYaw(double offset) {
    // Requires(Robot::pigeon);
    this->offset = offset;
>>>>>>> 2049c4a3761c73539323a05bf768cbdc00da8cff
}

// Called just before this Command runs the first time
void ResetPigeonYaw::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ResetPigeonYaw::Execute() {
    Robot::pigeon->ResetYaw(offset);
}

// Make this return true when this Command no longer needs to run execute()
bool ResetPigeonYaw::IsFinished() {
    return true;
}

// Called once after isFinished returns true
void ResetPigeonYaw::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetPigeonYaw::Interrupted() {
}
