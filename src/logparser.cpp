#include "logparser.h"

#include <fstream>
#include <iostream>
#include <string>

#include "logentry.h"

bool LogParser::parse() const
{
	std::ifstream input_file(input_file_path_);
	std::ofstream jsonl_file(output_file_path_);

	if (!input_file.is_open() || !jsonl_file.is_open())
	{
		std::cerr << "Failed to open a file." << '\n';
		return false;
	}

	constexpr size_t buffer_size = 4096;
	char input_buffer[buffer_size];
	char output_buffer[buffer_size];

	input_file.rdbuf()->pubsetbuf(input_buffer, buffer_size);
	jsonl_file.rdbuf()->pubsetbuf(output_buffer, buffer_size);


	std::string line;
	int line_number = 0;

	// Read and parse each line, writing to the file immediately
	while (std::getline(input_file, line))
	{
		++line_number;
		if (line.empty()) continue;  // Skip empty lines

		if (LogEntry entry; entry.parse(line))
		{
			// Write JSON directly to the file
			nlohmann::json j = entry.to_json();
			jsonl_file << j.dump() << '\n';
			jsonl_file.flush();
		}
		else
		{
			std::cerr << "Failed to parse log line " << line_number << ": " << line << '\n';
		}
	}

	input_file.close();
	jsonl_file.close();
	std::cout << "Log entries have been written to output.jsonl." << '\n';

	return true;
}
