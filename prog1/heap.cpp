#include<stdio.h> 
#include<vector> 
#include"heap.h" 
struct HeapNode{
    public: 
        int id; 
        int val; 
    HeapNode(int id, int val){
        id = id; 
        val = val; 
    }
}; 

void Heap::heapifyUp(){ 
    return; 
}; 
// params: x is index of element from which we heapify down 
void Heap::heapifyDown(int x){
    return; 
}; 
    // returns min element from heap without deleting it 
HeapNode Heap::peek(){ 
    return HeapNode(4, 5); 
}; 
// returns min element from heap and removes it from heap 
HeapNode Heap::extractMin(){ 
    return HeapNode(1, 2); 
}; 
// inserts element into the heap 
void Heap::insert(HeapNode elt){ 
    return; 
}; 