#pragma once

#include <string>
#include <vector>
#include <utility>

#include "../DataStructures/BST.h"

class ScoreManager
{
private :
    BST<std::string, int> scores;

public :
    ScoreManager();

    void setScore(const std::string& username, int score);

    void addToScore(const std::string& username, int delta);

    bool hasUser(const std::string& username) const;

    int getScore(const std::string& username) const;

   
    std::vector<std::pair<std::string,int>> getTopPlayers(int count) const;

   
    std::vector<std::pair<std::string,int>> getAllScoresSorted() const;

    int userCount() const;
};