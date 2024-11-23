#include "quant.h"
#include <regex>
#include "nlohmann/json_fwd.hpp"

bool Quant::parse(const std::string& s)
{
	if (s.empty())
	{
		return true;
	}

	if (std::smatch m; std::regex_match(s, m, pattern))
	{
		// Parse value
		if (m[1].matched && !m[1].str().empty())
		{
			value_ = std::stoi(m[1].str());
		}

		// Parse critical flag
		is_crit_ = m[2].matched && !m[2].str().empty();

		// Parse effective value
		if (m[3].matched && !m[3].str().empty())
		{
			effective_value_ = std::stoi(m[3].str());
		}

		// Parse damage type
		if (m[4].matched && !m[4].str().empty())
		{
			damage_type_ = m[4].str();
			damage_type_guid_ = m[5].str();
		}

		// Parse reflect type
		if (m[6].matched && !m[6].str().empty())
		{
			reflect_type_ = m[6].str();
			reflect_type_guid_ = m[7].str();
		}

		// Parse mitigation details
		if ((m[8].matched && !m[8].str().empty())) //|| (m[9].matched && !m[9].str().empty()))
		{
			is_mitigation_ = true;
			mitigation_type_ = m[8].str();
			mitigation_type_guid_ = m[9].str();
		}

		// Parse absorption details
		if (m[10].matched && !m[10].str().empty())
		{
			absorb_value_ = std::stoi(m[10].str());
			absorb_type_ = m[11].str();
			absorb_type_guid_ = m[12].str();
		}

		return true;
	}

	// If parsing fails, store raw amount as simpleValue
	simple_value_ = s;
	return true;
}

nlohmann::json Quant::to_json() const
{
	return nlohmann::json{
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
