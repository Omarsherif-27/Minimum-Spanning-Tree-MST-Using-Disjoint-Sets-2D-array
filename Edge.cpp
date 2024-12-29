#include "Edge.h"

Edge::Edge() {
    source = 0;
    destination = 0;
    weight = 0;
}

Edge::Edge(int src = 0, int dest = 0, int w = 0) {
    source = src;
    destination = dest;
    weight = w;
}