#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <string>

#include "DataStructures/Graph.h"
#include "IO/FileManager.h"
#include "Game/Menu.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Graph graph;

    if(!FileManager::loadGraph("Maps/graph.txt", graph))
    {
        std::cerr << "Error: could not load the map from Maps/graph.txt." << std::endl;
        return 1;
    }

    std::map<int,std::string> labels = {
        {0,  "A"}, {1,  "B"}, {2,  "C"}, {3,  "D"}, {4,  "E"},
        {5,  "F"}, {6,  "G"}, {7,  "J"}, {8,  "K"}, {9,  "M"},
        {10, "O"}, {11, "P"}, {12, "Q"}, {13, "R"}, {14, "S"},
        {15, "T"}, {16, "U"}, {17, "V"}, {18, "W"}
    };

   
    int goalVertex = 17;

    Menu menu(graph, goalVertex, labels);

    menu.run();

    return 0;
}