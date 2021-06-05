#include "../include/jsp_scanner.h"
#include "Cursor.h"
#include <memory>

using namespace jsp;
using namespace jsp::internal;

Token getNextToken(Cursor& cursor);

std::unique_ptr<std::vector<Token>> Scanner::scan(const std::string& input) {

    Cursor cursor(input);
    auto tokens = std::make_unique<std::vector<Token>>();
    do {

        char currentValue = cursor.getValue();
        if (currentValue == ' '
            || currentValue == ':'
            || currentValue == ',') {
            continue;
        }

        tokens->emplace_back(getNextToken(cursor));

    } while (cursor.advance());
    return tokens;
}

Token getObjectStartToken(Cursor& cursor) {
    return { cursor.getIndex(), 1, OBJECT_BEGIN };
}

Token getObjectEndToken(Cursor& cursor) {
    return { cursor.getIndex(), 1, OBJECT_END };
}

Token getArrayStartToken(Cursor& cursor) {
    return { cursor.getIndex(), 1, ARRAY_BEGIN };
}

Token getArrayEndToken(Cursor& cursor) {
    return { cursor.getIndex(), 1, ARRAY_END };
}

Token getStringToken(Cursor& cursor) {
    unsigned int currentIndex = cursor.getIndex();
    unsigned int length = 0;
    char currentValue = cursor.getValue();
    char previousValue = currentValue;

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
            : jsp::VALUE_STRING };
}

bool isJsonNumberChar(char value) {
    return value == 'e'
           || value == 'E'
           || value == '-'
           || value == '+'
           || value == '.';
}

Token getNumberToken(Cursor& cursor) {

    unsigned int startIndex = cursor.getIndex();

    do {
        char currentValue = cursor.getValue();
        if (!std::isdigit(currentValue) && !isJsonNumberChar(currentValue)) {
            break;
        }
    } while (cursor.advance());

    cursor.rewind();

    return { startIndex, cursor.getIndex() - startIndex + 1, VALUE_NUMBER };
}

Token getNullToken(Cursor& cursor) {

    Token token { cursor.getIndex(), 4, LITERAL_NULL };
    cursor.offset(3);
    return token;
}

Token getTrueToken(Cursor& cursor) {

    Token token { cursor.getIndex(), 4, LITERAL_TRUE };
    cursor.offset(3);
    return token;
}

Token getFalseToken(Cursor& cursor) {

    Token token { cursor.getIndex(), 5, LITERAL_FALSE };
    cursor.offset(4);
    return token;
}

Token getNextToken(Cursor& cursor) {

    char currentValue = cursor.getValue();

    switch (currentValue) {
        case '{':return getObjectStartToken(cursor);
        case '}':return getObjectEndToken(cursor);
        case '[':return getArrayStartToken(cursor);
        case ']':return getArrayEndToken(cursor);
        case '"':return getStringToken(cursor);
        case 'n':
        case 'N':return getNullToken(cursor);
        case 'f':
        case 'F':return getFalseToken(cursor);
        case 't':
        case 'T':return getTrueToken(cursor);
    }

    if (std::isdigit(currentValue) || isJsonNumberChar(currentValue)) {
        return getNumberToken(cursor);
    }

    return { cursor.getIndex(), 0, UNKNOWN };
}