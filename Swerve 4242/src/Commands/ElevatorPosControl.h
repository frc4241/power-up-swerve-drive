#ifndef ElevatorPosControl_H
#define ElevatorPosControl_H

#include "Commands/Command.h"
#include "WPILib.h"

class ElevatorPosControl : public Command {
public:
	ElevatorPosControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevatorPosControl_H
