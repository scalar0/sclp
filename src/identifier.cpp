// identifier.cpp
#include "identifier.h"
#include <string>

#include "parsing_utils.h"

#include "nlohmann/json_fwd.hpp"

bool Identifier::parse(const std::string& s)
{
	if (s.empty())
	{
		clear(); // Reset the identifier if the input is empty
		return true;
	}

	// Check for '@' prefix
	if (std::string str = s; str[0] == '@')
	{
		if (const size_t hash_pos = str.find('#'); hash_pos != std::string::npos)
		{
			setName(str.substr(1, hash_pos - 1));
			setId(str.substr(hash_pos + 1));
		}
		else
		{
			setName(str.substr(1));
		}
	}
	else
	{
		const size_t brace_open_pos = str.find('{');
		const size_t brace_close_pos = str.find('}');
		size_t colon_pos = std::string::npos;

		// Check if we have an ID enclosed in braces
		if (brace_open_pos != std::string::npos && brace_close_pos != std::string::npos && brace_close_pos >
			brace_open_pos)
		{
			setName(str.substr(0, brace_open_pos));
			setId(str.substr(brace_open_pos + 1, brace_close_pos - brace_open_pos - 1));

			// Check for instance after colon
			colon_pos = str.find(':', brace_close_pos + 1);
			setInstance(colon_pos != std::string::npos ? str.substr(colon_pos + 1) : "");
		}
		else
		{
			// Handle case where there is no brace but there might be an instance (colon notation)
			colon_pos = str.find(':');
			if (colon_pos != std::string::npos)
			{
				setName(str.substr(0, colon_pos));
				setInstance(str.substr(colon_pos + 1));
				setId("");
			}
			else
			{
				// Name only case
				setName(str);
				clearIdAndInstance(); // Reset the id and instance
			}
		}
	}

	// Trim the name at the end
	parsing_utils::trim(name_);
	return true;
}

void Identifier::clearIdAndInstance()
{
	guid_.clear();
	instance_.clear();
}


void Identifier::clear()
{
	name_.clear();
	clearIdAndInstance();
}

nlohmann::json Identifier::to_json() const
{
	return nlohmann::json{
		{"name", name_},
		{"id", guid_},
		{"instance", instance_}
	};
}
