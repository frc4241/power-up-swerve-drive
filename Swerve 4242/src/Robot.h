#pragma once

#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "RobotMap.h"
#include "SmartDashboard/SendableChooser.h"
#include "WPILib.h"
#include <Subsystems/Pigeon.h>

#include "Commands/ElevatorPosControl.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/LIDARLite.h"
#include "Subsystems/MB1013Sensor.h"
#include "Subsystems/PigeonPID.h"
#include "Subsystems/Pneumatics.h"
#include "Subsystems/PressureSensor.h"

using namespace frc;

class Robot : public IterativeRobot {
  public:
    // Command *autonomousCommand;
    static OI* oi;
    static DriveTrain* driveTrain;
    static Pigeon* pigeon;
    static Elevator* elevator;
    static Pneumatics* pneumatics;

    static bool gyroAssist;
    static PigeonPID* gyroAssistPID;

    static bool fieldCentric;
    static bool elevatorPositionControl;
    static bool useUpperLimitSwitch;

    static MB1013Sensor* mb1013Sensor;

    // static PositionPID*
    static LIDARLite* leftLidarLite;
    static LIDARLite* rightLidarLite;

    LiveWindow* lw;
    virtual void RobotInit();
    virtual void AutonomousInit();
    virtual void AutonomousPeriodic();
    virtual void TeleopInit();
    virtual void TeleopPeriodic();
    virtual void TestPeriodic();
    virtual void DisabledInit();
    virtual void DisabledPeriodic();

  private:
    void Dashboard();
    void LEDSet(int led);
    double FLOffset;
    double FROffset;
    double RLOffset;
    double RROffset;
    bool prevTrigger;
    Preferences* Prefs;
    int turnDegree;
    int turnDirection;
    float driveForwardAngle;
    std::unique_ptr<frc::Command> autonomousCommand;
    frc::SendableChooser<frc::Command*> chooser;
    // SendableChooser* LEDChooser;
    float cycleTime;
    int incnum;
    // Command *autonomousCommand;
};