#pragma once

#include <vector>
#include <utility>
#include <stdexcept>

#include "BSTNode.h"

template<typename K, typename V>
class BST
{
private:

    BSTNode<K,V>* root;

    int nodeCount;

    BSTNode<K,V>* insertNode(BSTNode<K,V>* node, const K& key, const V& value)
    {
        if(node == nullptr)
        {
            nodeCount++;

            return new BSTNode<K,V>(key, value);
        }

        if(key < node->key)
            node->left = insertNode(node->left, key, value);
        else if(key > node->key)
            node->right = insertNode(node->right, key, value);
        else
            node->value = value;

        return node;
    }

    BSTNode<K,V>* findNode(BSTNode<K,V>* node, const K& key) const
    {
        if(node == nullptr)
            return nullptr;

        if(key < node->key)
            return findNode(node->left, key);
        else if(key > node->key)
            return findNode(node->right, key);
        else
            return node;
    }

    BSTNode<K,V>* findMin(BSTNode<K,V>* node) const
    {
        while(node->left != nullptr)
            node = node->left;

        return node;
    }

    BSTNode<K,V>* removeNode(BSTNode<K,V>* node, const K& key, bool& removed)
    {
        if(node == nullptr)
            return nullptr;

        if(key < node->key)
        {
            node->left = removeNode(node->left, key, removed);
        }
        else if(key > node->key)
        {
            node->right = removeNode(node->right, key, removed);
        }
        else
        {
            removed = true;

            if(node->left == nullptr)
            {
                BSTNode<K,V>* rightChild = node->right;

                delete node;

                nodeCount--;

                return rightChild;
            }
            else if(node->right == nullptr)
            {
                BSTNode<K,V>* leftChild = node->left;

                delete node;

                nodeCount--;

                return leftChild;
            }
            else
            {
                BSTNode<K,V>* successor = findMin(node->right);

                node->key = successor->key;
                node->value = successor->value;

                bool dummy = false;

                node->right = removeNode(node->right, successor->key, dummy);
            }
        }

        return node;
    }

    void inorderCollect(BSTNode<K,V>* node, std::vector<std::pair<K,V>>& result) const
    {
        if(node == nullptr)
            return;

        inorderCollect(node->left, result);

        result.push_back(std::make_pair(node->key, node->value));

        inorderCollect(node->right, result);
    }

    void destroy(BSTNode<K,V>* node)
    {
        if(node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:

    BST()
    {
        root = nullptr;
        nodeCount = 0;
    }

    ~BST()
    {
        destroy(root);
    }

    void Insert(const K& key, const V& value)
    {
        root = insertNode(root, key, value);
    }

    bool Contains(const K& key) const
    {
        return findNode(root, key) != nullptr;
    }

    V Get(const K& key) const
    {
        BSTNode<K,V>* node = findNode(root, key);

        if(node == nullptr)
            throw std::out_of_range("Key not found in BST");

        return node->value;
    }

    bool Remove(const K& key)
    {
        bool removed = false;

        root = removeNode(root, key, removed);

        return removed;
    }

    int Size() const
    {
        return nodeCount;
    }

    bool IsEmpty() const
    {
        return nodeCount == 0;
    }

    std::vector<std::pair<K,V>> InorderTraversal() const
    {
        std::vector<std::pair<K,V>> result;

        inorderCollect(root, result);

        return result;
    }
};