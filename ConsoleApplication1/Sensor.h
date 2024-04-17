#pragma once
#include <iostream>

class sensor {
private:

	//reading of sensor values
	float rain_range;
public:
	//default constructor
	sensor() {
		this->rain_range = 0;
	}
	//constructor with params
	sensor(float rain) {
		this->rain_range = rain;
	}
	//getter
	float get_rain_range() {
		return this->rain_range;
	}
	//setter
	void set_rain_range(float rain) {
		this->rain_range = rain;
	}
	//sensor "reading" values 
	void read_weather(){
		float rain_range;
		std::cin >> rain_range;
		if (rain_range >= 0 && rain_range <= 12)
			set_rain_range(rain_range);
		else std::cout << "out of range";
	}

};