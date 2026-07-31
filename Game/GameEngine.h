#pragma once

#include <vector>

#include "../Models/GameState.h"
#include "../Models/Dice.h"
#include "../DataStructures/Graph.h"
#include "../DataStructures/Stack.h"

enum class TurnResult
{
    InvalidMove,
    Continue,
    PlayerWon,
    PlayerLost
};

class GameEngine
{
private:

    Graph& graph;

    int goalVertex;

    GameState state;

    Stack<GameState> history;

    Dice dice;

    std::vector<int> suggestedPath;

    void computeSuggestedPath();

    void runWolfTurn();

    bool checkCollision() const;

public:

    GameEngine(
        Graph& graph,
        int goalVertex,
        const Player& player,
        const Wolf& wolf
    );

    std::vector<int> getSuggestedPath() const;

    int getSuggestedNextMove() const;

    bool isValidMove(int destination) const;

    bool canUndo() const;

    TurnResult playTurn(int destination);

    bool undo();

    GameState getState() const;

    bool isGameOver() const;

    int getGoalVertex() const;

    int getLastWolfRoll() const;
};