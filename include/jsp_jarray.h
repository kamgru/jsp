#ifndef JSP_JSP_JARRAY_H
#define JSP_JSP_JARRAY_H

#include <vector>
#include "jsp_jnode.h"

namespace jsp {

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
}

#endif