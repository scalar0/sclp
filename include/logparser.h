#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <string>

class LogParser
{
	std::string input_file_path_;
	std::string output_file_path_;

public:
	LogParser(std::string i, std::string o)
		: input_file_path_(std::move(i)), output_file_path_(std::move(o))
	{
	}

	[[nodiscard]] bool parse() const;
};

#endif // LOGPARSER_H
