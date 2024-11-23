#include <gtest/gtest.h>
#include "action.h"

// Test case for the default constructor
TEST(ActionTest, DefaultConstructor)
{
	const Action action;
	EXPECT_EQ(action.getName(), "");
	EXPECT_EQ(action.getId(), "");
	EXPECT_EQ(action.getEffect().getName(), "");
	EXPECT_EQ(action.getEffect().getId(), "");
}

// Test case for setting and getting name
TEST(ActionTest, SetName)
{
	Action action;
	action.setName("TestAction");
	EXPECT_EQ(action.getName(), "TestAction");
}

// Test case for setting and getting ID
TEST(ActionTest, SetId)
{
	Action action;
	action.setId("1234");
	EXPECT_EQ(action.getId(), "1234");
}

// Test case for setting and getting effect
TEST(ActionTest, SetEffect)
{
	Action action;
	Effect effect;
	effect.setName("TestEffect");
	effect.setId("5678");
	action.setEffect(effect);
	EXPECT_EQ(action.getEffect().getName(), "TestEffect");
	EXPECT_EQ(action.getEffect().getId(), "5678");
}

// Test case for parsing
TEST(ActionTest, Parse)
{
	Action action;
	const std::string input = "TestAction {1234}: TestEffect {5678}";
	EXPECT_TRUE(action.parse(input));
	EXPECT_EQ(action.getName(), "TestAction");
	EXPECT_EQ(action.getId(), "1234");
	EXPECT_EQ(action.getEffect().getName(), "TestEffect");
	EXPECT_EQ(action.getEffect().getId(), "5678");
}

// Test case for clearing
TEST(ActionTest, Clear)
{
	Action action;
	action.setName("TestAction");
	action.setId("1234");
	Effect effect;
	effect.setName("TestEffect");
	effect.setId("5678");
	action.setEffect(effect);
	action.clear();
	EXPECT_EQ(action.getName(), "");
	EXPECT_EQ(action.getId(), "");
	EXPECT_EQ(action.getEffect().getName(), "");
	EXPECT_EQ(action.getEffect().getId(), "");
}
