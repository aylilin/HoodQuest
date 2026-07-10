#pragma once

#include <vector>
#include "../Models/Vertex.h"

class Graph{
private:
    std::vector<Vertex> vertices;
    int FindVertexIndex(int id);

public:
    Graph();
    
    void addVertex(int id);
    void addEdge(int from, int to, int weight);
    bool containsVertex(int id);
    Vertex* getVertex(int id);
    std::vector<Edge> getNeighbors(int id);
    void printGraph();
};