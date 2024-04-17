// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Wiper.h"

int main()
{

    wiper w;
    sensor s;
    s.set_rain_range(8);
    
    w.setSwitchState(SwitchButtonState::Automatic);
    w.set_speed_state(SwitchButtonState::Automatic);
    w.set_state_if_automatic(s.get_rain_range());
    std::cout << w.getWiperSpeed();
}



