#include <gtest/gtest.h>
#include "entity.h"
#include "nlohmann/json.hpp"

// Test case for the default constructor
TEST(EntityTest, DefaultConstructor)
{
	const Entity entity;
	EXPECT_EQ(entity.getOwner().getName(), "");
	EXPECT_EQ(entity.getOwner().getId(), "");
	EXPECT_EQ(entity.getIdentifier().getName(), "");
	EXPECT_EQ(entity.getIdentifier().getId(), "");
	EXPECT_EQ(entity.getIdentifier().getInstance(), "");
	EXPECT_EQ(entity.getVector().to_json(), nlohmann::json{});
	EXPECT_EQ(entity.getHealth().to_json(), nlohmann::json{});
}

// Test case for parsing with owner, identifier, vector, and health
TEST(EntityTest, ParseWithAllFields)
{
	Entity entity;
	const std::string input = "Owner/Identifier {Vector} {Health}";
	EXPECT_TRUE(entity.parse(input));
	EXPECT_EQ(entity.getOwner().getName(), "Owner");
	EXPECT_EQ(entity.getIdentifier().getName(), "Identifier");
	// Add more checks for vector and health if their structure is known
}

// Test case for parsing with identifier only
TEST(EntityTest, ParseWithIdentifierOnly)
{
	Entity entity;
	const std::string input = "Identifier";
	EXPECT_TRUE(entity.parse(input));
	EXPECT_EQ(entity.getOwner().getName(), "");
	EXPECT_EQ(entity.getIdentifier().getName(), "Identifier");
}

// Test case for parsing with empty string
TEST(EntityTest, ParseEmptyString)
{
	Entity entity;
	EXPECT_TRUE(entity.parse(""));
	EXPECT_EQ(entity.getOwner().getName(), "");
	EXPECT_EQ(entity.getIdentifier().getName(), "");
	EXPECT_EQ(entity.getVector().to_json(), nlohmann::json{});
	EXPECT_EQ(entity.getHealth().to_json(), nlohmann::json{});
}

// Test case for clearing
TEST(EntityTest, Clear)
{
	Entity entity;
	entity.parse("Owner/Identifier {Vector} {Health}");
	entity.clear();
	EXPECT_EQ(entity.getOwner().getName(), "");
	EXPECT_EQ(entity.getIdentifier().getName(), "");
	EXPECT_EQ(entity.getVector().to_json(), nlohmann::json{});
	EXPECT_EQ(entity.getHealth().to_json(), nlohmann::json{});
}

// Test case for converting to JSON
TEST(EntityTest, ToJson)
{
	Entity entity;
	entity.parse("Owner/Identifier {Vector} {Health}");
	const nlohmann::json expected_json = {
		{"owner_name", "Owner"},
		{"owner_id", ""},
		{"identifier_name", "Identifier"},
		{"identifier_id", ""},
		{"identifier_instance", ""},
		{"vector", nlohmann::json{}}, // Adjust based on actual vector structure
		{"health", nlohmann::json{}} // Adjust based on actual health structure
	};
	EXPECT_EQ(entity.to_json(), expected_json);
}
