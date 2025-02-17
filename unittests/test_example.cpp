#define BOOST_TEST_MODULE ExampleTest
#include <boost/test/included/unit_test.hpp>
#include <string>

using namespace std::literals::string_literals;

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

    for (int i = 13; i <= 50; ++i) {
        BOOST_TEST(!graph.containsBFS(i));
        Node<int>* searchNode = graph.getNodeDFS(i - 12);
        searchNode->nodes.push_back(new Node{i});
        BOOST_TEST(graph.containsDFS(i));
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

    for (int i = 13; i <= 50; ++i) {
        BOOST_TEST(!graph.containsDFS(i));
        Node<int>* searchNode = graph.getNodeDFS(i - 12);
        searchNode->nodes.push_back(new Node{i});
        BOOST_TEST(graph.containsDFS(i));
    }
}

BOOST_AUTO_TEST_CASE(test_graph_bfs_string)
{
    Graph<std::string> graph{new Node{"a"s, {new Node{"b"s}, new Node{"c"s, {new Node{"d"s}, new Node{"e"s}}}, new Node{"f"s, {new Node{"g"s}, new Node{"h"s}}}}}};

    Node<std::string>* searchNode = graph.getNodeBFS("h");

    if (searchNode != nullptr) {
        searchNode->nodes.push_back(new Node{"i"s});
        searchNode->nodes.push_back(new Node{"j"s, {new Node{"k"s}, new Node{"l"s}}});
    }

    for (char i = 'a'; i <= 'l'; ++i) {
        std::string test;
        test += i;
        BOOST_TEST(graph.containsBFS(test));
    }

    for (char i = 'm'; i <= 'z'; ++i) {
        std::string test;
        test += i;
        BOOST_TEST(!graph.containsBFS(test));
        std::string test2;
        test2 += static_cast<char>(i - 12);
        Node<std::string>* searchNode = graph.getNodeDFS(std::to_string(i - 12));
        searchNode->nodes.push_back(new Node{test});
        BOOST_TEST(graph.containsDFS(test));
    }
}