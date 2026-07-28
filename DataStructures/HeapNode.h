#pragma once

template<typename T>
class HeapNode
{
public :
    T data;

    int priority;

    HeapNode()
    {
        priority = 0;
    }

    HeapNode(const T& value, int priority)
    {
        this->data = value;
        this->priority = priority;
    }
};