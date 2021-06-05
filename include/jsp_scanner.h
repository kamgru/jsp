#ifndef JSP_JSP_SCANNER_H
#define JSP_JSP_SCANNER_H

#include <memory>
#include <string>
#include <vector>

#include "jsp_token.h"

namespace jsp {

    class Scanner {
    public:
        std::unique_ptr<std::vector<Token>> scan(std::string const& input);
    };
}

#endif