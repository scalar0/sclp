#include "logentry.h"
#include <regex>

bool LogEntry::parse(const std::string& l)
{
	std::smatch m;
	if (!std::regex_match(l, m, pattern))
	{
		return false;
	}

	// Set timestamp
	setTimestamp(m[1].str());

	// Parse source entity, early return if it fails
	if (!source.parse(m[2].str()))
	{
		return false;
	}

	// If target is "=", copy source to target, else parse target entity
	setTarget((m[3].str() == "=") ? getSource() : (target.parse(m[3].str()) ? target : Entity{}));

	// Parse ability (effect), early return if it fails
	if (!ability.parse(m[4].str()))
	{
		return false;
	}

	// Parse action, early return if it fails
	if (!action.parse(m[5].str()))
	{
		return false;
	}

	// Parse quant values, pass empty string if there's no quant group
	if (!quants.parse(m.size() > 6 ? m[6].str() : ""))
	{
		return false;
	}

	// Set threat if present
	setThreat(m.size() > 7 ? m[7].str() : "");

	return true;
}


nlohmann::json LogEntry::to_json() const
{
	return nlohmann::json{
		{"source", source.to_json()},
		{"target", target.to_json()},
		{"ability", ability.to_json()},
		{"action", action.to_json()},
		{"quant", quants.to_json()},
		{"threat", threat},
		{"timestamp", timestamp}
	};
}
