#include "IntakeDetection.h"
#include "../RobotMap.h"
#include "Ultrasonic.h"

using namespace frc;

IntakeDetection::IntakeDetection() : Subsystem("IntakeDetection") {
	DigitalInput* echo = new DigitalInput(6);
	DigitalOutput* trigger = new DigitalOutput(5);
	ultra = new Ultrasonic(trigger, echo);
	ultra->SetAutomaticMode(true);
}

void IntakeDetection::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

double IntakeDetection::GetRangeInches() {
	return ultra->GetRangeInches();
}

bool IntakeDetection::HasCube() {
	return GetRangeInches() < 3.0;
}
