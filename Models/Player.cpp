#include "Player.h"

Player::Player()
{
    id = 0;

    currentPosition = 0;

    score = 0;

    basket = false;
    flower = false;
    key = false;
}

Player::Player(int id, int startPosition)
{
    this->id = id;

    currentPosition = startPosition;

    score = 0;

    basket = false;
    flower = false;
    key = false;
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

void Player::collectBasket()
{
    basket = true;
}

void Player::collectFlower()
{
    flower = true;
}

void Player::collectKey()
{
    key = true;
}

bool Player::hasBasket() const
{
    return basket;
}

bool Player::hasFlower() const
{
    return flower;
}

bool Player::hasKey() const
{
    return key;
}

void Player::resetItems()
{
    basket = false;
    flower = false;
    key = false;
}