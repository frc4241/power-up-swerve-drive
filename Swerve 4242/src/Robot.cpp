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
#include "Autonomous/MidAuto.h"
#include "Autonomous/LeftAuto.h"
#include "Autonomous/RightAuto.h"
#include <Commands/PIDSubsystem.h>

using namespace frc;

OI* Robot::oi = NULL;

DriveTrain* Robot::driveTrain = NULL;
Pigeon* Robot::pigeon = NULL;
Elevator* Robot::elevator = NULL;
Pneumatics* Robot::pneumatics = NULL;
IntakeDetection* Robot::intakeDetection = NULL;
ElevatorPosControl* Robot::elevatorPosControl = NULL;
CycleElevator* Robot::cycleElevator = NULL;

double Robot::twistPID_Value = 0.0;
bool Robot::twistPID_Enabled = false;
PigeonPID* Robot::twistPID = NULL;

PressureSensor* Robot::pressureSensor = NULL;
MB1013Sensor* Robot::mb1013Sensor = NULL;

void Robot::RobotInit() {
	RobotMap::init();

	oi = new OI();

	elevator = new Elevator();
	pneumatics = new Pneumatics();

	intakeDetection = new IntakeDetection();
	driveTrain = new DriveTrain();
	pigeon = new Pigeon();

	twistPID = new PigeonPID();
	twistPID->SetSetpoint(0);

	chooser.AddDefault("Auto", new MidAuto());
	chooser.AddObject("LeftAuto",new LeftAuto());
	chooser.AddObject("RightAuto",new RightAuto());
	CameraServer::GetInstance()->StartAutomaticCapture();
	//CameraServer::GetInstance()->SetQuality(30);
	//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
    // Create an image

	lw = LiveWindow::GetInstance();

	// instantiate the command used for the autonomous period
	prevTrigger = false;

	driveTrain->SetWheelbase(24, 22, 24);
	FLOffset = 0;
	FROffset = 0;
	RLOffset = 0;
	RROffset = 0;

	//Read XXVolt from SmartDashboard with wheels aligned.  Subtract 2.5 from each value and put in function below.
	//FL, FR, RL, RR
	driveTrain->SetOffsets(FLOffset, FROffset, RLOffset, RROffset);

	driveTrain->frontLeft->Enable();
	driveTrain->frontRight->Enable();
	driveTrain->rearLeft->Enable();
	driveTrain->rearRight->Enable();

	pneumatics->Start();

	frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {

}

void Robot::AutonomousInit() {
	autonomousCommand.reset(chooser.GetSelected());
	if (autonomousCommand.get() != NULL) {
		autonomousCommand->Start();
	}
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

	if (oi->getDriverJoystickRight()->GetRawButton(4)) {
		twistPID_Enabled = !twistPID_Enabled;
	}

	if (oi->getDriverJoystickRight()->GetRawButton(7)) {
		twistPID->SetSetpoint(0);
	}

	if (oi->getDriverJoystickRight()->GetRawButton(8)) {
		twistPID->SetSetpoint(90);
	}

	if (twistPID_Enabled) {
		Robot::twistPID->Enable();
		driveTrain->Crab(twistPID_Value, -oi->getJoystickY(), oi->getJoystickX(), true);
	} else {
		Robot::twistPID->Disable();
		driveTrain->Crab(oi->getJoystickZ(), -oi->getJoystickY(), oi->getJoystickX(), false);
	}

	Dashboard();

	//elevator->PositionUpdate();
	elevator->MoveElevator();

	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

void Robot::Dashboard() {
	//Joystick Variables

	SmartDashboard::PutNumber("RightStickY", oi->getDriverJoystickRight()->GetY());
	SmartDashboard::PutNumber("RightStickX", oi->getDriverJoystickRight()->GetX());
	SmartDashboard::PutNumber("RightStickZ", oi->getDriverJoystickRight()->GetZ());

	//Wheel Module Voltages
	SmartDashboard::PutNumber("FrontLeftVol",  driveTrain->frontLeftPos->GetAverageVoltage());
	SmartDashboard::PutNumber("FrontRightVol", driveTrain->frontRightPos->GetAverageVoltage());
	SmartDashboard::PutNumber("RearLeftVol",   driveTrain->rearLeftPos->GetAverageVoltage());
	SmartDashboard::PutNumber("RearRightVol",  driveTrain->rearRightPos->GetAverageVoltage());
	//Wheel Module Errors
	SmartDashboard::PutNumber("FLError", driveTrain->frontLeft->GetError());
	SmartDashboard::PutNumber("FRError", driveTrain->frontRight->GetError());
	SmartDashboard::PutNumber("RLError", driveTrain->rearLeft->GetError());
	SmartDashboard::PutNumber("RRError", driveTrain->rearRight->GetError());
	//Wheel Module Setpoints
	SmartDashboard::PutNumber("FLSetPoint", driveTrain->frontLeft->GetSetpoint());
	SmartDashboard::PutNumber("FRSetPoint", driveTrain->frontRight->GetSetpoint());
	SmartDashboard::PutNumber("RLSetPoint", driveTrain->rearLeft->GetSetpoint());
	SmartDashboard::PutNumber("RRSetPoint", driveTrain->rearRight->GetSetpoint());

	SmartDashboard::PutNumber("DriveGyro", pigeon->GetYaw());

	SmartDashboard::PutNumber("IntakeDetection-Range",    intakeDetection->GetRangeInches());

	SmartDashboard::PutBoolean("LimitSwitch", RobotMap::elevatorUpperLimitSwitch->Get());

	SmartDashboard::PutNumber("PigeonPID-Pos", twistPID->GetPosition());
	SmartDashboard::PutBoolean("PigeonPID-OnTarget", twistPID->OnTarget());
	SmartDashboard::PutNumber("PigeonPID-Twist", twistPID_Value);
	SmartDashboard::PutNumber("PigeonPID-Error", twistPID->PosError());
	//SmartDashboard::PutNumber("PigeonPID-Error", twistPID->GetPIDController()->GetError());


	//SmartDashboard::PutNumber("Elevator-Distance", elevator->GetDistance());
	//SmartDashboard::PutNumber("Elevator-Error", elevator->GetPIDError());

	//SmartDashboard::PutNumber("Elevator-SetPoint", cycleElevator->ElevatorCycleNum);
	//SmartDashboard::PutNumber("Pressure", pressureSensor->Pressure());
	//SmartDashboard::PutNumber("Distance", mb1013Sensor->ReadSensor());
}

START_ROBOT_CLASS(Robot);
