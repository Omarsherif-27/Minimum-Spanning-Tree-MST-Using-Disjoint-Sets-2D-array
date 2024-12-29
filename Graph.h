#pragma once
#include "Edge.h"
#include "Disjoint.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
private:
    std::vector<Edge> edges; // Use vector instead of raw array
    int numVertices;
    std::vector<Edge> mstEdges; // Store MST edges

public:
    Graph(int vertices);
    Graph(int vertices, int edgesCount);
    // ~Graph();

    void addEdges(int src, int dest, int w);
    void karuskalMST();

    // Accessor methods
    int getNumVertices() const { return numVertices; }
    int getNumEdges() const { return edges.size(); }
    const std::vector<Edge>& getEdges() const { return edges; }
    const std::vector<Edge>& getMstEdges() const { return mstEdges; } // New accessor for MST edges
};
