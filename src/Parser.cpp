#include "../include/jsp.h"

using namespace jsp;

class TokenIterator {
public:
    TokenIterator(std::vector<Token>::iterator begin, std::vector<Token>::iterator end)
            : m_iterator(begin), m_end(end) {}

    bool MoveNext() {
        if (m_iterator != m_end) {
            m_iterator++;
            return true;
        }

        return false;
    }

    TOKEN_TYPE tokenType() {
        return m_iterator->tokenType;
    }

    unsigned int index() {
        return m_iterator->index;
    }

    unsigned int length() {
        return m_iterator->length;
    }

private:
    std::vector<Token>::iterator m_iterator;
    std::vector<Token>::iterator m_end;
};

JNode* parseNode(TokenIterator &iterator, std::string const &input);

JValue<std::string>* parseString(TokenIterator &iterator, std::string const &input) {
    std::string value = input.substr(iterator.index(), iterator.length());
    return new JValue<std::string>(value);
}

JObject* parseObject(TokenIterator &iterator, std::string const &input) {

    std::map<std::string, JNode*> nodes;
    while (iterator.MoveNext()) {
        TOKEN_TYPE tokenType = iterator.tokenType();

        if (tokenType == OBJECT_END) {
            break;
        }

        if (tokenType == KEY) {
            JValue<std::string> *keyNode = parseString(iterator, input);
            iterator.MoveNext();
            JNode *valueNode = parseNode(iterator, input);
            nodes.emplace(keyNode->value, valueNode);
        }
    }

    return new JObject(nodes);
}

JValue<double>* parseNumber(TokenIterator &iterator, std::string const &input) {
    std::string value = input.substr(iterator.index(), iterator.length());
    double number = std::stod(value);
    return new JValue<double>(number);
}

JNode* parseNode(TokenIterator &iterator, std::string const &input) {
    if (iterator.tokenType() == OBJECT_BEGIN) {
        return parseObject(iterator, input);
    }

    if (iterator.tokenType() == VALUE_STRING) {
        return parseString(iterator, input);
    }

    if (iterator.tokenType() == VALUE_NUMBER) {
        return parseNumber(iterator, input);
    }

    if (iterator.tokenType() == LITERAL_TRUE) {
        return new JValue<bool>(true);
    }

    if (iterator.tokenType() == LITERAL_FALSE) {
        return new JValue<bool>(false);
    }
}

JNode* Parser::parse(const std::string &json) {

    Scanner scanner;
    auto tokens = scanner.scan(json);
    TokenIterator tokenIterator(tokens->begin(), tokens->end());

    JNode* node = parseNode(tokenIterator, json);
    return node;
}