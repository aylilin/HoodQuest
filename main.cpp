#include <iostream>

#include "Models/GameState.h"

using namespace std;

int main()
{
    Player player(1,10);

    Wolf wolf(1,50);

    GameState state(player,wolf);

    cout
        << "Player Position : "
        << state.getPlayer().getPosition()
        << endl;

    cout
        << "Wolf Position : "
        << state.getWolf().getPosition()
        << endl;

    state.increaseMove();

    state.increaseMove();

    cout
        << "Moves : "
        << state.getMoveCount()
        << endl;

    state.finishGame();

    cout
        << "Finished : "
        << state.isFinished()
        << endl;
}