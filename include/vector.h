#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>

#include "nlohmann/json.hpp"

class Vector
{
	double x_;
	double y_;
	double z_;
	double ang_;

public:
	Vector() : x_(0.0), y_(0.0), z_(0.0), ang_(0.0)
	{
	}

	// Getters and setters
	[[nodiscard]] double getX() const { return x_; }
	[[nodiscard]] double getY() const { return y_; }
	[[nodiscard]] double getZ() const { return z_; }
	[[nodiscard]] double getAngle() const { return ang_; }

	void setX(const double x_val) { x_ = x_val; }
	void setY(const double y_val) { y_ = y_val; }
	void setZ(const double z_val) { z_ = z_val; }
	void setAngle(const double ang_val) { ang_ = ang_val; }

	// Parsing function as a static member
	bool parse(const std::string& s);
	void clear();
	[[nodiscard]] nlohmann::json to_json() const;
};

#endif // VECTOR_HPP
