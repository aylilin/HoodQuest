#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
}

void ScoreManager::setScore(const std::string& username, int score)
{
    scores.Insert(username, score);

    // Keep the ranking heap in sync the moment the score changes,
    // instead of rebuilding it whenever the leaderboard is read.
    ranking.Insert(username, score);
}

void ScoreManager::addToScore(const std::string& username, int delta)
{
    int current = 0;

    if(scores.Contains(username))
    {
        current = scores.Get(username);
    }

    int updated = current + delta;

    scores.Insert(username, updated);

    ranking.Insert(username, updated);
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
    std::vector<HeapNode<std::string>> topNodes = ranking.TopN(count);

    std::vector<std::pair<std::string,int>> top;

    for(const HeapNode<std::string>& node : topNodes)
    {
        top.push_back(std::make_pair(node.data, node.priority));
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