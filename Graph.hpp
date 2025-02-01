#pragma once

#include "Node.hpp"

template <typename T>
class Graph {
public:
    Graph();

    explicit Graph(Node<T>* head);

    Graph(const Graph<T>& rhs) = delete;
    Graph(Graph<T>&& rhs);

    Graph<T>& operator=(const Graph<T>& rhs) = delete;
    Graph<T>& operator=(Graph<T>&& rhs);

    ~Graph();

    void setNode(Node<T>* node);

    const Node<T>* getNodeDFS(T value) const&;
    Node<T>* getNodeDFS(T value) &;
    const Node<T>* getNodeBFS(T value) const&;
    Node<T>* getNodeBFS(T value) &;
    
    bool containsDFS(T value) const;
    bool containsBFS(T value) const;
    void clear();
private:
    Node<T> *head_;
};

#include "Graph.ipp"
