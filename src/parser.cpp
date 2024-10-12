#include <algorithm>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <regex>
#include <string>
#include <vector>
#include "logentry.h"

int main()
{
	// Open the test file containing the log lines
	std::ifstream input_file(R"(C:\Users\main\source\repos\sclp\test.log)");
	std::ofstream jsonl_file(R"(C:\Users\main\source\repos\sclp\output.jsonl)");

	if (!input_file.is_open() || !jsonl_file.is_open())
	{
		std::cerr << "Failed to open a file." << '\n';
		return 1;
	}

	std::vector<LogEntry> entries;
	std::string l;
	LogEntry entry;
	int line_number = 0;

	// Read each line from the file and parse it
	while (std::getline(input_file, l))
	{
		++line_number;
		// Skip empty lines
		if (l.empty())
		{
			continue;
		}

		if (entry.parse(l))
		{
			entries.push_back(std::move(entry));
		}
		else
		{
			std::cerr << "Failed to parse log line " << line_number << ": " << l << '\n';
		}
	}

	input_file.close();


	// Convert each LogEntry to JSON and write to the file
	for (const auto& entry : entries)
	{
		// Construct a JSON object for each log entry
		nlohmann::json j = entry.to_json();

		// Write the JSON object as a single line to the file
		jsonl_file << j.dump() << '\n';
	}

	jsonl_file.close();
	std::cout << "Log entries have been written to output.jsonl." << '\n';

	return 0;
}
