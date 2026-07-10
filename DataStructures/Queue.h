#pragma once

#include "QueueNode.h"
#include <stdexcept>

template<typename T>
class Queue
{
private:

    QueueNode<T>* front;

    QueueNode<T>* rear;

    int count;

public:

    Queue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    ~Queue()
    {
        Clear();
    }

    bool IsEmpty() const
    {
        return front == nullptr;
    }

    int Size() const
    {
        return count;
    }

    void Enqueue(const T& value)
    {
        QueueNode<T>* node = new QueueNode<T>(value);

        if(IsEmpty())
        {
            front = rear = node;
        }
        else
        {
            rear->next = node;
            rear = node;
        }

        count++;
    }

    void Dequeue()
    {
        if(IsEmpty())
            return;

        QueueNode<T>* temp = front;

        front = front->next;

        delete temp;

        count--;

        if(front == nullptr)
            rear = nullptr;
    }

    T Front() const
    {
        if(IsEmpty())
            throw std::out_of_range("Queue is empty");

        return front->data;
    }

    T Rear() const
    {
        if(IsEmpty())
            throw std::out_of_range("Queue is empty");

        return rear->data;
    }

    void Clear()
    {
        while(!IsEmpty())
        {
            Dequeue();
        }
    }
};