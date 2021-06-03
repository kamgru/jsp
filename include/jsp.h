#ifndef JSP_JSP_H
#define JSP_JSP_H

#include <vector>
#include <map>
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

    enum JNODE_TYPE {
        OBJECT_NODE,
        ARRAY_NODE,
        VALUE_NODE,
        NULL_NODE
    };

    class JNode {
    public:
        JNode(JNODE_TYPE type) : type(type) {}
        virtual ~JNode() {}

        const JNODE_TYPE type;
    };

    class JObject : public JNode {
    public:
        JObject(std::map<std::string, JNode*> nodes)
                : JNode(OBJECT_NODE),
                  m_nodes(nodes) {}

        ~JObject() {
            for (auto pair : m_nodes) {
                delete pair.second;
            }
            m_nodes.clear();
        }

        JNode *get(std::string key) {
            return m_nodes.at(key);
        }

        template<class T>
        T get(std::string key);

    private:
        std::map<std::string, JNode*> m_nodes;
    };

    template<class T>
    class JValue : public JNode {
    public:
        JValue(T value) : JNode(VALUE_NODE), value(value) {}

        const T value;
    };

    class JArrayNode : public JNode {
    public:
        JArrayNode() : JNode(ARRAY_NODE) {}
    };

    class Parser {
    public:
        JNode *parse(std::string const &json);
    };
}

#endif