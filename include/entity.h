#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <regex>

#include "health.h"
#include "identifier.h"
#include "vector.h"
#include <string>

class Entity
{
	friend bool operator==(const Entity& lhs, const Entity& rhs)
	{
		return lhs.identifier == rhs.identifier
			&& lhs.owner == rhs.owner
			&& lhs.vector == rhs.vector
			&& lhs.health == rhs.health;
	}

	friend bool operator!=(const Entity& lhs, const Entity& rhs)
	{
		return !(lhs == rhs);
	}

public:
	Identifier identifier;
	Identifier owner;
	Vector vector;
	Health health;
	inline static const std::regex pattern{R"(^(.*?)(?:\|\(([^)]*)\))?(?:\|\(([^)]*)\))?$)"};

	[[nodiscard]] const Identifier& getIdentifier() const { return identifier; }
	[[nodiscard]] const Identifier& getOwner() const { return owner; }
	[[nodiscard]] const Vector& getVector() const { return vector; }
	[[nodiscard]] const Health& getHealth() const { return health; }

	void setIdentifier(const Identifier& id) { identifier = id; }
	void setOwner(const Identifier& owner_id) { owner = owner_id; }
	void setVector(const Vector& vec) { vector = vec; }
	void setHealth(const Health& hlt) { health = hlt; }

	bool parse(const std::string& s);
	void clear();
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // ENTITY_HPP
