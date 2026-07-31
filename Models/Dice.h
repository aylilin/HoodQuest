#pragma once

class Dice
{
private :
    int lastRoll;

public :
    Dice();

    int roll();

    int getLastRoll() const;

    static bool isEven(int value);
};