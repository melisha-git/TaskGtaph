#include "Graph.hpp"
#include "Node.hpp"

#include <iostream>
#include <vector>
#include <random>

template <typename T>
void setupGraph(int numNodes, Graph<int>& graph) {
    graph.setNode(new Node<T>(0));
    int currentSize = 0;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 1; i < numNodes; ++i) {
        std::uniform_int_distribution<> dist(0, currentSize);
        int target = dist(gen);
        Node<T>* n = graph.getNodeBFS(target);
        n->nodes.push_back(new Node(i));
        ++currentSize;
    }
}

void initializeGraphs(int numNodes, Graph<int>& graph) {
    setupGraph<int>(numNodes, graph);
}

int main() {
    Graph<int> graph;
    initializeGraphs(8 << 10, graph);
    return 0;
}