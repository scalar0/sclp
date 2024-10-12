#include "entity.h"
#include <regex>

bool Entity::parse(const std::string& s)
{
	if (s.empty())
	{
		clear(); // Reset the entity to default state
		return true;
	}

	if (std::smatch matches; std::regex_match(s, matches, pattern))
	{
		std::string full_identifier_str = matches[1].str();
		const size_t slash_pos = full_identifier_str.find('/');

		// Split into owner and identifier
		const std::string owner_str = (slash_pos != std::string::npos) ? full_identifier_str.substr(0, slash_pos) : "";
		const std::string identifier_str = (slash_pos != std::string::npos)
			                                   ? full_identifier_str.substr(slash_pos + 1)
			                                   : full_identifier_str;

		// Parse owner, if present
		if (!owner_str.empty())
		{
			if (!owner.parse(owner_str)) return false;
			setOwner(owner);
		}
		else
		{
			owner.clear(); // Reset owner if not present
		}

		// Parse identifier
		if (!identifier.parse(identifier_str)) return false;
		setIdentifier(identifier);

		// Parse vector, if matched
		if (matches[2].matched)
		{
			if (vector.parse(matches[2].str()))
			{
				setVector(vector);
			}
			// Handle vector parsing failure if needed
		}

		// Parse health, if matched
		if (matches[3].matched)
		{
			if (health.parse(matches[3].str()))
			{
				setHealth(health);
			}
			// Handle health parsing failure if needed
		}

		return true;
	}

	return false;
}


void Entity::clear()
{
	identifier.clear();
	owner.clear();
	vector.clear();
	health.clear();
}

nlohmann::json Entity::to_json() const
{
	return nlohmann::json{
		{"owner_name", owner.getName()},
		{"owner_id", owner.getId()},
		{"identifier_name", identifier.getName()},
		{"identifier_id", identifier.getId()},
		{"identifier_instance", identifier.getInstance()},
		{"vector", vector.to_json()},
		{"health", health.to_json()}
	};
}
