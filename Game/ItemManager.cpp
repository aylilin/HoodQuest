#include "ItemManager.h"

ItemManager::ItemManager()
{
}

void ItemManager::addItem(const Item& item)
{
    items.push_back(item);
}

bool ItemManager::checkAndCollect(int vertexId, Player& player)
{
    bool collectedAny = false;

    for(Item& item : items)
    {
        if(!item.isCollected() && item.getVertexId() == vertexId)
        {
            item.collect();

            if(item.getType() == ItemType::Basket)
            {
                player.collectBasket();
            }
            else if(item.getType() == ItemType::Flower)
            {
                player.collectFlower();
            }
            else if(item.getType() == ItemType::Key)
            {
                player.collectKey();
            }

            collectedAny = true;
        }
    }

    return collectedAny;
}

bool ItemManager::hasAllItems(const Player& player) const
{
    return player.hasBasket() && player.hasFlower() && player.hasKey();
}

int ItemManager::remainingItemCount() const
{
    int count = 0;

    for(const Item& item : items)
    {
        if(!item.isCollected())
            count++;
    }

    return count;
}

std::vector<Item> ItemManager::getItems() const
{
    return items;
}