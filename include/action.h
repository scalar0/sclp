#ifndef ACTION_HPP
#define ACTION_HPP

#include "effect.h"
#include <regex>
#include <string>

/**
 * @class Action
 * @brief Represents an action with a name, ID, and associated effect.
 */
class Action
{
	/**
	 * @brief Compares two Action objects for equality.
	 * @param lhs The left-hand side Action object.
	 * @param rhs The right-hand side Action object.
	 * @return True if the two Action objects are equal, false otherwise.
	 */
	friend bool operator==(const Action& lhs, const Action& rhs)
	{
		return lhs.name_ == rhs.name_
			&& lhs.guid_ == rhs.guid_
			&& lhs.effect == rhs.effect;
	}

	/**
	 * @brief Compares two Action objects for inequality.
	 * @param lhs The left-hand side Action object.
	 * @param rhs The right-hand side Action object.
	 * @return True if the two Action objects are not equal, false otherwise.
	 */
	friend bool operator!=(const Action& lhs, const Action& rhs)
	{
		return !(lhs == rhs);
	}

	std::string name_;
	std::string guid_;
	inline static const std::regex pattern{
		R"(^(.*?)\s*\{(.*?)\}(?::\s*(.*?)\s*\{(.*?)\})?$)"
	};

public:
	Effect effect;

	/**
	 * @brief Gets the name of the action.
	 * @return The name of the action.
	 */
	[[nodiscard]] std::string getName() const { return name_; }

	/**
	 * @brief Gets the ID of the action.
	 * @return The ID of the action.
	 */
	[[nodiscard]] const std::string& getId() const { return guid_; }

	/**
	 * @brief Gets the effect associated with the action.
	 * @return The effect associated with the action.
	 */
	[[nodiscard]] const Effect& getEffect() const { return effect; }

	/**
	 * @brief Sets the name of the action.
	 * @param action_name The new name of the action.
	 */
	void setName(const std::string& action_name) { name_ = action_name; }

	/**
	 * @brief Sets the ID of the action.
	 * @param action_id The new ID of the action.
	 */
	void setId(const std::string& action_id) { guid_ = action_id; }

	/**
	 * @brief Sets the effect associated with the action.
	 * @param eff The new effect to associate with the action.
	 */
	void setEffect(const Effect& eff) { effect = eff; }

	/**
	 * @brief Parses a string to initialize the action.
	 * @param s The string to parse.
	 * @return True if parsing was successful, false otherwise.
	 */
	bool parse(const std::string& s);

	/**
	 * @brief Clears the action's data.
	 */
	void clear();

	/**
	 * @brief Converts the action to a JSON object.
	 * @return A JSON object representing the action.
	 */
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // ACTION_HPP
