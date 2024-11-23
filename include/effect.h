#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <regex>
#include <string>

#include "nlohmann/json.hpp"

class Effect
{
	friend bool operator==(const Effect& lhs, const Effect& rhs)
	{
		return lhs.name_ == rhs.name_
			&& lhs.guid_ == rhs.guid_;
	}

	friend bool operator!=(const Effect& lhs, const Effect& rhs)
	{
		return !(lhs == rhs);
	}

	std::string name_;
	std::string guid_;
	inline static const std::regex pattern{
		R"(^(.*?)\s*\{(.*?)\}$)"
	};

public:
	Effect() = default;

	Effect(const std::string& name, const std::string& guid)
		: name_(name),
		guid_(guid)
	{
	}

	// Getters and setters
	[[nodiscard]] std::string getName() const { return name_; }
	[[nodiscard]] std::string getId() const { return guid_; }

	void setName(const std::string& n) { name_ = n; }
	void setId(const std::string& id) { guid_ = id; }

	// Parsing function as a static member
	bool parse(const std::string& s);
	void clear();
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // EFFECT_HPP
