#include "PositionDrive.h"
#include "Robot.h"

#include "Subsystems/PositionPID.h"
#include "Subsystems/PigeonPID.h"

PositionDrive::PositionDrive(double pos, double angle) {
	Requires(Robot::driveTrain);

    posPID = new PositionPID();
    pigeonPID = new PigeonPID();

    posPID->SetSetpoint(pos);
    pigeonPID->SetSetpoint(angle);
}

// Called just before this Command runs the first time
void PositionDrive::Initialize() {
	SetTimeout(10);
}

// Called repeatedly when this Command is scheduled to run
void PositionDrive::Execute() {
                        // (twist            , y, x             , gyro)
	Robot::driveTrain->Crab(pigeonPID->output, 0, posPID->output, true);
}

// Make this return true when this Command no longer needs to run execute()
bool PositionDrive::IsFinished() {

           // check if gyro error is crazy
    return fabs(pigeonPID->PosError()) > 30 ||

           // did I fall over? lol
           Robot::pigeon->AmTilted() ||

           // did I hit something?
           //Robot::pigeon->WasCollision() ||

           // gone on for too long
           IsTimedOut() ||

           // we reached destination!
           posPID->OnTarget();
}

// Called once after isFinished returns true
void PositionDrive::End() {
    Robot::driveTrain->Stop();

    posPID->Disable();
    pigeonPID->Disable();

    delete posPID;
    delete pigeonPID;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionDrive::Interrupted() {
    Robot::driveTrain->Stop();

    posPID->Disable();
    pigeonPID->Disable();

    delete posPID;
    delete pigeonPID;
}