#include "../include/jsp.h"

using namespace jsp;

template<>
std::string JObject::get<std::string>(std::string key) {
    auto node = static_cast<JValue<std::string>*>(m_nodes[key]);
    return node->value;
}

template<>
double JObject::get<double>(std::string key) {
    auto node = static_cast<JValue<double>*>(m_nodes[key]);
    return node->value;
}

template<>
bool JObject::get<bool>(std::string key) {
    auto node = static_cast<JValue<bool>*>(m_nodes[key]);
    return node->value;
}
