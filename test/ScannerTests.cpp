#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest.h"
#include "../include/jsp_scanner.h"

jsp::Scanner scanner;

TEST_CASE("check empty object") {

    const std::string json = R"( { } )";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 2);
    CHECK(tokens->at(0).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::OBJECT_END);
}

TEST_CASE("check empty array") {

    const std::string json = R"( [ ] )";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 2);
    CHECK(tokens->at(0).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::ARRAY_END);
}

TEST_CASE("check object with one string property") {

    const std::string json = R"( { "key": "value" } )";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 4);
    CHECK(tokens->at(0).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::KEY);
    CHECK(tokens->at(2).tokenType == jsp::VALUE_STRING);
    CHECK(tokens->at(3).tokenType == jsp::OBJECT_END);
}

TEST_CASE("check object key index and length") {

    const std::string json = R"( { "key": "value" } )";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 4);

    jsp::Token result = tokens->at(1);
    CHECK(result.index == 4);
    CHECK(result.length == 3);
}

TEST_CASE("check object property index and length") {

    const std::string json = R"( { "key": "value" } )";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 4);

    jsp::Token result = tokens->at(2);
    CHECK(result.index == 11);
    CHECK(result.length == 5);
}

TEST_CASE("check simple string value") {

    const std::string json = R"("value")";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.index == 1);
    CHECK(result.length == 5);
    CHECK(result.tokenType == jsp::VALUE_STRING);
}

TEST_CASE("check integer value") {

    const std::string json = R"(1234)";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NUMBER);
    CHECK(result.index == 0);
    CHECK(result.length == 4);
}

TEST_CASE("check decimal value") {

    const std::string json = R"(12.34)";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NUMBER);
    CHECK(result.index == 0);
    CHECK(result.length == 5);
}

TEST_CASE("check negative decimal value") {

    const std::string json = R"(-12.34)";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NUMBER);
    CHECK(result.index == 0);
    CHECK(result.length == 6);
}

TEST_CASE("check negative decimal scientific notation value") {

    const std::string json = R"(-12.34e+2)";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NUMBER);
    CHECK(result.index == 0);
    CHECK(result.length == 9);
}

TEST_CASE("check null literal") {

    std::string json;
    SUBCASE("null") { json = "null"; }
    SUBCASE("NULL") { json = "NULL"; }
    SUBCASE("nUlL") { json = "nUlL"; }
    SUBCASE("Null") { json = "Null"; }
    CAPTURE(json);

    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::LITERAL_NULL);
    CHECK(result.index == 0);
    CHECK(result.length == 4);
}

TEST_CASE("check true literal") {

    std::string json;

    SUBCASE("true") { json = "true"; }
    SUBCASE("TRUE") { json = "TRUE"; }
    SUBCASE("True") { json = "True"; }
    SUBCASE("tRuE") { json = "tRuE"; }
    CAPTURE(json);

    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::LITERAL_TRUE);
    CHECK(result.index == 0);
    CHECK(result.length == 4);
}

TEST_CASE("check false literal") {

    std::string json;

    SUBCASE("false") { json = "false"; }
    SUBCASE("FALSE") { json = "FALSE"; }
    SUBCASE("False") { json = "False"; }
    SUBCASE("fAlSe") { json = "fAlSe"; }
    CAPTURE(json);

    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::LITERAL_FALSE);
    CHECK(result.index == 0);
    CHECK(result.length == 5);
}

TEST_CASE("check array of objects") {

    const std::string json = R"([{},{},{}])";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 8);
    CHECK(tokens->at(0).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(2).tokenType == jsp::OBJECT_END);
    CHECK(tokens->at(3).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(4).tokenType == jsp::OBJECT_END);
    CHECK(tokens->at(5).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(6).tokenType == jsp::OBJECT_END);
    CHECK(tokens->at(7).tokenType == jsp::ARRAY_END);
}

TEST_CASE("check object with array") {

    const std::string json = R"({"arr":[1, 2, 3]})";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 8);
    CHECK(tokens->at(0).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::KEY);
    CHECK(tokens->at(2).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(3).tokenType == jsp::VALUE_NUMBER);
    CHECK(tokens->at(4).tokenType == jsp::VALUE_NUMBER);
    CHECK(tokens->at(5).tokenType == jsp::VALUE_NUMBER);
    CHECK(tokens->at(6).tokenType == jsp::ARRAY_END);
    CHECK(tokens->at(7).tokenType == jsp::OBJECT_END);
}

TEST_CASE("check array of arrays") {

    const std::string json = R"([[],[],[]])";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 8);
    CHECK(tokens->at(0).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(2).tokenType == jsp::ARRAY_END);
    CHECK(tokens->at(3).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(4).tokenType == jsp::ARRAY_END);
    CHECK(tokens->at(5).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(6).tokenType == jsp::ARRAY_END);
    CHECK(tokens->at(7).tokenType == jsp::ARRAY_END);
}

TEST_CASE("check nested object") {

    const std::string json = R"({ "obj": { "nested" : true } })";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 7);
    CHECK(tokens->at(0).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::KEY);
    CHECK(tokens->at(2).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(3).tokenType == jsp::KEY);
    CHECK(tokens->at(4).tokenType == jsp::LITERAL_TRUE);
    CHECK(tokens->at(5).tokenType == jsp::OBJECT_END);
    CHECK(tokens->at(6).tokenType == jsp::OBJECT_END);
}

TEST_CASE("check array of simple values") {

    const std::string json = R"([1, "value", true, false, null])";
    auto tokens = scanner.scan(json);

    REQUIRE(tokens->size() == 7);
    CHECK(tokens->at(0).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::VALUE_NUMBER);
    CHECK(tokens->at(2).tokenType == jsp::VALUE_STRING);
    CHECK(tokens->at(3).tokenType == jsp::LITERAL_TRUE);
    CHECK(tokens->at(4).tokenType == jsp::LITERAL_FALSE);
    CHECK(tokens->at(5).tokenType == jsp::LITERAL_NULL);
    CHECK(tokens->at(6).tokenType == jsp::ARRAY_END);
}