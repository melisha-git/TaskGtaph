#pragma once

#include <vector>

template <typename T>
struct Node {
    T value;
    std::vector<Node<T> *> nodes;

    explicit Node(T newValue, std::vector<Node<T> *> newNodes = {});
};

#include "Node.ipp"