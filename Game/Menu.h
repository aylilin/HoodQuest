#pragma once

#include <map>
#include <string>
#include <vector>

#include "../DataStructures/Graph.h"
#include "../DataStructures/HashTable.h"
#include "../IO/FileManager.h"
#include "GameEngine.h"
#include "ScoreManager.h"

class Menu
{
private:

    Graph& graph;

    int goalVertex;

    std::map<int,std::string> labels;

    std::string usersFilePath;

    HashTable<std::string, UserRecord> userTable;

    std::vector<UserRecord> userList;

    ScoreManager scoreManager;

    int pickRandomStart(const std::vector<int>& ids, int exclude) const;

    void printState(GameEngine& engine) const;

    void printSuggestion(GameEngine& engine) const;

    std::string label(int vertexId) const;

    bool registerUser();

    bool loginUser(std::string& loggedInUser);

    void showTopPlayer() const;

    
    void searchPlayerScore() const;

    void updateUserScore(const std::string& username, int delta);

    void playGame(const std::string& username);

public:

    Menu(
        Graph& graph,
        int goalVertex,
        const std::map<int,std::string>& labels = {},
        const std::string& usersFilePath = "users.txt"
    );

    void run();
};