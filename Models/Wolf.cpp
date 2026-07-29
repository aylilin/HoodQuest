#include "Wolf.h"

Wolf::Wolf()
{
    id = 0;

    currentPosition = 0;

    active = true;
}

Wolf::Wolf(int id, int startPosition)
{
    this->id = id;

    currentPosition = startPosition;

    active = true;
}

void Wolf::move(int destination)
{
    currentPosition = destination;
}

int Wolf::getId() const
{
    return id;
}

int Wolf::getPosition() const
{
    return currentPosition;
}

void Wolf::setPosition(int position)
{
    currentPosition = position;
}

bool Wolf::isActive() const
{
    return active;
}

void Wolf::setActive(bool state)
{
    active = state;
}