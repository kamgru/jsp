#ifndef JSP_CURSOR_H
#define JSP_CURSOR_H

#include <string>

namespace jsp { namespace internal {

    class Cursor {
    public:
        Cursor(std::string const &input);
        bool advance();
        void rewind();
        bool offset(unsigned int value);
        char getValue();
        unsigned int getIndex();
        char peekNextValue();
    private:
        unsigned int m_index;
        const std::string& m_input;
    };
}}

#endif