#include "Player.h"

Player::Player()
{
    id = 0;

    currentPosition = 0;

    score = 0;
}

Player::Player(int id, int startPosition)
{
    this->id = id;

    currentPosition = startPosition;

    score = 0;
}

void Player::move(int destination)
{
    currentPosition = destination;
}

int Player::getId() const
{
    return id;
}

int Player::getPosition() const
{
    return currentPosition;
}

void Player::setPosition(int position)
{
    currentPosition = position;
}

int Player::getScore() const
{
    return score;
}

void Player::addScore(int value)
{
    score += value;
}

void Player::resetScore()
{
    score = 0;
}