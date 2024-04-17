#include "pch.h"

// Unit Tests

// Unit Test rain sensor 

float generateRandomValue() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(-2.0, 14.0);
    return dist(gen);
}

bool isSensorValueInRange(float value) {
    return (value >= 0.0 && value <= 12.0);
}

class SensorTest : public ::testing::TestWithParam<float> {
};

TEST_P(SensorTest, ValueInRange) {
    float sensorValue = GetParam();
    sensor test;
    test.set_rain_range(sensorValue);
    EXPECT_TRUE(isSensorValueInRange(test.get_rain_range()));
}

std::vector<float> generateRandomValues(int count) {
    std::vector<float> values;
    values.reserve(count);
    for (int i = 0; i < count; ++i) {
        values.push_back(generateRandomValue());
    }
    return values;
}

INSTANTIATE_TEST_CASE_P(Values, SensorTest, ::testing::ValuesIn(generateRandomValues(20)));

// Test fixture pentru testul de integrare
class IntegrationTest : public ::testing::Test {
protected:
    SwitchButton switchButton;
    sensor rainSensor;
    wiper wiperSystem;

public:
    IntegrationTest() : switchButton(), rainSensor(), wiperSystem(switchButton, rainSensor) {}

    void SetUp() override {
        // Inițializează comutatorul și senzorul
        switchButton.SetState(SwitchButtonState::Automatic);
    }

    void TearDown() override {
        // Eliberează resursele, dacă este necesar
    }
};

TEST_F(IntegrationTest, AutomaticModeIntegrationTest) {
    // Generare valori aleatorii pentru senzorul de ploaie între [-2, 14]
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-2.0, 14.0);
    float rainValue = dist(gen);

    std::cout << "Generated rain value: " << rainValue << std::endl;

    // Setare valoare generată în senzorul de ploaie
    rainSensor.set_rain_range(rainValue);

    // Setare starea comutatorului pe "automatic" și determinarea vitezei wiper-ului
    wiperSystem.setSwitchState(SwitchButtonState::Automatic);
    wiperSystem.set_speed_state(SwitchButtonState::Automatic);
    wiperSystem.set_state_if_automatic(rainSensor.get_rain_range());
    // Verificare dacă comportamentul corespunde cerinței software 2.4a-c
    if (rainSensor.get_rain_range() >= 0.0 && rainSensor.get_rain_range() < 2.0)
        EXPECT_EQ(wiperSystem.getWiperSpeed(), WiperSpeed::Off_speed); // Cerința 2.4a
    else if (rainSensor.get_rain_range() >= 2 && rainSensor.get_rain_range() <= 4.99)
        EXPECT_EQ(wiperSystem.getWiperSpeed(), WiperSpeed::Low_speed); // Cerința 2.4b
    else if (rainSensor.get_rain_range() >= 5 && rainSensor.get_rain_range() <= 12)
        EXPECT_EQ(wiperSystem.getWiperSpeed(), WiperSpeed::High_speed); // Cerința 2.4c
    else
        FAIL() << "Sensor speed not ok";
}