#include "AStar.h"

#include "../DataStructures/Queue.h"
#include "../DataStructures/MinHeap.h"

#include <map>
#include <algorithm>

namespace
{ 
    std::map<int,int> computeHeuristic(Graph& graph, int goal)
    {
        std::map<int,int> hopDistance;

        std::map<int,bool> visited;

        Queue<int> q;

        visited[goal] = true;

        hopDistance[goal] = 0;

        q.Enqueue(goal);

        while(!q.IsEmpty())
        {
            int current = q.Front();

            q.Dequeue();

            std::vector<Edge> neighbors = graph.getNeighbors(current);

            for(const Edge& edge : neighbors)
            {
                int next = edge.destination;

                if(!visited[next])
                {
                    visited[next] = true;

                    hopDistance[next] = hopDistance[current] + 1;

                    q.Enqueue(next);
                }
            }
        }

        return hopDistance;
    }
}

std::vector<int> AStar::shortestPath(
    Graph& graph,
    int start,
    int goal)
{
    std::map<int,int> heuristic = computeHeuristic(graph, goal);

    MinHeap<int> openSet;

    std::map<int,int> gScore;

    std::map<int,int> parent;

    std::map<int,bool> closed;

    gScore[start] = 0;

    int hStart = heuristic.count(start) ? heuristic[start] : 0;

    openSet.Insert(start, hStart);

    while(!openSet.IsEmpty())
    {
        HeapNode<int> node = openSet.ExtractMin();

        int current = node.data;

        if(closed[current])
            continue;

        closed[current] = true;

        if(current == goal)
            break;

        std::vector<Edge> neighbors = graph.getNeighbors(current);

        for(const Edge& edge : neighbors)
        {
            int next = edge.destination;

            int tentativeG = gScore[current] + edge.weight;

            if(!gScore.count(next) || tentativeG < gScore[next])
            {
                gScore[next] = tentativeG;

                parent[next] = current;

                int h = heuristic.count(next) ? heuristic[next] : 0;

                openSet.Insert(next, tentativeG + h);
            }
        }
    }

    if(!gScore.count(goal))
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

int AStar::pathCost(
    Graph& graph,
    const std::vector<int>& path)
{
    if(path.empty())
        return 0;

    int total = 0;

    for(size_t i = 0; i < path.size() - 1; i++)
    {
        std::vector<Edge> neighbors = graph.getNeighbors(path[i]);

        for(const Edge& edge : neighbors)
        {
            if(edge.destination == path[i+1])
            {
                total += edge.weight;

                break;
            }
        }
    }

    return total;
}