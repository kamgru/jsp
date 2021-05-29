#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/jsp.h"
#include <string>

jsp::Lexer lexer;

TEST_CASE("check empty object") {

    const std::string json = R"( { } )";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 2);
    CHECK(tokens->at(0).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::OBJECT_END);
}

TEST_CASE("check empty array") {

    const std::string json = R"( [ ] )";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 2);
    CHECK(tokens->at(0).tokenType == jsp::ARRAY_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::ARRAY_END);
}

TEST_CASE("check object with one string property") {

    const std::string json = R"( { "key": "value" } )";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 4);
    CHECK(tokens->at(0).tokenType == jsp::OBJECT_BEGIN);
    CHECK(tokens->at(1).tokenType == jsp::KEY);
    CHECK(tokens->at(2).tokenType == jsp::VALUE_STRING);
    CHECK(tokens->at(3).tokenType == jsp::OBJECT_END);
}

TEST_CASE("check object key index and length") {

    const std::string json = R"( { "key": "value" } )";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 4);

    jsp::Token result = tokens->at(1);
    CHECK(result.index == 4);
    CHECK(result.length == 3);
}

TEST_CASE("check object property index and length") {

    const std::string json = R"( { "key": "value" } )";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 4);

    jsp::Token result = tokens->at(2);
    CHECK(result.index == 11);
    CHECK(result.length == 5);
}

TEST_CASE("check simple string value") {

    const std::string json = R"("value")";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.index == 1);
    CHECK(result.length == 5);
    CHECK(result.tokenType == jsp::VALUE_STRING);
}

TEST_CASE("check integer value") {

    const std::string json = R"(1234)";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NUMBER);
    CHECK(result.index == 0);
    CHECK(result.length == 4);
}

TEST_CASE("check decimal value") {

    const std::string json = R"(12.34)";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NUMBER);
    CHECK(result.index == 0);
    CHECK(result.length == 5);
}

TEST_CASE("check negative decimal value") {

    const std::string json = R"(-12.34)";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NUMBER);
    CHECK(result.index == 0);
    CHECK(result.length == 6);
}

TEST_CASE("check negative decimal scientific notation value") {

    const std::string json = R"(-12.34e+2)";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NUMBER);
    CHECK(result.index == 0);
    CHECK(result.length == 9);
}

TEST_CASE("check null value") {

    const std::string json = R"(null)";
    auto tokens = lexer.scan(json);

    REQUIRE(tokens->size() == 1);

    jsp::Token result = tokens->at(0);
    CHECK(result.tokenType == jsp::VALUE_NULL);
    CHECK(result.index == 0);
    CHECK(result.length == 4);
}