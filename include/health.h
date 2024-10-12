#ifndef HEALTH_HPP
#define HEALTH_HPP

#include <string>

#include "nlohmann/json.hpp"

class Health
{
	int current_hp_;
	int max_hp_;

public:
	Health() : current_hp_(0), max_hp_(0)
	{
	}

	[[nodiscard]] int getCurrentHp() const { return current_hp_; }
	[[nodiscard]] int getMaxHp() const { return max_hp_; }

	void setCurrentHp(int hp) { current_hp_ = hp; }
	void setMaxHp(int hp) { max_hp_ = hp; }

	bool parse(const std::string& s);
	void clear();
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // HEALTH_HPP
