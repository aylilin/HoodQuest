#pragma once

#include "StackNode.h"
#include <stdexcept>

template<typename T>
class Stack
{
private:

    StackNode<T>* top;

    int count;

public:

    Stack()
    {
        top = nullptr;
        count = 0;
    }

    ~Stack()
    {
        Clear();
    }

    bool IsEmpty() const
    {
        return top == nullptr;
    }

    int Size() const
    {
        return count;
    }

    void Push(const T& value)
    {
        StackNode<T>* node = new StackNode<T>(value);

        node->next = top;

        top = node;

        count++;
    }

    void Pop()
    {
        if(IsEmpty())
            return;

        StackNode<T>* temp = top;

        top = top->next;

        delete temp;

        count--;
    }

    T Top() const
    {
        if(IsEmpty())
            throw std::out_of_range("Stack is empty");

        return top->data;
    }

    void Clear()
    {
        while(!IsEmpty())
        {
            Pop();
        }
    }
};