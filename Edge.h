#pragma once
#include <iostream>

class Edge {
public:
    int source;
    int destination;
    int weight;

    Edge();
    Edge(int src, int dest, int w);

    // Define the equality operator
    bool operator==(const Edge& other) const {
        return (source == other.source && destination == other.destination && weight == other.weight);
    }
};