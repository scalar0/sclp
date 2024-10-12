#ifndef QUANT_HPP
#define QUANT_HPP

#include <regex>
#include <string>

#include "nlohmann/json.hpp"

class Quant
{
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
	Quant() : value_(0), is_crit_(false), effective_value_(0), is_mitigation_(false), absorb_value_(0)
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
