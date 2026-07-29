#include "Dijkstra.h"

#include "../DataStructures/MinHeap.h"

#include <map>
#include <algorithm>
#include <climits>

std::vector<int> Dijkstra::shortestPath(
    Graph& graph,
    int start,
    int goal)
{
    MinHeap<int> heap;

    std::map<int,int> distance;

    std::map<int,int> parent;

    std::map<int,bool> visited;

    heap.Insert(start,0);

    distance[start]=0;

    while(!heap.IsEmpty())
    {
        HeapNode<int> node=
            heap.ExtractMin();

        int current=node.data;

        if(visited[current])
            continue;

        visited[current]=true;

        if(current==goal)
            break;

        std::vector<Edge> neighbors=
            graph.getNeighbors(current);

        for(const Edge& edge : neighbors)
        {
            int next=edge.destination;

            int newDistance=
                distance[current]+edge.weight;

            if(!distance.count(next) ||
               newDistance<distance[next])
            {
                distance[next]=newDistance;

                parent[next]=current;

                heap.Insert(next,newDistance);
            }
        }
    }

    if(!distance.count(goal))
        return {};

    std::vector<int> path;

    int current=goal;

    while(current!=start)
    {
        path.push_back(current);

        current=parent[current];
    }

    path.push_back(start);

    std::reverse(path.begin(),path.end());

    return path;
}

int Dijkstra::pathCost(
    Graph& graph,
    const std::vector<int>& path)
{
    if(path.empty())
        return 0;

    int total=0;

    for(size_t i=0;i<path.size()-1;i++)
    {
        std::vector<Edge> neighbors=
            graph.getNeighbors(path[i]);

        for(const Edge& edge : neighbors)
        {
            if(edge.destination==path[i+1])
            {
                total+=edge.weight;
                break;
            }
        }
    }

    return total;
}