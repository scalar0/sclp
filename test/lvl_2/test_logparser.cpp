#include <gtest/gtest.h>
#include <fstream>
#include "logparser.h"
#include "logentry.h"
#include "nlohmann/json.hpp"

// Helper function to create a temporary file with given content
static void createTempFile(const std::string& file_path, const std::string& content)
{
	std::ofstream file(file_path);
	file << content;
	file.close();
}

// Test case for parsing a valid log file
TEST(LogParserTest, ParseValidLogFile)
{
	const std::string input_file_path = "test_input.log";
	const std::string output_file_path = "test_output.jsonl";
	const std::string log_content = "2023-10-01T12:34:56Z SourceEntity TargetEntity Ability Action Quant Threat\n";
	createTempFile(input_file_path, log_content);

	LogParser log_parser(input_file_path, output_file_path);
	EXPECT_TRUE(log_parser.parse());

	std::ifstream output_file(output_file_path);
	std::string output_content;
	std::getline(output_file, output_content);
	output_file.close();

	nlohmann::json expected_json = {
		{"source", {{"name", "SourceEntity"}, {"id", ""}, {"instance", ""}}},
		{"target", {{"name", "TargetEntity"}, {"id", ""}, {"instance", ""}}},
		{"ability", {{"name", "Ability"}, {"id", ""}, {"instance", ""}}},
		{"action", {{"name", "Action"}, {"id", ""}, {"instance", ""}}},
		{"quant", nlohmann::json{}},
		{"threat", "Threat"},
		{"timestamp", "2023-10-01T12:34:56Z"}
	};
	EXPECT_EQ(nlohmann::json::parse(output_content), expected_json);
}

// Test case for parsing an invalid log file
TEST(LogParserTest, ParseInvalidLogFile)
{
	const std::string input_file_path = "test.log";
	const std::string output_file_path = "test_output.jsonl";
	const std::string log_content = "InvalidLogEntry\n";
	createTempFile(input_file_path, log_content);

	LogParser log_parser(input_file_path, output_file_path);
	EXPECT_TRUE(log_parser.parse());

	std::ifstream output_file(output_file_path);
	std::string output_content;
	EXPECT_FALSE(std::getline(output_file, output_content));
	output_file.close();
}

// Test case for parsing an empty log file
TEST(LogParserTest, ParseEmptyLogFile)
{
	const std::string input_file_path = "test_empty_input.log";
	const std::string output_file_path = "test_output.jsonl";
	createTempFile(input_file_path, "");

	LogParser log_parser(input_file_path, output_file_path);
	EXPECT_TRUE(log_parser.parse());

	std::ifstream output_file(output_file_path);
	std::string output_content;
	EXPECT_FALSE(std::getline(output_file, output_content));
	output_file.close();
}

// Test case for handling file open failure
TEST(LogParserTest, FileOpenFailure)
{
	const std::string input_file_path = "non_existent_input.log";
	const std::string output_file_path = "test_output.jsonl";

	const LogParser log_parser(input_file_path, output_file_path);
	EXPECT_FALSE(log_parser.parse());
}
