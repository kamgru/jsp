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

TEST_CASE("check object string property") {

    const std::string json = R"({ "key": "value" })";
    auto node = parser.parse(json);

    JObject result = static_cast<JObject&>(*node);
    std::string value = result.get<std::string>("key");

    CHECK(value == "value");
}

TEST_CASE("check object number property") {

    const std::string json = R"({ "key": 12.34 })";
    auto node = parser.parse(json);

    JObject result = static_cast<JObject&>(*node);
    double value = result.get<double>("key");

    CHECK(value == 12.34);
}

TEST_CASE("check object boolean false property") {

    const std::string json = R"({ "key": false })";
    auto node = parser.parse(json);

    JObject result = static_cast<JObject&>(*node);
    bool value = result.get<bool>("key");

    CHECK(value == false);
}

TEST_CASE("check object boolean true property") {

    const std::string json = R"({ "key": true })";
    auto node = parser.parse(json);

    JObject result = static_cast<JObject&>(*node);
    bool value = result.get<bool>("key");

    CHECK(value == true);
}

TEST_CASE("check nested object") {

    const std::string json = R"({ "key" : { "nested": "value" } })";
    auto node = parser.parse(json);

    JObject result = static_cast<JObject&>(*node);
    JObject* nested = static_cast<JObject*>(result.get("key"));
    std::string value = nested->get<std::string>("nested");

    CHECK(value == "value");
}