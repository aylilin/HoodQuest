#pragma once

class Wolf{
private :
    int id;

    int currentPosition;

    bool active;

public :
    Wolf();

    Wolf(int id, int startPosition);

    void move(int destination);

    int getId() const;

    int getPosition() const;

    void setPosition(int position);

    bool isActive() const;

    void setActive(bool state);
};