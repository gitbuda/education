#include <cassert>

namespace dsa::traverse {

/// Adjacency list graph type.
using Graph = std::vector<std::vector<unsigned int>>;

/// List of visited graph nodes.
using Visited = std::vector<bool>;

/// Traverse a given graph from a given node by taking into account visited
/// info. Kernel function is called whenever a new node is visited.
/// NOTE: Passed list of visited nodes might change (side effect).
void FloodFill(
    const Graph &graph,
    Visited &visited,
    unsigned int node,
    std::function<void(unsigned int node)> kernel) {
  assert(graph.size() == visited.size());
  visited[node] = true;
  kernel(node);
  for (unsigned int i = 0; i < graph[node].size(); ++i) {
    if (!visited[graph[node][i]]) {
      FloodFill(graph, visited, graph[node][i], kernel);
    }
  }
}

} // namespace dsa::traverse
