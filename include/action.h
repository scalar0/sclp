#ifndef ACTION_HPP
#define ACTION_HPP

#include <regex>
#include <string>
#include "effect.h"

class Action
{
	std::string name_;
	std::string guid_;
	inline static const std::regex pattern{
		R"(^(.*?)\s*\{(.*?)\}(?::\s*(.*?)\s*\{(.*?)\})?$)"
	};

public:
	Effect effect;

	// Getters and setters
	[[nodiscard]] std::string getName() const { return name_; }
	[[nodiscard]] const std::string& getId() const { return guid_; }
	[[nodiscard]] const Effect& getEffect() const { return effect; }

	void setName(const std::string& action_name) { name_ = action_name; }
	void setId(const std::string& action_id) { guid_ = action_id; }
	void setEffect(const Effect& eff) { effect = eff; }

	// Parsing function as a static member
	bool parse(const std::string& s);
	void clear();
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // ACTION_HPP
