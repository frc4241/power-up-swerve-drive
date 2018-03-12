// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/ResetPigeonYaw.h"
#include "Commands/ClawControl.h"
#include "Commands/RampEndUp.h"
#include "Commands/IntakeActuate.h"
#include "Commands/ElevatorPosControl.h"
#include "Commands/IncreasePos.h"
#include "Commands/DeployRamp.h"
#include "Commands/ToggleTwistPID.h"
#include "Commands/ToggleFieldCentric.h"

OI::OI() {
	// Process operator interface input here.
	pi = 3.14159;

	xBoxControl = new Joystick(0);
	xBoxDrive = new Joystick(1);

	//Xbox
	DriveA = new JoystickButton(xBoxDrive, 1);
	DriveB = new JoystickButton(xBoxDrive, 2);
	DriveX = new JoystickButton(xBoxDrive, 3);
	DriveY = new JoystickButton(xBoxDrive, 4);
	DriveLB = new JoystickButton(xBoxDrive, 5);
	DriveRB = new JoystickButton(xBoxDrive, 6);
	DriveBack = new JoystickButton(xBoxDrive, 7);
	DriveStart = new JoystickButton(xBoxDrive, 8);
	//^Xbox^


	ControlA = new JoystickButton(xBoxControl, 1);
	ControlB = new JoystickButton(xBoxControl, 2);
	ControlX = new JoystickButton(xBoxControl, 3);
	ControlY = new JoystickButton(xBoxControl, 4);
	ControlLB = new JoystickButton(xBoxControl, 5);
	ControlRB = new JoystickButton(xBoxControl, 6);
	ControlBack = new JoystickButton(xBoxControl, 7);
	ControlStart = new JoystickButton(xBoxControl, 8);
	//Used For controlling main subsystems excluding drive


	//XboxDrive
	DriveA->WhenPressed(new ResetPigeonYaw);
	DriveY->WhenPressed(new ToggleTwistPID);
	DriveB->ToggleWhenPressed(new ToggleFieldCentric);

	if (xBoxDrive->GetPOV() != -1) {
		Robot::twistPID_Enabled = true;
		Robot::twistPID->SetSetpoint(xBoxDrive->GetPOV());
	}

	//XboxControl
	ControlX->ToggleWhenPressed(new ClawControl);
	ControlStart->ToggleWhenPressed(new RampEndUp);
	ControlBack->ToggleWhenPressed(new DeployRamp);
	ControlY->WhenPressed(new ElevatorPosControl);

}

Joystick* OI::getControlJoystick() {
	return xBoxControl;
}
Joystick* OI::getDriveJoystick() {
	return xBoxDrive;
}

bool OI::getLB() {
	return xBoxDrive->GetRawButton(5);
}

double OI::getJoystickMagnitude() {
	if(xBoxDrive->GetMagnitude() < .1) {
		return 0;
	} else {
		if (xBoxDrive->GetY() < 0) {
			return -xBoxDrive->GetMagnitude();
		} else {
			return xBoxDrive->GetMagnitude();
		}
	}
}

double OI::getJoystickZ() {
	return adjustJoystick(xBoxDrive->GetRawAxis(4));
}

double OI::getJoystickX() {
	return adjustJoystick(xBoxDrive->GetX());
}

double OI::getJoystickY() {
	return adjustJoystick(xBoxDrive->GetY());
}

double OI::getControlJoy() {
	return adjustJoystick(xBoxControl->GetY());
}

double OI::adjustJoystick(double value) {
	// cube output
	double adjV = pow(value, 3);

	// add deadzone
	if (fabs(adjV) < 0.05) {
		return 0;
	} else {
		return adjV;
	}
}
