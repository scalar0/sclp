#ifndef HEALTH_HPP
#define HEALTH_HPP

#include <string>

#include "nlohmann/json.hpp"

class Health
{
	friend bool operator==(const Health& lhs, const Health& rhs)
	{
		return lhs.current_hp_ == rhs.current_hp_
			&& lhs.max_hp_ == rhs.max_hp_;
	}

	friend bool operator!=(const Health& lhs, const Health& rhs)
	{
		return !(lhs == rhs);
	}

	int current_hp_;
	int max_hp_;

public:
	Health() : current_hp_(0), max_hp_(0)
	{
	}

	Health(const int current_hp, const int max_hp)
		: current_hp_(current_hp),
		max_hp_(max_hp)
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
