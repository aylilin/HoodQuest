#include "Dice.h"

#include <cstdlib>

Dice::Dice()
{
    lastRoll = 0;
}

int Dice::roll()
{
    lastRoll = (rand() % 6) + 1;

    return lastRoll;
}

int Dice::getLastRoll() const
{
    return lastRoll;
}

bool Dice::isEven(int value)
{
    return value % 2 == 0;
}