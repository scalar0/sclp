#include <gtest/gtest.h>
#include "effect.h"
#include "../parsetest.h"
#include "nlohmann/json.hpp"

class EffectParseTest : public ParseTest<Effect>
{
};

static void check_effect_state(const Effect& effect,
								const std::string& name = "",
								const std::string& id = "")
{
	EXPECT_EQ(effect.getName(), name) << "Name mismatch.";
	EXPECT_EQ(effect.getId(), id) << "ID mismatch.";
}


TEST_P(EffectParseTest, Parse)
{
	Effect e;
	const std::string input = std::get<0>(GetParam());
	const Effect ee = std::get<1>(GetParam());
	if (input.empty())
	{
		EXPECT_TRUE(e.parse(input)) << "Parsing empty string should succeed.";
		check_effect_state(e);
	}
	else
	{
		EXPECT_TRUE(e.parse(input)) << "Parsing valid input should succeed.";
		check_effect_state(e, ee.getName(), ee.getId());
	}
}

INSTANTIATE_TEST_SUITE_P(Effect, EffectParseTest,
						testing::Values(
							std::make_tuple("", Effect{}),
							std::make_tuple("TestEffect {5678}", Effect{ "TestEffect", "5678" })
						)
);

TEST(EffectTest, SetAndGet)
{
	Effect e;
	e.setName("TestEffect");
	EXPECT_EQ(e.getName(), "TestEffect");
	e.setId("5678");
	EXPECT_EQ(e.getId(), "5678");
}

TEST(EffectTest, Clear)
{
	Effect e;
	e.setName("TestEffect");
	e.setId("5678");
	e.clear();
	EXPECT_EQ(e.getName(), "");
	EXPECT_EQ(e.getId(), "");
}

TEST(EffectTest, ToJson)
{
	Effect e;
	e.setName("TestEffect");
	e.setId("5678");
	const nlohmann::json expected_json = {
		{"name", "TestEffect"},
		{"id", "5678"}
	};
	EXPECT_EQ(e.to_json(), expected_json);
}
