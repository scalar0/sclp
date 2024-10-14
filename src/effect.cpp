#include "effect.h"
#include <regex>
#include "parsing_utils.h"
#include "nlohmann/json_fwd.hpp"

bool Effect::parse(const std::string& s)
{
	if (s.empty())
	{
		clear();
		return true;
	}

	if (std::smatch matches; std::regex_match(s, matches, pattern))
	{
		// Set name and id from the regex match, trimming the name
		setName(parsing_utils::trim_copy(matches[1].str()));
		setId(matches[2].str());
		return true;
	}

	// No regex match, assume name only
	setName(parsing_utils::trim_copy(s));
	setId("");
	return true;
}

void Effect::clear()
{
	name_.clear();
	guid_.clear();
}

nlohmann::json Effect::to_json() const
{
	return nlohmann::json{
		{"name", name_},
		{"id", guid_}
	};
}
