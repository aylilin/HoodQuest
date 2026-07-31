#pragma once

#include <vector>

#include "../Models/Item.h"
#include "../Models/Player.h"

class ItemManager
{
private :
    std::vector<Item> items;

public :
    ItemManager();

    void addItem(const Item& item);

   
    bool checkAndCollect(int vertexId, Player& player);

    bool hasAllItems(const Player& player) const;

    int remainingItemCount() const;

    std::vector<Item> getItems() const;
};