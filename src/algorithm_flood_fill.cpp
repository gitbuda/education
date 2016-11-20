#include "include/using_iostream.hpp"

#include <vector>
#include <functional>

using graph_t = std::vector<std::vector<int>>;
using visited_t = std::vector<bool>;

void flood_fill(const graph_t& graph, visited_t& visited,
                int node, std::function<void (int node)> kernel)
{
    visited[node] = true;
    kernel(node);
    for (int i = 0; i < graph[node].size(); ++i)
    {
        if (!visited[graph[node][i]])
        {
            flood_fill(graph, visited, graph[node][i], kernel);
        }
    } 
}

int main()
{
    graph_t graph = {
        {1},
        {0, 2, 3, 4},
        {1},
        {1},
        {1},
        {6},
        {5}
    };
    
    for (int i = 0; i < graph.size(); ++i)
    {
        visited_t visited = {0, 0, 0, 0, 0, 0, 0};
        cout << "Segment in which is node " << i << " also contains:" << endl;
        flood_fill(graph, visited, i, [](int node) {
            cout << node << endl;
        });
        cout << endl;
    }

    return 0;
}
