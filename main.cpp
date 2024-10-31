#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <set>
#include <chrono> // For timing

using namespace std;

typedef pair<int, int> Edge; // {cost, node}
typedef vector<vector<Edge>> Graph;

// Initialize the graph with V nodes
Graph createGraph(int V) {
    return Graph(V);
}

// Add edges to make the graph connected and add extra random edges
void addConnectedEdges(Graph &graph, int V, int extraEdges, int maxWeight = 10) {
    srand(100); // Set seed for reproducibility
    vector<int> visited(V, false);
    visited[0] = true;

    // Add edges to form a spanning tree
    for (int i = 1; i < V; ++i) {
        int u = rand() % i;
        int v = i;
        int weight = rand() % maxWeight + 1;
        graph[u].push_back({weight, v});
        graph[v].push_back({weight, u});
        visited[v] = true;
    }

    // Add extra random edges
    for (int i = 0; i < extraEdges; ++i) {
        int u = rand() % V;
        int v = rand() % V;
        int weight = rand() % maxWeight + 1;
        if (u != v) {
            graph[u].push_back({weight, v});
            graph[v].push_back({weight, u});
        }
    }
}

int prim_with_heap(const Graph &graph, int start_node, int &heap_operations) {
    int V = graph.size();
    vector<int> min_cost(V, numeric_limits<int>::max());
    vector<bool> visited(V, false);
    min_cost[start_node] = 0;
    int totalCost = 0;
    set<Edge> heap_edges;
    heap_edges.insert({0, start_node});

    while (!heap_edges.empty()) {
        auto it = heap_edges.begin();
        int minimum_weight = it->first;
        int v = it->second;
        heap_edges.erase(it);
        heap_operations++;

        if (visited[v]) continue;
        visited[v] = true;
        totalCost += minimum_weight;

        for (const Edge &edge : graph[v]) {
            int weight = edge.first;
            int node = edge.second;
            if (!visited[node] && weight < min_cost[node]) {
                heap_edges.erase({min_cost[node], node});
                min_cost[node] = weight;
                heap_edges.insert({weight, node});
                heap_operations += 2;
            }
        }
    }
    return totalCost;
}

int prim_with_array(const Graph &graph, int start_node, int &array_operations) {
    int V = graph.size();
    vector<int> min_cost(V, numeric_limits<int>::max());
    vector<bool> visited(V, false);
    min_cost[start_node] = 0;
    int totalCost = 0;

    for (int visited_count = 0; visited_count < V; ++visited_count) {
        int v = -1;
        for (int i = 0; i < V; ++i) {
            array_operations++;
            if (!visited[i] && (v == -1 || min_cost[i] < min_cost[v])) {
                v = i;
            }
        }
        if (v == -1) break;

        visited[v] = true;
        totalCost += min_cost[v];

        for (const Edge &edge : graph[v]) {
            int weight = edge.first;
            int node = edge.second;
            if (!visited[node] && weight < min_cost[node]) {
                min_cost[node] = weight;
                array_operations++;
            }
        }
    }
    return totalCost;
}

int main() {
    int V = 1000, E = 3000;
    Graph graph = createGraph(V);
    addConnectedEdges(graph, V, E);

    // Heap-based Prim's Algorithm
    int heap_operations = 0;
    auto start = chrono::high_resolution_clock::now();
    int heap_cost = prim_with_heap(graph, 0, heap_operations);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> heap_duration = end - start;

    // Array-based Prim's Algorithm
    int array_operations = 0;
    start = chrono::high_resolution_clock::now();
    int array_cost = prim_with_array(graph, 0, array_operations);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> array_duration = end - start;

    // Results
    cout << "Heap-based MST cost: " << heap_cost << ", Time: " << heap_duration.count()
         << "s, Operations: " << heap_operations << endl;
    cout << "Array-based MST cost: " << array_cost << ", Time: " << array_duration.count()
         << "s, Operations: " << array_operations << endl;

    return 0;
}
