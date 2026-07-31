#include "GameEngine.h"

#include "../Algorithms/Dijkstra.h"
#include "../Algorithms/BFS.h"

GameEngine::GameEngine(
    Graph& graph,
    int goalVertex,
    const Player& player,
    const Wolf& wolf)
    : graph(graph),
      goalVertex(goalVertex),
      state(player, wolf)
{
    computeSuggestedPath();
}

void GameEngine::computeSuggestedPath()
{
    suggestedPath = Dijkstra::shortestPath(
        graph,
        state.getPlayer().getPosition(),
        goalVertex
    );
}

std::vector<int> GameEngine::getSuggestedPath() const
{
    return suggestedPath;
}

int GameEngine::getSuggestedNextMove() const
{
    if(suggestedPath.size() > 1)
        return suggestedPath[1];

    return state.getPlayer().getPosition();
}

bool GameEngine::isValidMove(int destination) const
{
    std::vector<Edge> neighbors =
        graph.getNeighbors(state.getPlayer().getPosition());

    for(const Edge& edge : neighbors)
    {
        if(edge.destination == destination)
            return true;
    }

    return false;
}

bool GameEngine::canUndo() const
{
    return !history.IsEmpty();
}

bool GameEngine::checkCollision() const
{
    return state.getPlayer().getPosition() ==
           state.getWolf().getPosition();
}

void GameEngine::runWolfTurn()
{
    Wolf wolf = state.getWolf();

    int rollValue = dice.roll();

    if(Dice::isEven(rollValue))
    {
        int next = BFS::nextMove(
            graph,
            wolf.getPosition(),
            state.getPlayer().getPosition()
        );

        wolf.move(next);
    }

    state.setWolf(wolf);
}

int GameEngine::getLastWolfRoll() const
{
    return dice.getLastRoll();
}

TurnResult GameEngine::playTurn(int destination)
{
    if(isGameOver())
        return TurnResult::InvalidMove;

    if(!isValidMove(destination))
        return TurnResult::InvalidMove;

    // Save the state at the start of this turn so it can be
    // restored later if the player calls Undo().
    history.Push(state);

    // Score depends on whether the chosen move matches Dijkstra's
    // suggested next step (computed from the position we are in
    // right now, before moving).
    int scoreDelta = 1;

    if(suggestedPath.size() > 1 && suggestedPath[1] == destination)
    {
        scoreDelta = 3;
    }

    Player player = state.getPlayer();

    player.move(destination);
    player.addScore(scoreDelta);

    state.setPlayer(player);

    state.increaseMove();

    // Reaching the goal wins immediately.
    if(player.getPosition() == goalVertex)
    {
        Player winner = state.getPlayer();

        winner.addScore(5);

        state.setPlayer(winner);

        state.finishGame();

        return TurnResult::PlayerWon;
    }

    // Walking onto the wolf's current tile loses immediately;
    // we must not wait for the wolf to move.
    if(checkCollision())
    {
        state.finishGame();

        return TurnResult::PlayerLost;
    }

    // Wolf's turn: roll the dice, move only on an even result.
    runWolfTurn();

    if(checkCollision())
    {
        state.finishGame();

        return TurnResult::PlayerLost;
    }

    // Recompute the suggestion from the new position for the
    // next call to getSuggestedPath()/getSuggestedNextMove().
    computeSuggestedPath();

    return TurnResult::Continue;
}

bool GameEngine::undo()
{
    if(history.IsEmpty())
        return false;

    GameState previous = history.Top();

    history.Pop();

    Player player = previous.getPlayer();

    // Two-point penalty applied on top of the restored score.
    player.addScore(-2);

    previous.setPlayer(player);

    state = previous;

    computeSuggestedPath();

    return true;
}

GameState GameEngine::getState() const
{
    return state;
}

bool GameEngine::isGameOver() const
{
    return state.isFinished();
}

int GameEngine::getGoalVertex() const
{
    return goalVertex;
}