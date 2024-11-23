#ifndef QUANT_HPP
#define QUANT_HPP

#include <regex>
#include <string>

#include "nlohmann/json.hpp"

class Quant
{
	friend bool operator==(const Quant& lhs, const Quant& rhs)
	{
		return lhs.value_ == rhs.value_
			&& lhs.is_crit_ == rhs.is_crit_
			&& lhs.effective_value_ == rhs.effective_value_
			&& lhs.damage_type_ == rhs.damage_type_
			&& lhs.damage_type_guid_ == rhs.damage_type_guid_
			&& lhs.reflect_type_ == rhs.reflect_type_
			&& lhs.reflect_type_guid_ == rhs.reflect_type_guid_
			&& lhs.is_mitigation_ == rhs.is_mitigation_
			&& lhs.mitigation_type_ == rhs.mitigation_type_
			&& lhs.mitigation_type_guid_ == rhs.mitigation_type_guid_
			&& lhs.absorb_value_ == rhs.absorb_value_
			&& lhs.absorb_type_ == rhs.absorb_type_
			&& lhs.absorb_type_guid_ == rhs.absorb_type_guid_
			&& lhs.simple_value_ == rhs.simple_value_;
	}

	friend bool operator!=(const Quant& lhs, const Quant& rhs)
	{
		return !(lhs == rhs);
	}

	int value_;
	bool is_crit_;
	int effective_value_;
	std::string damage_type_;
	std::string damage_type_guid_;
	std::string reflect_type_;
	std::string reflect_type_guid_;
	bool is_mitigation_;
	std::string mitigation_type_;
	std::string mitigation_type_guid_;
	int absorb_value_;
	std::string absorb_type_;
	std::string absorb_type_guid_;
	std::string simple_value_;
	inline static const std::regex pattern{
		R"((-?\d+(?:\.0)?)?(\*)?\s*(?:~(-?\d+))?\s*(?:\s+([^\s\-]+)\s*\{(\d+)\})?(?:\s*\(([^\s]+)\s*\{(\d+)\}\))?(?:\s*-(?:\s*([^\s]+)\s*\{(\d+)\})?)?(?:\s*\((\d+)\s+([^\s]+)\s*\{(\d+)\}\))?)"
	};

public:
	Quant(const int value, const bool is_crit, const int effective_value, const std::string& damage_type,
		const std::string& damage_type_guid, const std::string& reflect_type, const std::string& reflect_type_guid,
		const bool is_mitigation, const std::string& mitigation_type, const std::string& mitigation_type_guid,
		const int absorb_value, const std::string& absorb_type, const std::string& absorb_type_guid,
		const std::string& simple_value)
		: value_(value),
		is_crit_(is_crit),
		effective_value_(effective_value),
		damage_type_(damage_type),
		damage_type_guid_(damage_type_guid),
		reflect_type_(reflect_type),
		reflect_type_guid_(reflect_type_guid),
		is_mitigation_(is_mitigation),
		mitigation_type_(mitigation_type),
		mitigation_type_guid_(mitigation_type_guid),
		absorb_value_(absorb_value),
		absorb_type_(absorb_type),
		absorb_type_guid_(absorb_type_guid),
		simple_value_(simple_value)
	{
	}

	Quant() : value_(0), is_crit_(false), effective_value_(0), is_mitigation_(false), absorb_value_(0)
	{
	}

	explicit Quant(const std::string& simple_value)
		: value_(0), is_crit_(false), effective_value_(0), is_mitigation_(false), absorb_value_(0),
		simple_value_(simple_value)
	{
	}


	// Getters and setters
	[[nodiscard]] int getValue() const { return value_; }
	[[nodiscard]] bool getIsCrit() const { return is_crit_; }
	[[nodiscard]] int getEffective() const { return effective_value_; }
	[[nodiscard]] const std::string& getDamageType() const { return damage_type_; }
	[[nodiscard]] const std::string& getDamageTypeGuid() const { return damage_type_guid_; }
	[[nodiscard]] const std::string& getReflectType() const { return reflect_type_; }
	[[nodiscard]] const std::string& getReflectTypeGuid() const { return reflect_type_guid_; }
	[[nodiscard]] bool getIsMitigation() const { return is_mitigation_; }
	[[nodiscard]] const std::string& getMitigationType() const { return mitigation_type_; }
	[[nodiscard]] const std::string& getMitigationTypeGuid() const { return mitigation_type_guid_; }
	[[nodiscard]] int getAbsorbValue() const { return absorb_value_; }
	[[nodiscard]] const std::string& getAbsorbType() const { return absorb_type_; }
	[[nodiscard]] const std::string& getAbsorbTypeGuid() const { return absorb_type_guid_; }
	[[nodiscard]] const std::string& getSimpleValue() const { return simple_value_; }

	// Static parsing function
	bool parse(const std::string& s);
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // QUANT_HPP
