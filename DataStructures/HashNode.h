#pragma once

template<typename K, typename V>
class HashNode
{
public:

    K key;

    V value;

    HashNode<K,V>* next;

    HashNode(const K& key, const V& value)
    {
        this->key = key;
        this->value = value;
        next = nullptr;
    }
};