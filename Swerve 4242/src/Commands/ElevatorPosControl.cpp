#include "ElevatorPosControl.h"
#include "Robot.h"
#include "Subsystems/Elevator.h"

ElevatorPosControl::ElevatorPosControl() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator);
	int ElevatorPosNum = 1;

}

// Called just before this Command runs the first time
void ElevatorPosControl::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorPosControl::Execute() {
	if (ElevatorPosNum() == 1)
	{
		Robot::elevator->ElevatorPos1();
		ElevatorPosNum = 2;
	}
	else if (ElevatorPosNum() == 2)
	{
		Robot::elevator->ElevatorPos2();
		ElevatorPosNum = 3;
	}
	else if (ElevatorPosNum() == 3)
	{
		Robot::elevator->ElevatorPos3();
		ElevatorPosNum = 4;
	}
	else if (ElevatorPosNum() == 4)
	{
		Robot::elevator->ElevatorPos4();
		ElevatorPosNum = 1;
	}
	else
	{
		ElevatorPosNum = 1;
	}

}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorPosControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ElevatorPosControl::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorPosControl::Interrupted() {

}
