#include "Vertex.h"

Vertex::Vertex(int id){
    this -> id = id;
}

void Vertex::addEdge(int destination, int weight){
    edges.push_back(Edge(destination, weight));
}
