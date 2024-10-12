#include "quant.h"
#include <regex>

#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

bool Quant::parse(const std::string& s)
{
	if (s.empty())
	{
		return true;
	}

	if (std::smatch matches; std::regex_match(s, matches, pattern))
	{
		// Parse value
		if (matches[1].matched && !matches[1].str().empty())
		{
			value_ = std::stoi(matches[1].str());
		}

		// Parse critical flag
		is_crit_ = matches[2].matched && !matches[2].str().empty();

		// Parse effective value
		if (matches[3].matched && !matches[3].str().empty())
		{
			effective_value_ = std::stoi(matches[3].str());
		}

		// Parse damage type
		if (matches[4].matched && !matches[4].str().empty())
		{
			damage_type_ = matches[4].str();
			damage_type_guid_ = matches[5].str();
		}

		// Parse reflect type
		if (matches[6].matched && !matches[6].str().empty())
		{
			reflect_type_ = matches[6].str();
			reflect_type_guid_ = matches[7].str();
		}

		// Parse mitigation details
		if ((matches[8].matched && !matches[8].str().empty()) || (matches[9].matched && !matches[9].str().empty()))
		{
			is_mitigation_ = true;
			mitigation_type_ = matches[8].str();
			mitigation_type_guid_ = matches[9].str();
		}

		// Parse absorption details
		if (matches[10].matched && !matches[10].str().empty())
		{
			absorb_value_ = std::stoi(matches[10].str());
			absorb_type_ = matches[11].str();
			absorb_type_guid_ = matches[12].str();
		}

		return true;
	}

	// If parsing fails, store raw amount as simpleValue
	simple_value_ = s;
	return true;
}

json Quant::to_json() const
{
	return json{
		{"value", value_},
		{"is_crit", is_crit_},
		{"effective", effective_value_},
		{"damage_type", damage_type_},
		{"damage_type_guid", damage_type_guid_},
		{"reflect_type", reflect_type_},
		{"reflect_type_guid", reflect_type_guid_},
		{"is_mitigation", is_mitigation_},
		{"mitigation_type", mitigation_type_},
		{"mitigation_type_guid", mitigation_type_guid_},
		{"absorb_value", absorb_value_},
		{"absorb_type", absorb_type_},
		{"absorb_type_guid", absorb_type_guid_},
		{"simple_value", simple_value_}
	};
}
