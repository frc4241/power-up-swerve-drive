// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "Robot.h"
#include <Commands/PIDSubsystem.h>
#include <thread>

using namespace frc;


LIDARLite3* Robot::lidarLiteL = NULL;
LIDARLite3* Robot::lidarLiteR = NULL;
IntakeDetection* Robot::intakeDetection = NULL;
Vision* Robot::vision = NULL;

void Robot::RobotInit() {
	RobotMap::init();

	vision = new Vision();

	intakeDetection = new IntakeDetection();

	lidarLiteL = new LIDARLite3(13);
	lidarLiteR = new LIDARLite3(14);
	//lidarLite->startMeasuring();
	/*std::thread lidarThread([]() {

	});*/

	lw = LiveWindow::GetInstance();

	// instantiate the command used for the autonomous period
	prevTrigger = false;
}

void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {

}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	cycleTime = GetClock();
	incnum = 1;
}

void Robot::TeleopPeriodic() {
	SmartDashboard::PutNumber("CycleTime", GetClock() - cycleTime);
	cycleTime = GetClock();
	//lidarLite->updateDistance();

	Dashboard();
	SmartDashboard::PutString("vision", vision->ReadData()->c_str());

	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

void Robot::Dashboard() {
<<<<<<< HEAD
	SmartDashboard::PutNumber("LidarLite-L", lidarLiteL->Distance());
	SmartDashboard::PutNumber("LidarLite-R", lidarLiteR->Distance());
	SmartDashboard::PutNumber("US", intakeDetection->GetRangeInches());
=======

>>>>>>> eae6e871cff6823ba437c464e4ed2f68dc8dc5f6
}

START_ROBOT_CLASS(Robot);
