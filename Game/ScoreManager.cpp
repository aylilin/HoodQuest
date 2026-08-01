#include "ScoreManager.h"

#include "../DataStructures/MinHeap.h"

ScoreManager::ScoreManager()
{
}

void ScoreManager::setScore(const std::string& username, int score)
{
    scores.Insert(username, score);
}

void ScoreManager::addToScore(const std::string& username, int delta)
{
    int current = 0;

    if(scores.Contains(username))
    {
        current = scores.Get(username);
    }

    scores.Insert(username, current + delta);
}

bool ScoreManager::hasUser(const std::string& username) const
{
    return scores.Contains(username);
}

int ScoreManager::getScore(const std::string& username) const
{
    return scores.Get(username);
}

std::vector<std::pair<std::string,int>> ScoreManager::getTopPlayers(int count) const
{
    std::vector<std::pair<std::string,int>> all = scores.InorderTraversal();

   
    MinHeap<std::string> heap;

    for(const auto& entry : all)
    {
        heap.Insert(entry.first, -entry.second);
    }

    std::vector<std::pair<std::string,int>> top;

    int extracted = 0;

    while(!heap.IsEmpty() && extracted < count)
    {
        HeapNode<std::string> node = heap.ExtractMin();

        int score = -node.priority;

        top.push_back(std::make_pair(node.data, score));

        extracted++;
    }

    return top;
}

std::vector<std::pair<std::string,int>> ScoreManager::getAllScoresSorted() const
{
    return scores.InorderTraversal();
}

int ScoreManager::userCount() const
{
    return scores.Size();
}