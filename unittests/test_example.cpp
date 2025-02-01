#define BOOST_TEST_MODULE ExampleTest
#include <boost/test/included/unit_test.hpp>
#include "../Graph.hpp"

BOOST_AUTO_TEST_CASE(test_graph_bfs)
{
    Graph<int> graph{new Node{1, {new Node{2}, new Node{3, {new Node{5}, new Node{6}}}, new Node{4, {new Node{7}, new Node{8}}}}}};

    Node<int>* searchNode = graph.getNodeBFS(5);

    if (searchNode != nullptr) {
        searchNode->nodes.push_back(new Node{9});
        searchNode->nodes.push_back(new Node{10, {new Node{11}, new Node{12}}});
    }

    for (int i = 1; i <= 12; ++i) {
        BOOST_TEST(graph.containsBFS(i));
    }
}

BOOST_AUTO_TEST_CASE(test_graph_dfs)
{
    Graph<int> graph{new Node{1, {new Node{2}, new Node{3, {new Node{5}, new Node{6}}}, new Node{4, {new Node{7}, new Node{8}}}}}};

    Node<int>* searchNode = graph.getNodeDFS(5);

    if (searchNode != nullptr) {
        searchNode->nodes.push_back(new Node{9});
        searchNode->nodes.push_back(new Node{10, {new Node{11}, new Node{12}}});
    }

    for (int i = 1; i <= 12; ++i) {
        BOOST_TEST(graph.containsDFS(i));
    }
}