#include <gtest/gtest.h>
#include "identifier.h"
#include "../parsetest.h"
#include "nlohmann/json.hpp"

class IdentifierParseTest : public ParseTest<Identifier>
{
};

static void check_identifier_state(const Identifier& id, const std::string& name, const std::string& guid,
									const std::string& instance)
{
	EXPECT_EQ(id.getName(), name);
	EXPECT_EQ(id.getId(), guid);
	EXPECT_EQ(id.getInstance(), instance);
}

TEST(IdentifierTest, SetAndGet)
{
	Identifier id;
	id.setName("Bak'aara");
	EXPECT_EQ(id.getName(), "Bak'aara");
	id.setId("687421948234378");
	EXPECT_EQ(id.getId(), "687421948234378");
	id.setInstance("11767001200859");
	EXPECT_EQ(id.getInstance(), "11767001200859");
}

TEST_P(IdentifierParseTest, Parse)
{
	Identifier id;
	const std::string input = std::get<0>(GetParam());
	const Identifier eid = std::get<1>(GetParam());
	EXPECT_TRUE(id.parse(input));
	check_identifier_state(id, eid.getName(), eid.getId(), eid.getInstance());
}

INSTANTIATE_TEST_SUITE_P(
	Identifier,
	IdentifierParseTest,
	::testing::Values(
		std::make_tuple("", Identifier()),
		std::make_tuple("@Bak'aara#687421948234378", Identifier("Bak'aara", "687421948234378", "")),
		std::make_tuple("Imperial Enforcer {4510969791250432}:11767001200859", Identifier("Imperial Enforcer",
			"4510969791250432", "11767001200859")),
		std::make_tuple("Imperial Enforcer {4510969791250432}", Identifier("Imperial Enforcer", "4510969791250432", ""))
	)
);

TEST(IdentifierTest, Clear)
{
	Identifier identifier;
	identifier.setName("TestName");
	identifier.setId("1234");
	identifier.setInstance("Instance1");
	identifier.clear();
	EXPECT_EQ(identifier.getName(), "");
	EXPECT_EQ(identifier.getId(), "");
	EXPECT_EQ(identifier.getInstance(), "");
}

TEST(IdentifierTest, ToJson)
{
	Identifier identifier;
	identifier.setName("TestName");
	identifier.setId("1234");
	identifier.setInstance("Instance1");
	const nlohmann::json expected_json = {
		{"name", "TestName"},
		{"id", "1234"},
		{"instance", "Instance1"}
	};
	EXPECT_EQ(identifier.to_json(), expected_json);
}
