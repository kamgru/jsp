#include "../include/jsp_jobject.h"
#include "../include/jsp_jarray.h"

using namespace jsp;

JObject::~JObject()  {
    for (auto pair : m_nodes) {
        delete pair.second;
    }
    m_nodes.clear();
}

template<>
const std::string& JObject::get<std::string>(std::string key) {
    auto node = static_cast<JValue<std::string>*>(m_nodes[key]);
    return node->value;
}

template<>
const double& JObject::get<double>(std::string key) {
    auto node = static_cast<JValue<double>*>(m_nodes[key]);
    return node->value;
}

template<>
const bool& JObject::get<bool>(std::string key) {
    auto node = static_cast<JValue<bool>*>(m_nodes[key]);
    return node->value;
}

template<>
const JObject& JObject::get<JObject>(std::string key) {
    auto node = static_cast<JObject*>(m_nodes[key]);
    return *node;
}

template<>
const JEmpty& JObject::get<JEmpty>(std::string key) {
    auto node = static_cast<JEmpty*>(m_nodes[key]);
    return *node;
}

template<>
const JArray& JObject::get<JArray>(std::string key) {
    auto node = static_cast<JArray*>(m_nodes[key]);
    return *node;
}