#include "action.h"
#include <regex>
#include "parsing_utils.h"

bool Action::parse(const std::string& s)
{
	if (s.empty())
	{
		clear();
		return true;
	}

	if (std::smatch m; std::regex_match(s, m, pattern))
	{
		// Set name and ID from the matches, trimming the name
		setName(parsing_utils::trim_copy(m[1].str()));
		setId(m[2].str());

		// Handle effect if matched
		if (m[3].matched && m[4].matched)
		{
			effect.setName(parsing_utils::trim_copy(m[3].str()));
			effect.setId(m[4].str());
			setEffect(effect);
		}
		else
		{
			effect.clear(); // Clear only the effect
		}
		return true;
	}

	// If no regex match, assume the name-only case
	setName(parsing_utils::trim_copy(s));
	setId("");
	effect.clear();
	return true;
}

void Action::clear()
{
	name_.clear();
	guid_.clear();
	effect.clear();
}

nlohmann::json Action::to_json() const
{
	return nlohmann::json{
		{"name", name_},
		{"id", guid_},
		{"effect", effect.to_json()}
	};
}
