#include "Graph.h"

#include <iostream>

using namespace std;

Graph::Graph(){}

int Graph::FindVertexIndex(int id){
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].id == id){
            return i;
        }
    }
    return -1;
}

bool Graph::containsVertex(int id){
    return FindVertexIndex(id) != -1;
}

void Graph::addVertex(int id){
    if (containsVertex(id)){
        return;
    }
    vertices.push_back(Vertex(id));
}

void Graph::addEdge(int from, int to, int weight){
    int fromIndex = FindVertexIndex(from);
    int toIndex = FindVertexIndex(to);

    if (fromIndex == -1 || toIndex == -1){
        return;
    }
    vertices[fromIndex].addEdge(to, weight);
    vertices[toIndex].addEdge(from, weight);
}

Vertex* Graph::getVertex(int id)
{
    int index = FindVertexIndex(id);
    if(index==-1){
        return nullptr;
    }
    return &vertices[index];
}

std::vector<Edge> Graph::getNeighbors(int id)
{
    Vertex* vertex = getVertex(id);
    if(vertex==nullptr){
        return {};
    }
    return vertex->edges;
}

void Graph::printGraph()
{
    cout<<"----------- Graph -----------"<<endl;
    for(Vertex &vertex : vertices){
        cout<<vertex.id<<" -> ";
        for(Edge &edge : vertex.edges){
            cout <<"(" << edge.destination << "," <<edge.weight << ")";
        }
        cout<<endl;
    }
    cout<<"-----------------------------"<<endl;
}

