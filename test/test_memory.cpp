#include "logparser.h"
#include <filesystem>

int main()
{
	// Define relative paths
	std::filesystem::path log_path = "sample.log";
	std::filesystem::path output_path = "output.jsonl";

	// Convert relative paths to absolute paths
	log_path = absolute(log_path);
	output_path = absolute(output_path);

	if (const LogParser parser(log_path.string(), output_path.string()); !parser.parse())
	{
		return 1;
	}
	return 0;
}
