#include "BFS.h"

#include "../DataStructures/Queue.h"

#include <map>
#include <algorithm>

std::vector<int> BFS::shortestPath(Graph& graph, int start, int goal)
{
    Queue<int> q;

    std::map<int,bool> visited;

    std::map<int,int> parent;

    visited[start] = true;

    q.Enqueue(start);

    while(!q.IsEmpty())
    {
        int current = q.Front();

        q.Dequeue();

        if(current == goal)
            break;

        std::vector<Edge> neighbors =
            graph.getNeighbors(current);

        for(const Edge& edge : neighbors)
        {
            int next = edge.destination;

            if(!visited[next])
            {
                visited[next] = true;

                parent[next] = current;

                q.Enqueue(next);
            }
        }
    }

    if(!visited[goal])
        return {};

    std::vector<int> path;

    int current = goal;

    while(current != start)
    {
        path.push_back(current);

        current = parent[current];
    }

    path.push_back(start);

    std::reverse(path.begin(), path.end());

    return path;
}

int BFS::nextMove(
    Graph& graph,
    int wolfPosition,
    int playerPosition)
{
    std::vector<int> path =
        shortestPath(
            graph,
            wolfPosition,
            playerPosition
        );

    if(path.size() <= 1)
        return wolfPosition;

    return path[1];
}