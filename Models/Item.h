#pragma once

#include <string>

enum class ItemType
{
    Basket,
    Flower,
    Key
};

class Item
{
private :
    int id;

    ItemType type;

    int vertexId;

    bool collected;

public :
    Item();

    Item(int id, ItemType type, int vertexId);

    int getId() const;

    ItemType getType() const;

    int getVertexId() const;

    bool isCollected() const;

    void collect();

    std::string getName() const;
};