#pragma once

#include <vector>
#include <stdexcept>
#include<iostream>

#include "HeapNode.h"

template<typename T>
class MinHeap
{
private:
    std::vector<HeapNode<T>> heap;

private :
    void HeapifyUp(int index)
    {
        while(index > 0)
        {
            int parent = (index - 1) / 2;

            if(heap[parent].priority <= heap[index].priority)
                break;

            std::swap(heap[parent], heap[index]);

            index = parent;
        }
    }

    void HeapifyDown(int index)
    {
        while(true)
        {
            int left = 2 * index + 1;

            int right = 2 * index + 2;

            int smallest = index;

            if(left < heap.size() &&
               heap[left].priority < heap[smallest].priority)
            {
                smallest = left;
            }

            if(right < heap.size() &&
               heap[right].priority < heap[smallest].priority)
            {
                smallest = right;
            }

            if(smallest == index)
                break;

            std::swap(heap[index], heap[smallest]);

            index = smallest;
        }
    }

public :
    MinHeap()
    {}

    bool IsEmpty() const
    {
        return heap.empty();
    }

    int Size() const
    {
        return heap.size();
    }

    void Clear()
    {
        heap.clear();
    }

    void Insert(const T& value, int priority)
    {
        heap.push_back(
            HeapNode<T>(value, priority)
        );

        HeapifyUp(heap.size()-1);
    }

    HeapNode<T> Peek() const
    {
        if(IsEmpty())
            throw std::out_of_range("Heap is empty");

        return heap.front();
    }

    HeapNode<T> ExtractMin()
    {
        if(IsEmpty())
            throw std::out_of_range("Heap is empty");

        HeapNode<T> root = heap.front();

        heap[0] = heap.back();

        heap.pop_back();

        if(!heap.empty())
        {
            HeapifyDown(0);
        }

        return root;
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