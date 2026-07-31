#pragma once

#include "../DataStructures/Graph.h"
#include <vector>

class AStar
{
public:

    static std::vector<int> shortestPath(
        Graph& graph,
        int start,
        int goal
    );

    static int pathCost(
        Graph& graph,
        const std::vector<int>& path
    );
};