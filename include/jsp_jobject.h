#ifndef JSP_JSP_JOBJECT_H
#define JSP_JSP_JOBJECT_H

#include <string>
#include <vector>
#include "jsp_jnode.h"

namespace jsp {

    class JObject : public JNode {
    public:
        JObject(std::map<std::string,
                JNode*> nodes)
                : JNode(OBJECT_NODE),
                  m_nodes(nodes) {}

        ~JObject();

        template<class T>
        const T& get(std::string key);

    private:
        std::map<std::string, JNode*> m_nodes;
    };
}

#endif