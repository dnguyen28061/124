#include<stdio.h>
#include<vector> 

struct HeapNode; 
struct Heap{
    private: 
        std::vector<int>heap; 
        void heapifyUp(); 
        void heapifyDown(int x); 
    public: 
        HeapNode peek(); 
        HeapNode extractMin(); 
        void insert(HeapNode elt); 
};