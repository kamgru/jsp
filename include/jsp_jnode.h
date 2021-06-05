#ifndef JSP_JSP_JNODE_H
#define JSP_JSP_JNODE_H

#include <map>
#include <string>
#include <vector>

namespace jsp {

    enum JNODE_TYPE {
        OBJECT_NODE,
        ARRAY_NODE,
        VALUE_NODE,
        EMPTY_NODE
    };

    class JNode {
    public:
        JNode(JNODE_TYPE type) : type(type) {}

        virtual ~JNode() {}

        const JNODE_TYPE type;
    };

    class JEmpty : public JNode {
    public:
        JEmpty() : JNode(EMPTY_NODE) {}
    };

    template<class T>
    class JValue : public JNode {
    public:
        JValue(T value) : JNode(VALUE_NODE), value(value) {}

        const T value;
    };
}

#endif