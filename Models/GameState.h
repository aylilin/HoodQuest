#pragma once

#include "Player.h"
#include "Wolf.h"

class GameState{
private :
    Player player;

    Wolf wolf;

    int moveCount;

    bool gameFinished;

public :
    GameState();

    GameState(const Player& player, const Wolf& wolf);

    void setPlayer(const Player& player);

    Player getPlayer() const;

    void setWolf(const Wolf& wolf);

    Wolf getWolf() const;

    void increaseMove();

    int getMoveCount() const;

    void setMoveCount(int moves);

    void finishGame();

    bool isFinished() const;

    void reset();
};