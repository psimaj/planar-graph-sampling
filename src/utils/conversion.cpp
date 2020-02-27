#include <map>

#include "conversion.h"

std::vector<std::vector<int>> halfGraphToAdjacencyList(RootedHalfGraph &graph) {
    std::map<HalfVertexPtr, int> vertexIndex;
    for (size_t i = 0; i < graph.vertices.size(); i++) {
        vertexIndex[graph.vertices[i]] = i + 1;
    }
    std::vector<std::vector<int>> adj(graph.vertices.size() + 1);
    for (HalfEdgePtr edge : graph.edges) {
        int a = vertexIndex[edge->origin];
        int b = vertexIndex[edge->other->origin];
        adj[a].push_back(b);
    }
    return adj;
}