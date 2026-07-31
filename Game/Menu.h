#pragma once

#include "../DataStructures/Graph.h"
#include "GameEngine.h"

class Menu
{
private:

    Graph& graph;

    int goalVertex;

    int pickRandomStart(const std::vector<int>& ids, int exclude) const;

    void printState(GameEngine& engine) const;

    void printSuggestion(GameEngine& engine) const;

public:

    Menu(Graph& graph, int goalVertex);

    void run();
};