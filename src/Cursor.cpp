#include "Cursor.h"

using namespace jsp;

Cursor::Cursor(const std::string &input)
    : m_input(input), m_index(0) {
}

bool Cursor::advance() {
    m_index += 1;
    return m_index < m_input.length();
}

char Cursor::getValue() {
    return m_input[m_index];
}

unsigned int Cursor::getIndex() {
    return m_index;
}

char Cursor::peekNextValue() {
    for (unsigned int index = m_index + 1; index < m_input.length(); index++) {
        if (m_input[index] != ' ') {
            return m_input[index];
        }
    }

    return '\0';
}

bool Cursor::offset(unsigned int value) {
    m_index += value;
    return m_index + value > m_input.length();
}