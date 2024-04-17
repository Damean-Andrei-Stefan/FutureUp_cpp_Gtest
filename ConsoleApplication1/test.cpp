#include "pch.h"

// Unit Tests

// #1UB.SwV1.0 Unit Test Button SwC / 25.03.2024 / 1.0 / Future Up

TEST(ButtonUnitTest, GivenValue_ExpectedSameValue) {

	Button bt{};

	bt.SetState({ ButtonState::Off });
	EXPECT_EQ(bt.GetState(), ButtonState::Off);

	bt.SetState({ ButtonState::LowBeam });
	EXPECT_EQ(bt.GetState(), ButtonState::LowBeam);

	bt.SetState({ ButtonState::HighBeam });
	EXPECT_EQ(bt.GetState(), ButtonState::HighBeam);

	bt.SetState({ ButtonState::Automatic });
	EXPECT_EQ(bt.GetState(), ButtonState::Automatic);
}