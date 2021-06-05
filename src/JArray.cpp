#include "../include/jsp.h"

using namespace jsp;

template<>
const std::string& JArray::at<std::string>(unsigned int index) {
    auto node = static_cast<JValue<std::string>*>(m_nodes[index]);
    return node->value;
}

template<>
const double& JArray::at<double>(unsigned int index) {
    auto node = static_cast<JValue<double>*>(m_nodes[index]);
    return node->value;
}

template<>
const bool& JArray::at<bool>(unsigned int index) {
    auto node = static_cast<JValue<bool>*>(m_nodes[index]);
    return node->value;
}

template<>
const JObject& JArray::at<JObject>(unsigned int index) {
    auto node = static_cast<JObject*>(m_nodes[index]);
    return *node;
}

template<>
const JEmpty& JArray::at<JEmpty>(unsigned int index) {
    auto node = static_cast<JEmpty*>(m_nodes[index]);
    return *node;
}