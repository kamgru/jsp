#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest.h"
#include "../include/jsp_parser.h"

using namespace jsp;

TEST_SUITE("Parser::parseArray") {
    Parser parser;

    TEST_CASE("empty array") {
        const std::string json = R"([])";

        auto result = parser.parseArray(json);

        REQUIRE(result->size() == 0);
    }

    TEST_CASE("array with one number") {
        const std::string json = R"([ 1 ])";

        auto result = parser.parseArray(json);

        CHECK((double)((*result)[0]) == 1.0);
    }

    TEST_CASE("array with three numbers") {
        const std::string json = R"([ 1, 2, 3 ])";

        auto result = parser.parseArray(json);

        CHECK((double)((*result)[0]) == 1);
        CHECK((double)((*result)[1]) == 2);
        CHECK((double)((*result)[2]) == 3);
    }

    TEST_CASE("array with one string") {
        const std::string json = R"(["value"])";

        auto result = parser.parseArray(json);

        std::string value = (*result)[0];

        CHECK(value == "value");
    }

    TEST_CASE("array with three strings") {
        const std::string json = R"(["x", "y", "z"])";

        auto result = parser.parseArray(json);

        CHECK(result->at<std::string>(0) == "x");
        CHECK(result->at<std::string>(1) == "y");
        CHECK(result->at<std::string>(2) == "z");
    }

    TEST_CASE("array with one object") {
        const std::string json = R"( [{"key":"value"}] )";

        auto result = parser.parseArray(json);

        JObject jObject = (*result)[0];
        auto value = jObject.get<std::string>("key");

        CHECK(value == "value");
    }

    TEST_CASE("array with three objects") {
        const std::string json = R"( [ {"name":"one"}, {"name":"two"}, {"name":"three"} ] )";

        auto result = parser.parseArray(json);
        std::string expectedNames[] = {"one", "two", "three"};

        for (int i = 0; i < 3; i++) {
            JObject jObject = (*result)[i];
            auto name = jObject.get<std::string>("name");
            CHECK(name == expectedNames[i]);
        }
    }
}
