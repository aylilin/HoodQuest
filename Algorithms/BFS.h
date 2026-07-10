#pragma once

#include "../DataStructures/Graph.h"
#include <vector>

class BFS
{
public:

    // پیدا کردن کوتاه‌ترین مسیر بین دو رأس
    static std::vector<int> ShortestPath(
        Graph& graph,
        int start,
        int goal
    );

    // حرکت بعدی گرگ
    static int NextMove(
        Graph& graph,
        int wolfPosition,
        int playerPosition
    );
};