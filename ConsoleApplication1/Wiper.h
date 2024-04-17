#pragma once
#include "Data_types.h"
#include "Sensor.h"
#include <algorithm>
#include "Switch.h"
class wiper{
	//switch button, State for speed, sensor as part of wiper system
private: 
	 SwitchButton Button;
	 sensor Sensor;
	 WiperSpeed wiperSpeed;

public:
	//constructor
	wiper(SwitchButton sb, sensor s) {
		this->Button = sb;
		this->Sensor = s;
		this->wiperSpeed = WiperSpeed::Off_speed;
	}

	wiper() {
		this->Button.SetState(SwitchButtonState::Off);
		this->Sensor.set_rain_range(0);
		this->wiperSpeed = WiperSpeed::Off_speed;
	}

	

	//method to determine speed if switch set to automatic
	void set_state_if_automatic(float RainScore) {
		if (RainScore >= 0 && RainScore <= 1.99)
			setWhiperSpeed(WiperSpeed::Off_speed);
		else if (RainScore >= 2 && RainScore <= 4.99)
			setWhiperSpeed(WiperSpeed::Low_speed);
		else if (RainScore >= 5 && RainScore <= 12)
			setWhiperSpeed(WiperSpeed::High_speed);
	}

	//method to set switch state, normally we would read from button input
	void setSwitchState(SwitchButtonState stateToBeSet)
	{
		this->Button.SetState(stateToBeSet);
	}

	//method to set speed based on switch state
	void set_speed_state(SwitchButtonState ButtonState) {
		if (ButtonState == SwitchButtonState::Off) setWhiperSpeed(WiperSpeed::Off_speed);
		else if (ButtonState == SwitchButtonState::Low) setWhiperSpeed(WiperSpeed::Low_speed);
		else if (ButtonState == SwitchButtonState::High) setWhiperSpeed(WiperSpeed::High_speed);
		else if (ButtonState == SwitchButtonState::Automatic) set_state_if_automatic(this->Sensor.get_rain_range());

	}

	//method to "send" speed to motors, because we have no actual motors we just print it 
	void send_to_motors() {
		std::cout << " sent to motors";
	}

	WiperSpeed getWiperSpeed() {
		return this->wiperSpeed;
	}

	void setWhiperSpeed(WiperSpeed newSpeed)
	{
		this->wiperSpeed = newSpeed;
	}

};