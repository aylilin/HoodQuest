#include <iostream>
#include <ctime>
#include <cstdlib>

#include "DataStructures/Graph.h"
#include "Game/Menu.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

  
    Graph graph;

    for(int i = 0; i <= 8; i++)
    {
        graph.addVertex(i);
    }

    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 4);
    graph.addEdge(2, 4, 5);
    graph.addEdge(3, 5, 3);
    graph.addEdge(4, 5, 1);
    graph.addEdge(5, 6, 2);
    graph.addEdge(6, 7, 3);
    graph.addEdge(4, 7, 6);
    graph.addEdge(7, 8, 2);
    graph.addEdge(6, 8, 4);

    int goalVertex = 8;

    Menu menu(graph, goalVertex);

    menu.run();

    return 0;
}