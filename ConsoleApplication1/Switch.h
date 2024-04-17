#pragma once
#include "DataTypes.h"
class SwitchButton {

public:

	SwitchButtonState GetState() {
		return this->state;
	}

	void SetState(SwitchButtonState newState)
	{
		this->state = newState;
	}

private:
	SwitchButtonState state;
};
