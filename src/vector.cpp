#include "vector.h"
#include <sstream>
#include <vector>
#include <stdexcept>

#include "nlohmann/json_fwd.hpp"

bool Vector::parse(const std::string& s)
{
	if (s.empty()) return false;

	std::istringstream iss(s);
	std::string token;
	std::vector<double> components;

	while (std::getline(iss, token, ','))
	{
		try
		{
			components.push_back(std::stod(token));
		}
		catch (const std::invalid_argument&)
		{
			components.push_back(0.0); // Default to 0.0 if parsing fails
		}
	}

	if (components.size() == 4)
	{
		setX(components[0]);
		setY(components[1]);
		setZ(components[2]);
		setAngle(components[3]);
		return true;
	}
	return false;
}

void Vector::clear()
{
	setX(0.0);
	setY(0.0);
	setZ(0.0);
	setAngle(0.0);
}


nlohmann::json Vector::to_json() const
{
	return nlohmann::json{
		{"x", getX()},
		{"y", getY()},
		{"z", getZ()},
		{"angle", getAngle()}
	};
}
