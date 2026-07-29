#include "GameState.h"

GameState::GameState()
{
    moveCount = 0;

    gameFinished = false;
}

GameState::GameState(const Player& player, const Wolf& wolf)
{
    this->player = player;

    this->wolf = wolf;

    moveCount = 0;

    gameFinished = false;
}

void GameState::setPlayer(const Player& player)
{
    this->player = player;
}

Player GameState::getPlayer() const
{
    return player;
}

void GameState::setWolf(const Wolf& wolf)
{
    this->wolf = wolf;
}

Wolf GameState::getWolf() const
{
    return wolf;
}

void GameState::increaseMove()
{
    moveCount++;
}

int GameState::getMoveCount() const
{
    return moveCount;
}

void GameState::setMoveCount(int moves)
{
    moveCount = moves;
}

void GameState::finishGame()
{
    gameFinished = true;
}

bool GameState::isFinished() const
{
    return gameFinished;
}

void GameState::reset()
{
    moveCount = 0;

    gameFinished = false;
}