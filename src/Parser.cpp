#include "../include/jsp_scanner.h"
#include "../include/jsp_parser.h"
#include "TokenEnumerator.h"

using namespace jsp;
using namespace jsp::internal;

JNode* parseNode(TokenEnumerator& enumerator, std::string const& input);
JObject* parseObject(TokenEnumerator& enumerator, std::string const& input);
JArray* parseArray(TokenEnumerator& enumerator, std::string const& input);

JNode* Parser::parse(const std::string& json) {
    Scanner scanner;
    auto tokens = scanner.scan(json);
    TokenEnumerator enumerator(tokens->begin(), tokens->end());

    JNode* node = parseNode(enumerator, json);
    return node;
}

JObject* Parser::parseObject(const std::string& json) {
    Scanner scanner;
    auto tokens = scanner.scan(json);
    if (tokens->size() == 0 || tokens->front().tokenType != OBJECT_BEGIN) {
        return nullptr;
    }

    TokenEnumerator enumerator(tokens->begin(), tokens->end());
    JObject* jObject = ::parseObject(enumerator, json);

    return jObject;
}

JArray* Parser::parseArray(const std::string& json) {
    Scanner scanner;
    auto tokens = scanner.scan(json);
    if (tokens->size() == 0 || tokens->front().tokenType != ARRAY_BEGIN) {
        return nullptr;
    }

    TokenEnumerator enumerator(tokens->begin(), tokens->end());
    JArray* jArray = ::parseArray(enumerator, json);

    return jArray;
}

JValue<std::string>* parseString(TokenEnumerator& enumerator, std::string const& input) {
    std::string value = input.substr(enumerator.index(), enumerator.length());
    return new JValue<std::string>(value);
}

JObject* parseObject(TokenEnumerator& enumerator, std::string const& input) {
    std::map<std::string, JNode*> nodes;
    while (enumerator.MoveNext()) {
        TOKEN_TYPE tokenType = enumerator.tokenType();

        if (tokenType == OBJECT_END) {
            break;
        }

        if (tokenType == KEY) {
            JValue<std::string>* keyNode = parseString(enumerator, input);
            enumerator.MoveNext();
            JNode* valueNode = parseNode(enumerator, input);
            nodes.emplace(keyNode->value, valueNode);
        }
    }

    return new JObject(nodes);
}

JValue<double>* parseNumber(TokenEnumerator& enumerator, std::string const& input) {
    std::string value = input.substr(enumerator.index(), enumerator.length());
    double number = std::stod(value);
    return new JValue<double>(number);
}

JArray* parseArray(TokenEnumerator& enumerator, std::string const& input) {
    std::vector<JNode*> nodes;

    while (enumerator.MoveNext()) {
        TOKEN_TYPE tokenType = enumerator.tokenType();

        if (tokenType == ARRAY_END) {
            break;
        }

        JNode* node = parseNode(enumerator, input);
        nodes.emplace_back(node);
    }

    return new JArray(nodes);
}

JNode* parseNode(TokenEnumerator& enumerator, std::string const& input) {
    if (enumerator.tokenType() == OBJECT_BEGIN) {
        return parseObject(enumerator, input);
    }

    if (enumerator.tokenType() == ARRAY_BEGIN) {
        return parseArray(enumerator, input);
    }

    if (enumerator.tokenType() == VALUE_STRING) {
        return parseString(enumerator, input);
    }

    if (enumerator.tokenType() == VALUE_NUMBER) {
        return parseNumber(enumerator, input);
    }

    if (enumerator.tokenType() == LITERAL_TRUE) {
        return new JValue<bool>(true);
    }

    if (enumerator.tokenType() == LITERAL_FALSE) {
        return new JValue<bool>(false);
    }

    return new JEmpty();
}