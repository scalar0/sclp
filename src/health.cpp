#include "health.h"
#include <stdexcept>

#include "nlohmann/json_fwd.hpp"

bool Health::parse(const std::string& s)
{
	if (s.empty())
	{
		return false;
	}

	const size_t pos = s.find('/');
	if (pos == std::string::npos)
	{
		return false; // No '/' found, invalid format
	}

	try
	{
		setCurrentHp(std::stoi(s.substr(0, pos)));
		setMaxHp(std::stoi(s.substr(pos + 1)));
		return true;
	}
	catch (const std::invalid_argument&)
	{
		clear(); // Reset health values if parsing fails
		return false;
	}
}

void Health::clear()
{
	setCurrentHp(0);
	setMaxHp(0);
}


nlohmann::json Health::to_json() const
{
	return nlohmann::json{
		{"current_hp", getCurrentHp()},
		{"max_hp", getMaxHp()}
	};
}
