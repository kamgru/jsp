#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest.h"
#include "../include/jsp.h"

using namespace jsp;
Parser parser;

TEST_CASE("check empty object") {

    const std::string json = R"({})";
    auto node = parser.parse(json);

    CHECK(node->type == OBJECT_NODE);
}

TEST_CASE("check simple object") {

    const std::string json = R"({ "key": "value" })";
    auto node = parser.parse(json);

    JObject result = static_cast<JObject&>(*node);
    JNode* value = result.get("key");

    JStringNode stringNode = static_cast<JStringNode&>(*value);
    CHECK(stringNode.value == "value");
}