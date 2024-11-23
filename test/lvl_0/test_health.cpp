#include <gtest/gtest.h>
#include "health.h"
#include "../parsetest.h"
#include "nlohmann/json.hpp"

class HealthParseTest : public ParseTest<Health>
{
};

static void check_health_state(const Health& h, const int chp = 0, const int mhp = 0)
{
	EXPECT_EQ(h.getCurrentHp(), chp);
	EXPECT_EQ(h.getMaxHp(), mhp);
}

TEST(HealthTest, SetAndGet)
{
	Health h;
	h.setCurrentHp(50);
	EXPECT_EQ(h.getCurrentHp(), 50);
	h.setMaxHp(100);
	EXPECT_EQ(h.getMaxHp(), 100);
}

TEST_P(HealthParseTest, Parse)
{
	Health h;
	const std::string input = std::get<0>(GetParam());
	const Health eh = std::get<1>(GetParam());

	if (const size_t pos = input.find('/'); (pos == std::string::npos) || input.empty() || input.
		find_first_not_of("0123456789/") != std::string::npos)
	{
		EXPECT_FALSE(h.parse(input)) << "Parsing invalid input should fail.";
		check_health_state(h);
	}
	else
	{
		EXPECT_TRUE(h.parse(input)) << "Parsing valid input should succeed.";
		check_health_state(h, std::stoi(input.substr(0, pos)), std::stoi(input.substr(pos + 1)));
	}
}

INSTANTIATE_TEST_SUITE_P(
	Health,
	HealthParseTest,
	::testing::Values(
		std::make_tuple("", Health()),
		std::make_tuple("0/0", Health()),
		std::make_tuple("invalid_/health_string", Health()),
		std::make_tuple("50100", Health()),
		std::make_tuple("50/100", Health(50, 100))
	)
);

TEST(HealthTest, Clear)
{
	Health h;
	h.setCurrentHp(50);
	h.setMaxHp(100);
	h.clear();
	EXPECT_EQ(h.getCurrentHp(), 0);
	EXPECT_EQ(h.getMaxHp(), 0);
}

TEST(HealthTest, ToJson)
{
	Health h;
	h.setCurrentHp(50);
	h.setMaxHp(100);
	const nlohmann::json expected_json = {
		{"current_hp", 50},
		{"max_hp", 100}
	};
	EXPECT_EQ(h.to_json(), expected_json);
}
