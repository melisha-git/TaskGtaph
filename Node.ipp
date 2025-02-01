#include "Node.hpp"

template <typename T>
Node<T>::Node(T newValue, std::vector<Node<T> *> newNodes) 
    : value(newValue), nodes(newNodes) {}

