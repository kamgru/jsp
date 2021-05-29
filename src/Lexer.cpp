#include "../include/jsp.h"
#include "Cursor.h"
#include <memory>

using namespace jsp;

Token getNextToken(Cursor &cursor) {
    char currentValue = cursor.getValue();
    unsigned int currentIndex = cursor.getIndex();

    if (currentValue == '{') {
        Token token{currentIndex, 1, OBJECT_BEGIN};
        cursor.advance();
        return token;
    }

    if (currentValue == '}') {
        Token token{currentIndex, 1, OBJECT_END};
        cursor.advance();
        return token;
    }

    if (currentValue == '[') {
        Token token{currentIndex, 1, ARRAY_BEGIN};
        cursor.advance();
        return token;
    }

    if (currentValue == ']') {
        Token token{currentIndex, 1, ARRAY_END};
        cursor.advance();
        return token;
    }

    if (currentValue == '"') {

        char previousValue = currentValue;
        unsigned int length;

        while (cursor.advance()) {

            currentValue = cursor.getValue();

            if (currentValue == '"' && previousValue != '\\') {
                length = cursor.getIndex() - currentIndex - 1;
                break;
            }

            previousValue = currentValue;
        }

        char nextValue = cursor.peekNextValue();

        return {
                currentIndex + 1,
                length,
                nextValue == ':'
                    ? jsp::KEY
                    : jsp::VALUE_STRING};
    }

    return {currentIndex, 0, UNKNOWN};
}

std::unique_ptr<std::vector<Token>> Lexer::scan(const std::string &input) {
    Cursor cursor(input);
    auto tokens = std::make_unique<std::vector<Token>>();
    do {

        if (cursor.getValue() == ' ') {
            continue;
        }

        if (cursor.getValue() == ':') {
            continue;
        }

        tokens->emplace_back(getNextToken(cursor));

    } while (cursor.advance());
    return tokens;
}