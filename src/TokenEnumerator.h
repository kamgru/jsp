#ifndef JSP_TOKENENUMERATOR_H
#define JSP_TOKENENUMERATOR_H

#include <vector>
#include "../include/jsp_token.h"

namespace jsp { namespace internal {

    class TokenEnumerator {
    public:
        TokenEnumerator(std::vector<jsp::Token>::iterator begin,
                        std::vector<jsp::Token>::iterator end)
                : m_iterator(begin),
                  m_end(end) {}

        bool MoveNext() {
            if (m_iterator != m_end) {
                m_iterator++;
                return true;
            }

            return false;
        }

        jsp::TOKEN_TYPE tokenType() { return m_iterator->tokenType; }

        unsigned int index() { return m_iterator->index; }

        unsigned int length() { return m_iterator->length; }

    private:
        std::vector<jsp::Token>::iterator m_iterator;
        std::vector<jsp::Token>::iterator m_end;
    };
}}

#endif