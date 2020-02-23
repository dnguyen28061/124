#include<stdio.h> 
#include<vector> 
#include <unordered_map>
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

Heap Heap::Heap(int k) {
    k = k; 
    std::vector<HeapNode>heap; 
    std::unordered_map<int, int>map;
}

void Heap::heapifyUp(int idx){ 
    int child = idx; 
    int parent = (idx - 1)/k; 
    while(heap[child].val > heap[parent].val && parent > 0) { 
        map[heap[child].id] = parent;
        map[heap[parent].id] = child;
        std::swap(heap[child], heap[parent]);
        child = parent;
        parent = (child - 1)/k; 
    }
}; 
// params: idx is index of element from which we heapify down 
void Heap::heapifyDown(int idx){
    HeapNode parent = heap[idx];
    int mindex = 0;
    HeapNode min = heap[k * idx + 1];
    for (int i = k * idx + 1; i <= k * idx + k; i++) {
        if (i < heap.size() - 1) {
            if (min.val > heap[i].val) {
                min = heap[i];
                mindex = i;
            }
        }
        
    }
    if (min.val < parent.val) {
        map[min.id] = idx;
        map[parent.id] = mindex;
        std::swap(min, parent);
        heapifyDown(mindex);
    }
    return; 
}; 
// returns min element from heap without deleting it 
HeapNode Heap::peek(){ 
    return heap[0]; 
}; 

// returns min element from heap and removes it from heap 
HeapNode Heap::extractMin(){ 
    HeapNode min = heap.front(); 
    heap.pop_front();
    heapifyDown(0); 
    return min; 
}; 
// inserts element into the heap 
void Heap::insert(HeapNode elt){ 
    map[elt.id] = heap.size() - 1
    heap.push_back(elt);
    heapifyUp(heap.size() - 1); 
}; 

// Decreases key of the given element
void Heap::decreaseKey(int newKey, int vertex) { 
    HeapNode node = heap[map[vertex]];
    node.val = newKey;
    return;
}; 