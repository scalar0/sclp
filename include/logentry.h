#ifndef LOGENTRY_HPP
#define LOGENTRY_HPP

#include <string>
#include "entity.h"
#include "effect.h"
#include "action.h"
#include "quant.h"

class LogEntry
{
	friend bool operator==(const LogEntry& lhs, const LogEntry& rhs)
	{
		return lhs.timestamp == rhs.timestamp
			&& lhs.source == rhs.source
			&& lhs.target == rhs.target
			&& lhs.ability == rhs.ability
			&& lhs.action == rhs.action
			&& lhs.quants == rhs.quants
			&& lhs.threat == rhs.threat;
	}

	friend bool operator!=(const LogEntry& lhs, const LogEntry& rhs)
	{
		return !(lhs == rhs);
	}

	inline static const std::regex pattern{
		R"(^\[(\d{2}:\d{2}:\d{2}\.\d{3})\] \[(.*?)\] \[(.*?)\] \[(.*?)\] \[(.*?)\](?: \((.*?)\))?(?: <(.*?)>)?$)"
	};

public:
	std::string timestamp;
	Entity source;
	Entity target;
	Effect ability;
	Action action;
	Quant quants;
	std::string threat;


	[[nodiscard]] const std::string& getTimestamp() const { return timestamp; }
	[[nodiscard]] const Entity& getSource() const { return source; }
	[[nodiscard]] const Entity& getTarget() const { return target; }
	[[nodiscard]] const Effect& getAbility() const { return ability; }
	[[nodiscard]] const Action& getAction() const { return action; }
	[[nodiscard]] const Quant& getQuants() const { return quants; }
	[[nodiscard]] const std::string& getThreat() const { return threat; }

	void setTimestamp(const std::string& ts) { timestamp = ts; }
	void setSource(const Entity& src) { source = src; }
	void setTarget(const Entity& tgt) { target = tgt; }
	void setAbility(const Effect& e) { ability = e; }
	void setAction(const Action& a) { action = a; }
	void setQuants(const Quant& q) { quants = q; }
	void setThreat(const std::string& t) { threat = t; }

	bool parse(const std::string& l);
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // LOGENTRY_HPP
