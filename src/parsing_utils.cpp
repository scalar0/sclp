#include "parsing_utils.h"

#include <string>

namespace parsing_utils
{
	void trim(std::string s)
	{
		const auto whitespace = " \t\n\r\f\v";
		s.erase(0, s.find_first_not_of(whitespace)); // Leading whitespace
		s.erase(s.find_last_not_of(whitespace) + 1); // Trailing whitespace
	}

	std::string trim_copy(const std::string& s)
	{
		std::string copy = s;
		trim(copy); // Trim the copy in place
		return copy;
	}
}
