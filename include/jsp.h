#ifndef JSP_JSP_H
#define JSP_JSP_H

#include <vector>
#include <string>
#include <memory>

namespace jsp {

    enum TOKEN_TYPE {
        OBJECT_BEGIN,
        OBJECT_END,
        ARRAY_BEGIN,
        ARRAY_END,
        VALUE_STRING,
        VALUE_NUMBER,
        LITERAL_TRUE,
        LITERAL_FALSE,
        LITERAL_NULL,
        KEY,
        UNKNOWN
    };

    class Token {
    public:
        Token(unsigned int index, unsigned int length, TOKEN_TYPE tokenType)
                : index(index), length(length), tokenType(tokenType) {}

        const unsigned int index;
        const unsigned int length;
        const TOKEN_TYPE tokenType;
    };

    class Scanner {
    public:
        std::unique_ptr<std::vector<Token>> scan(std::string const &input);
    };

}

#endif
