#include <gtest/gtest.h>
#include "vector.h"
#include "../parsetest.h"
#include "nlohmann/json.hpp"

class VectorParseTest : public ParseTest<Vector>
{
};

static void check_vector_state(const Vector& v,
								const double x = 0.0,
								const double y = 0.0,
								const double z = 0.0,
								const double t = 0.0)
{
	EXPECT_DOUBLE_EQ(v.getX(), x) << "X value mismatch.";
	EXPECT_DOUBLE_EQ(v.getY(), y) << "Y value mismatch.";
	EXPECT_DOUBLE_EQ(v.getZ(), z) << "Z value mismatch.";
	EXPECT_DOUBLE_EQ(v.getAngle(), t) << "Angle value mismatch.";
}

TEST(VectorTest, SetAndGet)
{
	Vector vector;

	vector.setX(1.0);
	EXPECT_DOUBLE_EQ(vector.getX(), 1.0) << "X not set correctly.";

	vector.setY(2.0);
	EXPECT_DOUBLE_EQ(vector.getY(), 2.0) << "Y not set correctly.";

	vector.setZ(3.0);
	EXPECT_DOUBLE_EQ(vector.getZ(), 3.0) << "Z not set correctly.";

	vector.setAngle(45.0);
	EXPECT_DOUBLE_EQ(vector.getAngle(), 45.0) << "Angle not set correctly.";
}

TEST_P(VectorParseTest, Parse)
{
	Vector v;
	const std::string input = std::get<0>(GetParam());
	const Vector ev = std::get<1>(GetParam());

	if (input.empty() || input.find_first_not_of("0123456789.,-") != std::string::npos)
	{
		EXPECT_FALSE(v.parse(input)) << "Parsing invalid input should fail.";
		check_vector_state(v);
	}
	else
	{
		EXPECT_TRUE(v.parse(input)) << "Parsing valid input should succeed.";
		check_vector_state(v, ev.getX(), ev.getY(), ev.getZ(), ev.getAngle());
	}
}


INSTANTIATE_TEST_SUITE_P(
	Vector,
	VectorParseTest,
	::testing::Values(
		std::make_tuple("", Vector()),
		std::make_tuple("0.0,0.0,0.0,0.0", Vector()),
		std::make_tuple("invalid_vector_string", Vector()),
		std::make_tuple("1.0,2.0,3.0,45.0", Vector(1.0, 2.0, 3.0, 45.0))
	)
);

TEST(VectorTest, Clear)
{
	Vector v;
	v.setX(1.0);
	v.setY(2.0);
	v.setZ(3.0);
	v.setAngle(45.0);

	v.clear();
	check_vector_state(v);
}

TEST(VectorTest, ToJson)
{
	Vector vector;
	vector.setX(1.0);
	vector.setY(2.0);
	vector.setZ(3.0);
	vector.setAngle(45.0);

	const nlohmann::json expected_json = {
		{"x", 1.0},
		{"y", 2.0},
		{"z", 3.0},
		{"angle", 45.0}
	};
	EXPECT_EQ(vector.to_json(), expected_json) << "JSON serialization mismatch.";
}
