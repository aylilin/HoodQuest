#pragma once

template<typename T>
class StackNode
{
public:

    T data;

    StackNode<T>* next;

    StackNode(const T& value)
    {
        data = value;
        next = nullptr;
    }
};