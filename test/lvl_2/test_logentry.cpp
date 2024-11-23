#include <gtest/gtest.h>
#include "logentry.h"
#include "nlohmann/json.hpp"

// Test case for the default constructor
TEST(LogEntryTest, DefaultConstructor)
{
	const LogEntry log_entry;
	EXPECT_EQ(log_entry.getSource(), Entity());
	EXPECT_EQ(log_entry.getTarget(), Entity());
	EXPECT_EQ(log_entry.getAbility(), Effect());
	EXPECT_EQ(log_entry.getAction(), Action());
	EXPECT_EQ(log_entry.getQuants(), Quant());
	EXPECT_EQ(log_entry.getThreat(), "");
	EXPECT_EQ(log_entry.getTimestamp(), "");
}

// Test case for parsing an invalid log entry
TEST(LogEntryTest, ParseInvalidLogEntry)
{
	LogEntry log_entry;
	const std::string input = "InvalidLogEntry";
	EXPECT_FALSE(log_entry.parse(input));
}

// Test case for parsing an empty log entry
TEST(LogEntryTest, ParseEmptyLogEntry)
{
	LogEntry log_entry;
	EXPECT_FALSE(log_entry.parse(""));
}

// Test case for parsing a valid log entry

// Test case for parsing a log entry with target as "="

// Test case for converting to JSON
TEST(LogEntryTest, ToJson)
{
	LogEntry log_entry;
	log_entry.parse("2023-10-01T12:34:56Z SourceEntity TargetEntity Ability Action Quant Threat");
	const nlohmann::json expected_json = {
		{"source", log_entry.getSource().to_json()},
		{"target", log_entry.getTarget().to_json()},
		{"ability", log_entry.getAbility().to_json()},
		{"action", log_entry.getAction().to_json()},
		{"quant", log_entry.getQuants().to_json()},
		{"threat", "Threat"},
		{"timestamp", "2023-10-01T12:34:56Z"}
	};
	EXPECT_EQ(log_entry.to_json(), expected_json);
}
