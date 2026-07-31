#pragma once

template<typename K, typename V>
class BSTNode
{
public:

    K key;

    V value;

    BSTNode<K,V>* left;

    BSTNode<K,V>* right;

    BSTNode(const K& key, const V& value)
    {
        this->key = key;
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};