#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "HeapNode.h"
#include "HashTable.h"

template<typename T>
class MaxHeap
{
private:

    std::vector<HeapNode<T>> heap;

    HashTable<T,int> position;

    void swapNodes(int a, int b)
    {
        std::swap(heap[a], heap[b]);

        position.Insert(heap[a].data, a);
        position.Insert(heap[b].data, b);
    }

    void HeapifyUp(int index)
    {
        while(index > 0)
        {
            int parent = (index - 1) / 2;

            if(heap[parent].priority >= heap[index].priority)
                break;

            swapNodes(parent, index);

            index = parent;
        }
    }

    void HeapifyDown(int index)
    {
        while(true)
        {
            int left = 2 * index + 1;

            int right = 2 * index + 2;

            int largest = index;

            if(left < (int)heap.size() &&
               heap[left].priority > heap[largest].priority)
            {
                largest = left;
            }

            if(right < (int)heap.size() &&
               heap[right].priority > heap[largest].priority)
            {
                largest = right;
            }

            if(largest == index)
                break;

            swapNodes(index, largest);

            index = largest;
        }
    }

public :
    MaxHeap()
    {}

    bool IsEmpty() const
    {
        return heap.empty();
    }

    int Size() const
    {
        return (int)heap.size();
    }

    bool Contains(const T& key) const
    {
        return position.Contains(key);
    }

    int GetPriority(const T& key) const
    {
        int index = position.Get(key);

        return heap[index].priority;
    }

    void Insert(const T& value, int priority)
    {
        if(position.Contains(value))
        {
            UpdatePriority(value, priority);

            return;
        }

        heap.push_back(
            HeapNode<T>(value, priority)
        );

        int index = (int)heap.size() - 1;

        position.Insert(value, index);

        HeapifyUp(index);
    }

    void UpdatePriority(const T& key, int newPriority)
    {
        if(!position.Contains(key))
        {
            Insert(key, newPriority);

            return;
        }

        int index = position.Get(key);

        int oldPriority = heap[index].priority;

        heap[index].priority = newPriority;

        if(newPriority > oldPriority)
            HeapifyUp(index);
        else if(newPriority < oldPriority)
            HeapifyDown(index);
    }

    HeapNode<T> Peek() const
    {
        if(IsEmpty())
            throw std::out_of_range("Heap is empty");

        return heap.front();
    }

    HeapNode<T> ExtractMax()
    {
        if(IsEmpty())
            throw std::out_of_range("Heap is empty");

        HeapNode<T> root = heap.front();

        position.Remove(root.data);

        heap[0] = heap.back();

        heap.pop_back();

        if(!heap.empty())
        {
            position.Insert(heap[0].data, 0);

            HeapifyDown(0);
        }

        return root;
    }

    std::vector<HeapNode<T>> TopN(int count) const
    {
        std::vector<HeapNode<T>> copy = heap;

        int n = std::min(count, (int)copy.size());

        std::partial_sort(
            copy.begin(),
            copy.begin() + n,
            copy.end(),
            [](const HeapNode<T>& a, const HeapNode<T>& b)
            {
                return a.priority > b.priority;
            }
        );

        return std::vector<HeapNode<T>>(copy.begin(), copy.begin() + n);
    }

    void Print() const
    {
        for(const auto& node : heap)
        {
            std::cout
                << "("
                << node.data
                << ", "
                << node.priority
                << ") ";
        }

        std::cout << std::endl;
    }
};