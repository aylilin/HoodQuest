#pragma once

#include <vector>
#include "Edge.h"

class Vertex{
public:
    int id;
    std::vector<Edge> edges;

    Vertex(int id);

    void addEdge(int destination, int weight);
};