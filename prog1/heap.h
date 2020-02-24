#include<stdio.h>
#include<vector> 

struct HeapNode; 
struct Heap{
    private: 
        std::vector<int>heap; 
        void heapifyUp(int idx); 
        void heapifyDown(int x); 
    public: 
        void decreaseKey(int newKey, int vertex)
        HeapNode peek(); 
        HeapNode extractMin(); 
        void insert(HeapNode elt); 
};

