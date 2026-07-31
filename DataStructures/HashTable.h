#pragma once

#include <vector>
#include <stdexcept>
#include <functional>

#include "HashNode.h"

template<typename K, typename V>
class HashTable
{
private:

    std::vector<HashNode<K,V>*> buckets;

    int bucketCount;

    int elementCount;

    int hashIndex(const K& key) const
    {
        std::hash<K> hasher;

        return static_cast<int>(hasher(key) % bucketCount);
    }

public:

    HashTable(int bucketCount = 101)
    {
        this->bucketCount = bucketCount;

        buckets.assign(bucketCount, nullptr);

        elementCount = 0;
    }

    ~HashTable()
    {
        Clear();
    }

    void Insert(const K& key, const V& value)
    {
        int index = hashIndex(key);

        HashNode<K,V>* node = buckets[index];

        while(node != nullptr)
        {
            if(node->key == key)
            {
                node->value = value;

                return;
            }

            node = node->next;
        }

        HashNode<K,V>* newNode = new HashNode<K,V>(key, value);

        newNode->next = buckets[index];

        buckets[index] = newNode;

        elementCount++;
    }

    bool Contains(const K& key) const
    {
        int index = hashIndex(key);

        HashNode<K,V>* node = buckets[index];

        while(node != nullptr)
        {
            if(node->key == key)
                return true;

            node = node->next;
        }

        return false;
    }

    V Get(const K& key) const
    {
        int index = hashIndex(key);

        HashNode<K,V>* node = buckets[index];

        while(node != nullptr)
        {
            if(node->key == key)
                return node->value;

            node = node->next;
        }

        throw std::out_of_range("Key not found in HashTable");
    }

    bool Remove(const K& key)
    {
        int index = hashIndex(key);

        HashNode<K,V>* node = buckets[index];

        HashNode<K,V>* prev = nullptr;

        while(node != nullptr)
        {
            if(node->key == key)
            {
                if(prev == nullptr)
                    buckets[index] = node->next;
                else
                    prev->next = node->next;

                delete node;

                elementCount--;

                return true;
            }

            prev = node;

            node = node->next;
        }

        return false;
    }

    int Size() const
    {
        return elementCount;
    }

    bool IsEmpty() const
    {
        return elementCount == 0;
    }

    void Clear()
    {
        for(int i = 0; i < bucketCount; i++)
        {
            HashNode<K,V>* node = buckets[i];

            while(node != nullptr)
            {
                HashNode<K,V>* temp = node;

                node = node->next;

                delete temp;
            }

            buckets[i] = nullptr;
        }

        elementCount = 0;
    }
};