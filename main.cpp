#include "Graph.hpp"
#include "Node.hpp"

#include <iostream>

int main() {
    Graph<int> graph{new Node{1, {new Node{2}, new Node{3, {new Node{5}, new Node{6}}}, new Node{4, {new Node{7}, new Node{8}}}}}};

    Node<int>* searchNode = graph.getNodeDFS(5);

    if (searchNode != nullptr) {
        searchNode->nodes.push_back(new Node{9});
        searchNode->nodes.push_back(new Node{10, {new Node{11}, new Node{12}}});
    }

    searchNode = graph.getNodeBFS(12);

    if (searchNode != nullptr) {
        searchNode->nodes.push_back(new Node{13});
        searchNode->nodes.push_back(new Node{14, {new Node{15}, new Node{14}}});
    }

    return 0;
}