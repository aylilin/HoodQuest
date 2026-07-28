#pragma once

#include "../DataStructures/Graph.h"
#include <vector>

class BFS
{
public:

    static std::vector<int> shortestPath(Graph& graph, int start, int goal);

    static int nextMove(Graph& graph, int wolfPosition, int playerPosition);
};