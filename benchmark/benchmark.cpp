#include <benchmark/benchmark.h>
#include <memory>
#include "../Graph.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <vector>
#include <random>

// Определение графа с помощью Boost Graph Library
using graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
using Vertex = boost::graph_traits<graph>::vertex_descriptor;

Graph<int> graph1;
graph graph2;

// Функция для создания графа с N вершинами
void setupGraphBoost(int numNodes) {
    for (int i = 0; i < numNodes; ++i) {
        boost::add_vertex(graph2);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, numNodes - 1);

    for (int i = 0; i < numNodes; ++i) {
        int target = dist(gen);
        if (i != target) {
            boost::add_edge(i, target, graph2);
        }
    }
}

template <typename T>
void setupGraph(int numNodes) {
    graph1.setNode(new Node<T>(0));
    int currentSize = 0;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 1; i < numNodes; ++i) {
        std::uniform_int_distribution<> dist(0, currentSize);
        int target = dist(gen);
        Node<T>* n = graph1.getNodeBFS(target);
        n->nodes.push_back(new Node(i));
        ++currentSize;
    }
}

// Инициализация графов перед запуском бенчмарков
void initializeGraphs(int numNodes) {
    setupGraph<int>(numNodes);
    setupGraphBoost(numNodes);
}

// Бенчмарк DFS с Boost
static void BM_Boost_DFS(benchmark::State& state) {
    std::vector<boost::default_color_type> color_map(boost::num_vertices(graph2));

    for (auto _ : state) {
        boost::depth_first_search(graph2, boost::visitor(boost::default_dfs_visitor()).color_map(color_map.data()));
        benchmark::DoNotOptimize(color_map);
    }
}

// Бенчмарк BFS с Boost
static void BM_Boost_BFS(benchmark::State& state) {
    std::vector<boost::default_color_type> color_map(boost::num_vertices(graph2));

    for (auto _ : state) {
        boost::breadth_first_search(graph2, 0, boost::visitor(boost::default_bfs_visitor()).color_map(color_map.data()));
        benchmark::DoNotOptimize(color_map);
    }
}

// Бенчмарк DFS
static void BM_Graph_DFS(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(graph1.containsDFS(state.range(0) - 1));
    }
}

// Бенчмарк BFS
static void BM_Graph_BFS(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(graph1.containsBFS(state.range(0) - 1));
    }
}

// Регистрируем бенчмарки с разными размерами графа
BENCHMARK(BM_Graph_DFS)->Range(8, 8 << 10);
BENCHMARK(BM_Boost_DFS)->Range(8, 8 << 10);
BENCHMARK(BM_Graph_BFS)->Range(8, 8 << 10);
BENCHMARK(BM_Boost_BFS)->Range(8, 8 << 10);

int main(int argc, char** argv) {
    // Инициализация графов перед запуском бенчмарков
    initializeGraphs(8 << 10); // Инициализация графов с максимальным размером

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
}