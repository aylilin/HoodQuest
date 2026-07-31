#include "Item.h"

Item::Item()
{
    id = 0;
    type = ItemType::Basket;
    vertexId = 0;
    collected = false;
}

Item::Item(int id, ItemType type, int vertexId)
{
    this->id = id;
    this->type = type;
    this->vertexId = vertexId;
    collected = false;
}

int Item::getId() const
{
    return id;
}

ItemType Item::getType() const
{
    return type;
}

int Item::getVertexId() const
{
    return vertexId;
}

bool Item::isCollected() const
{
    return collected;
}

void Item::collect()
{
    collected = true;
}

std::string Item::getName() const
{
    switch(type)
    {
        case ItemType::Basket:
            return "Basket";

        case ItemType::Flower:
            return "Flower";

        case ItemType::Key:
            return "Key";
    }

    return "Unknown";
}