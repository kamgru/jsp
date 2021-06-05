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
        std::unique_ptr<std::vector<Token>> scan(std::string const& input);
    };

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

    class JObject : public JNode {
    public:
        JObject(std::map<std::string, JNode*> nodes)
                : JNode(OBJECT_NODE),
                  m_nodes(nodes) {}

        ~JObject();

        template<class T>
        const T& get(std::string key);

    private:
        std::map<std::string, JNode*> m_nodes;
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

    class JArray;


    class JArray : public JNode {
    public:

        class Proxy {
        public:
            Proxy(JArray* jArray, unsigned int index)
                    : m_jArray(jArray), m_index(index) {}

            template<class T>
            operator T() {
                return m_jArray->at<T>(m_index);
            }

        private:
            unsigned int m_index;
            JArray* m_jArray;
        };


        JArray(std::vector<JNode*> nodes)
                : JNode(ARRAY_NODE), m_nodes(nodes) {}

        ~JArray() {
            for (auto node : m_nodes) {
                delete node;
            }
            m_nodes.clear();
        }

        template<class T>
        const T& at(unsigned int index);

        Proxy operator[](unsigned int index) { return Proxy(this, index); };

    private:
        std::vector<JNode*> m_nodes;
    };




    class Parser {
    public:
        JObject* parseObject(std::string const& json);
        JArray* parseArray(std::string const& json);
        JNode* parse(std::string const& json);
    };
}

#endif