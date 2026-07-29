#pragma once

class Player
{
private :
    int id;
    int currentPosition;
    int score;

    bool basket;
    bool flower;
    bool key;

public :
    Player();

    Player(int id, int startPosition);

    void move(int destination);

    int getId() const;

    int getPosition() const;

    void setPosition(int position);

    int getScore() const;

    void addScore(int value);

    void resetScore();

    void collectBasket();

    void collectFlower();

    void collectKey();

    bool hasBasket() const;

    bool hasFlower() const;

    bool hasKey() const;

    void resetItems();
};