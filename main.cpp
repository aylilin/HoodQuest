#include <iostream>

#include "DataStructures/MinHeap.h"

using namespace std;

int main()
{
    MinHeap<int> heap;

    heap.Insert(10,5);

    heap.Insert(20,2);

    heap.Insert(30,9);

    heap.Insert(40,1);

    heap.Insert(50,7);

    cout<<"Heap : ";

    heap.Print();

    cout<<endl;

    while(!heap.IsEmpty())
    {
        HeapNode<int> node =
            heap.ExtractMin();

        cout
            << node.data
            << " "
            << node.priority
            << endl;
    }

    return 0;
}