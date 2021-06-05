#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest.h"
#include "../include/jsp_parser.h"

using namespace jsp;
Parser parser;

TEST_CASE("check empty object") {

    const std::string json = R"({})";
    auto node = parser.parse(json);

    CHECK(node->type == OBJECT_NODE);
}

TEST_CASE("check object string property") {
    const std::string json = R"({ "key": "value" })";

    auto result = parser.parseObject(json);
    auto value = result->get<std::string>("key");

    CHECK(value == "value");
}

TEST_CASE("check object number property") {
    const std::string json = R"({ "key": 12.34 })";

    auto result = parser.parseObject(json);
    auto value = result->get<double>("key");

    CHECK(value == 12.34);
}

TEST_CASE("check object boolean false property") {
    const std::string json = R"({ "key": false })";

    auto result = parser.parseObject(json);
    auto value = result->get<bool>("key");

    CHECK(value == false);
}

TEST_CASE("check object boolean true property") {
    const std::string json = R"({ "key": true })";

    auto result = parser.parseObject(json);
    auto value = result->get<bool>("key");

    CHECK(value == true);
}

TEST_CASE("check object with null property") {
    const std::string json = R"({ "key": null })";

    auto resut = parser.parseObject(json);
    auto value = resut->get<JEmpty>("key");

    CHECK(value.type == EMPTY_NODE);
}

TEST_CASE("check nested object") {
    const std::string json = R"({ "key" : { "nested": "value" } })";

    auto result = parser.parseObject(json);
    auto nested = result->get<JObject>("key");
    auto value = nested.get<std::string>("nested");

    CHECK(value == "value");
}

TEST_CASE("check array with simple values") {
    const std::string json = R"([1, "value", true])";

    auto result = parser.parse(json);
    auto array = static_cast<JArray*>(result);

    double first = (*array)[0];
    std::string second = (*array)[1];
    bool third = (*array)[2];

    CHECK(first == 1);
    CHECK(second == "value");
    CHECK(third == true);
}

TEST_CASE("check object with array property") {
    const std::string json = R"({ "key": ["value", null]  })";

    auto result = parser.parseObject(json);
    auto array = result->get<JArray>("key");

    std::string first = array[0];
    JEmpty second = array[1];
    CHECK(first == "value");
    CHECK(second.type == EMPTY_NODE);
}

