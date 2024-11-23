#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>

#include "nlohmann/json.hpp"

class Identifier
{
	friend bool operator==(const Identifier& lhs, const Identifier& rhs)
	{
		return lhs.name_ == rhs.name_
			&& lhs.guid_ == rhs.guid_
			&& lhs.instance_ == rhs.instance_;
	}

	friend bool operator!=(const Identifier& lhs, const Identifier& rhs)
	{
		return !(lhs == rhs);
	}

	std::string name_;
	std::string guid_;
	std::string instance_;

public:
	Identifier() = default;

	Identifier(const std::string& name, const std::string& guid, const std::string& inst)
		: name_(name), guid_(guid), instance_(inst)
	{
	}

	[[nodiscard]] const std::string& getName() const { return name_; }
	[[nodiscard]] const std::string& getId() const { return guid_; }
	[[nodiscard]] const std::string& getInstance() const { return instance_; }

	void setName(const std::string& name_val) { name_ = name_val; }
	void setId(const std::string& id_val) { guid_ = id_val; }
	void setInstance(const std::string& instance_val) { instance_ = instance_val; }

	bool parse(const std::string& s);
	void clearIdAndInstance();
	void clear();
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // IDENTIFIER_HPP
