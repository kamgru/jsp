#ifndef JSP_CURSOR_H
#define JSP_CURSOR_H

#include <string>

namespace jsp {

    class Cursor {
    public:
        Cursor(std::string const &input);
        bool advance();
        char getValue();
        unsigned int getIndex();
        char peekNextValue();
    private:
        unsigned int m_index;
        const std::string& m_input;
    };
}


#endif
