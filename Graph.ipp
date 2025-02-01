#include "Graph.hpp"

#include <queue>
#include <stack>

template <typename T>
Graph<T>::Graph() {
    head_ = new Node{T{0}};
}

template <typename T>
Graph<T>::Graph(Node<T>* head) {
    head_ = new Node{T{0}};
    head_->nodes.push_back(head);
}

template <typename T>
Graph<T>::Graph(Graph<T>&& rhs) {
    head_ = rhs.head_;
    rhs.head_ = nullptr;
}

template <typename T>
Graph<T>& Graph<T>::operator=(Graph<T>&& rhs) {
    if (this == &rhs) {
        return *this;
    }

    head_ = rhs.head_;
    rhs.head_ = nullptr;

    return *this;
}

template <typename T>
Graph<T>::~Graph() {
    clear();
}

template <typename T>
void Graph<T>::setNode(Node<T>* node) {
    if (head_ == nullptr) {
        head_ = new Node{T{0}};
    }
    head_->nodes.push_back(node);
}

template <typename T>
const Node<T>* Graph<T>::getNodeDFS(T value) const& {
    std::stack<Node<T>*> next;

    next.push(head_);

    while (!next.empty()) {
        Node<T>* node = next.top();
        
        if (node != head_ && node->value == value) {
            return node;
        }
        
        next.pop();

        for (Node<T>* subNode: node->nodes) {
            next.push(subNode);
        }
    }

    return nullptr;
}

template <typename T>
Node<T>* Graph<T>::getNodeDFS(T value) & {
    const Node<T> *node = const_cast<const Graph<T>*>(this)->getNodeDFS(value);
    return const_cast<Node<T>*>(node);
}

template <typename T>
const Node<T>* Graph<T>::getNodeBFS(T value) const & {
    std::queue<Node<T>*> next;

    next.push(head_);

    while (!next.empty()) {
        Node<T>* node = next.front();
        next.pop();

        if (node != head_ && node->value == value) {
            return node;
        }

        for (Node<T>* subNode : node->nodes) {
            next.push(subNode);
        }
    }
    return nullptr;
}

template <typename T>
Node<T>* Graph<T>::getNodeBFS(T value) & {
    const Node<T>* node = const_cast<const Graph<T>*>(this)->getNodeBFS(value);
    return const_cast<Node<T>*>(node);
}

template <typename T>
bool Graph<T>::containsDFS(T value) const {
    return getNodeDFS(value) != nullptr;
}

template <typename T>
bool Graph<T>::containsBFS(T value) const {
    return getNodeBFS(value) != nullptr;
}

template <typename T>
void Graph<T>::clear() {
    Node<T>* parrent = head_;
    for (Node<T>* node: head_->nodes) {
        if (node == nullptr)
            continue;
        head_ = node;
        clear();
    }

    parrent->nodes.clear();

    delete parrent;
    parrent = nullptr;
}