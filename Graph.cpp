#include "Graph.h"
#include <vector>
#include <algorithm>
#include <iostream>
using  namespace std;
Graph::Graph(int vertices, int edgesCount) : numVertices(vertices) {
    edges.reserve(edgesCount); // Reserve space for edges
}

//Graph::~Graph() {
    // No need to manually delete edges since we're using vector
//}
Graph::Graph(int vertices) : numVertices(vertices) {
    // No need to reserve edges since we don't know the count yet
}
void Graph::addEdges(int src, int dest, int w) {
    edges.push_back(Edge(src, dest, w)); // Add edge to vector
}

void Graph::karuskalMST() {
    // Sort edges based on weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
        });

    Disjoint ds(numVertices);
    mstEdges.clear(); // Clear previous MST edges

    for (const auto& currentEdge : edges) {
        int root1 = ds.find(currentEdge.source);
        int root2 = ds.find(currentEdge.destination);

        // If the edge doesn't form a cycle, include it in MST
        if (root1 != root2) {
            mstEdges.push_back(currentEdge); // Add to MST
            ds.unionSets(root1, root2);
        }
    }
}