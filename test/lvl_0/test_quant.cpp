#include <gtest/gtest.h>
#include "quant.h"
#include "../parsetest.h"
#include "nlohmann/json.hpp"

class QuantParseTest : public ParseTest<Quant>
{
};

static void check_quant_state(const Quant& q,
							const int value = 0,
							const std::string& simple_value = "",
							const bool is_crit = false,
							const int effective = 0,
							const std::string& damage_type = "",
							const std::string& damage_type_guid = "",
							const std::string& reflect_type = "",
							const std::string& reflect_type_guid = "",
							const bool is_mitigation = false,
							const std::string& mitigation_type = "",
							const std::string& mitigation_type_guid = "",
							const int absorb_value = 0,
							const std::string& absorb_type = "",
							const std::string& absorb_type_guid = "")
{
	EXPECT_EQ(q.getValue(), value) << "Value mismatch.";
	EXPECT_EQ(q.getSimpleValue(), simple_value) << "Simple value mismatch.";
	EXPECT_EQ(q.getIsCrit(), is_crit) << "Critical flag mismatch.";
	EXPECT_EQ(q.getEffective(), effective) << "Effective value mismatch.";
	EXPECT_EQ(q.getDamageType(), damage_type) << "Damage type mismatch.";
	EXPECT_EQ(q.getDamageTypeGuid(), damage_type_guid) << "Damage type GUID mismatch.";
	EXPECT_EQ(q.getReflectType(), reflect_type) << "Reflect type mismatch.";
	EXPECT_EQ(q.getReflectTypeGuid(), reflect_type_guid) << "Reflect type GUID mismatch.";
	EXPECT_EQ(q.getIsMitigation(), is_mitigation) << "Mitigation flag mismatch.";
	EXPECT_EQ(q.getMitigationType(), mitigation_type) << "Mitigation type mismatch.";
	EXPECT_EQ(q.getMitigationTypeGuid(), mitigation_type_guid) << "Mitigation type GUID mismatch.";
	EXPECT_EQ(q.getAbsorbValue(), absorb_value) << "Absorb value mismatch.";
	EXPECT_EQ(q.getAbsorbType(), absorb_type) << "Absorb type mismatch.";
	EXPECT_EQ(q.getAbsorbTypeGuid(), absorb_type_guid) << "Absorb type GUID mismatch.";
}

TEST_P(QuantParseTest, Parse)
{
	Quant q;
	const std::string input = std::get<0>(GetParam());
	const Quant eq = std::get<1>(GetParam());
	EXPECT_TRUE(q.parse(input));
	check_quant_state(q,
					eq.getValue(),
					eq.getSimpleValue(),
					eq.getIsCrit(),
					eq.getEffective(),
					eq.getDamageType(),
					eq.getDamageTypeGuid(),
					eq.getReflectType(),
					eq.getReflectTypeGuid(),
					eq.getIsMitigation(),
					eq.getMitigationType(),
					eq.getMitigationTypeGuid(),
					eq.getAbsorbValue(),
					eq.getAbsorbType(),
					eq.getAbsorbTypeGuid());
}

INSTANTIATE_TEST_SUITE_P(
	Quant,
	QuantParseTest,
	testing::Values(
		std::make_tuple("", Quant()),
		std::make_tuple("0 -miss {836045448945502}", Quant( 0, false, false, "", "", "", "", true, "miss",
			"836045448945502",
			0, "", "", "" )),
		std::make_tuple("invalid_quant_string", Quant("invalid_quant_string" ))
	)
);

TEST(QuantTest, ToJson)
{
	Quant q;
	q.parse("0 -miss {836045448945502}");
	const nlohmann::json expected_json = {
		{"absorb_type", ""}, {"absorb_type_guid", ""}, {"absorb_value", 0}, {"damage_type", ""},
		{"damage_type_guid", ""}, {"effective", 0}, {"is_crit", false}, {"is_mitigation", true},
		{"mitigation_type", "miss"}, {"mitigation_type_guid", "836045448945502"}, {"reflect_type", ""},
		{"reflect_type_guid", ""}, {"simple_value", ""}, {"value", 0}
	};
	EXPECT_EQ(q.to_json(), expected_json);
}
