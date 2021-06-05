#ifndef JSP_JSP_PARSER_H
#define JSP_JSP_PARSER_H

#include "jsp_jnode.h"
#include "jsp_jarray.h"
#include "jsp_jobject.h"

namespace jsp {

    class Parser {
    public:
        JObject* parseObject(std::string const& json);
        JArray* parseArray(std::string const& json);
        JNode* parse(std::string const& json);
    };
}

#endif