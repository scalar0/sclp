#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <regex>
#include <string>

#include "nlohmann/json.hpp"

class Effect
{
	std::string name_;
	std::string guid_;
	inline static const std::regex pattern{
		R"(^(.*?)\s*\{(.*?)\}$)"
	};

public:
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
