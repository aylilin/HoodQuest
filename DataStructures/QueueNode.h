#pragma once

template<typename T>
class QueueNode
{
public:

    T data;

    QueueNode<T>* next;

    QueueNode(const T& value)
    {
        data = value;
        next = nullptr;
    }
};