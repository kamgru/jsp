#include "../include/jsp.h"

using namespace jsp;

namespace jspInternal {

    class TokenEnumerator {
    public:
        TokenEnumerator(std::vector<Token>::iterator begin, std::vector<Token>::iterator end)
                : m_iterator(begin), m_end(end) {}

        bool MoveNext() {
            if (m_iterator != m_end) {
                m_iterator++;
                return true;
            }

            return false;
        }

        TOKEN_TYPE tokenType() { return m_iterator->tokenType; }

        unsigned int index() { return m_iterator->index; }

        unsigned int length() { return m_iterator->length; }

    private:
        std::vector<Token>::iterator m_iterator;
        std::vector<Token>::iterator m_end;
    };

    JNode* parseNode(TokenEnumerator& enumerator, std::string const& input);

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

        while (enumerator.MoveNext()){
            TOKEN_TYPE tokenType = enumerator.tokenType();

            if (tokenType == ARRAY_END){
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

        if (enumerator.tokenType() == ARRAY_BEGIN){
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
}


JObject* Parser::parseObject(const std::string& json) {
    Scanner scanner;
    auto tokens = scanner.scan(json);
    if (tokens->size() == 0 || tokens->front().tokenType != OBJECT_BEGIN) {
        return nullptr;
    }

    jspInternal::TokenEnumerator enumerator(tokens->begin(), tokens->end());
    JObject* jObject = jspInternal::parseObject(enumerator, json);

    return jObject;
}

JNode* Parser::parse(const std::string& json) {
    Scanner scanner;
    auto tokens = scanner.scan(json);
    jspInternal::TokenEnumerator enumerator(tokens->begin(), tokens->end());

    JNode* node = parseNode(enumerator, json);
    return node;
}