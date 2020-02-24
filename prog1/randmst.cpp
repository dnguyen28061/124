
#include<stdio.h>
#include<iostream> 
#include<vector>
#include<deque>
#include <unordered_map>

// generates MSTs and calculates the average weight of the MST based on number of vertices 
// usage: ./ 0 numpoints, numtrials, dimension 

// argc == number of arguments provided (4 by default). Access these elements by indexing into argv array 


struct HeapNode{
    public: 
        int id; 
        int val; 
    HeapNode(int num1, int num2){
        id = num1; 
        val = num2; 
    }
}; 

struct Heap {
    public: 

    std::deque<HeapNode>heap;
    std::unordered_map<int, int>map;
    int k;

    Heap(int num) {
        k = num; 
    };    

    HeapNode peek(){ 
        return this->heap[0]; 
    }; 

    // returns min element from heap and removes it from heap 
    HeapNode extractMin(){ 
        HeapNode min = this->heap.front();
        HeapNode top = this->heap.back();
        this->heap.pop_back();
        this->heap.pop_front();
        this->heap.push_front(top);
        heapifyDown(0); 
        return min; 
    }; 
    // inserts element into the heap 
    void insert(HeapNode elt){ 
        map[elt.id] = this->heap.size() - 1;
        this->heap.push_back(elt);
        heapifyUp(this->heap.size() - 1); 
    }; 

    // Decreases key of the given element
    void decreaseKey(int newKey, int vertex){ 
        HeapNode node = this->heap[this->map[vertex]];
        node.val = newKey;
    }; 

    private: 
        
    void heapifyUp(int idx){ 
        int child = idx; 
        int parent = (idx - 1)/k; 
        while(this->heap[child].val < this->heap[parent].val && child > 0) { 
            this->map[this->heap[child].id] = parent;
            this->map[this->heap[parent].id] = child;
            std::swap(this->heap[child], this->heap[parent]);
            child = parent;
            parent = (child - 1)/k; 
        }
    }; 


    void heapifyDown(int idx){
        HeapNode parent = this->heap[idx];
        int mindex = k * idx + 1;
        if (k * idx + 1 <= this->heap.size() - 1){
            HeapNode min = this->heap[k * idx + 1];
            for (int i = k * idx + 1; i <= k * idx + k; i++) {
                if (i <= this->heap.size() - 1) {
                    if (min.val > this->heap[i].val) {
                        min = this->heap[i];
                        mindex = i;
                    }
                }
                
            }

            if (min.val < parent.val) {
                this->map[min.id] = idx;
                this->map[parent.id] = mindex;
                std::swap(this->heap[idx], this->heap[mindex]);
                heapifyDown(mindex);
            }
        }
        
        return; 
    }; 
         
};


struct Set{
    public: 
    int vertex; 
    int rank; 
    Set* parent; 

    Set(int x){
        vertex = x; 
        rank = 0; 
        parent = this; 
    };    

    Set* find(){
        if (this->parent != this){
            Set* parent = this->parent->find(); 
            this->parent = parent; 
        }
        return this->parent; 
    };    

    void makeUnion(Set* nodeToUnionWith){
        Set* parent1 = this->find(); 
        Set* parent2 = nodeToUnionWith->find(); 
        
        parent1->link(parent2); 
    }; 
    // replace two sets containing x and y by their union.   
    void link(Set* nodeToLinkWith){
        Set* smallRankNode = this; 
        Set* largeRankNode = nodeToLinkWith; 
        
        if (smallRankNode->rank > largeRankNode->rank){ 
            Set* temp = smallRankNode; 
            smallRankNode = largeRankNode; 
            largeRankNode = temp; 
        }
        // only increase rank when ranks are equal. 
        if(smallRankNode->rank == largeRankNode->rank){ 
            largeRankNode->rank++; 
        }
        // point smaller rank node to larger rank node. 
        smallRankNode->parent = largeRankNode; 

    }; // connect two nodes with union by rank 
};



int main(int argc, char* argv[]){ 
    std::vector<Set *> setList; 
    for(int i = 0; i < 10; i++){ 
        setList.push_back(new Set(i)); 
    }
    for(int i = 0; i < 10; i++){ 
        std::cout << setList[i]->find()->vertex << "\n"; 
    }
    setList[0]->makeUnion(setList[1]); 
    setList[9]->makeUnion(setList[8]);
    std::cout << setList[0]->find()->vertex << "\n"; 
    std::cout << setList[1]->find()->vertex << "\n";
    std::cout << setList[9]->find()->vertex << "\n"; 
    std::cout << setList[8]->find()->vertex << "\n";
    std::cout << setList[2]->find()->vertex << "\n"; 

    HeapNode a = HeapNode(1, 8);
    HeapNode b = HeapNode(2, 1);
    HeapNode c = HeapNode(3, 4);
    HeapNode d = HeapNode(4, 2);
    HeapNode e = HeapNode(5, 12);
    HeapNode f = HeapNode(6, 7);
    HeapNode g = HeapNode(7, 3);
    HeapNode h = HeapNode(8, 10);
    HeapNode i = HeapNode(9, 6);
    HeapNode j = HeapNode(10, 11);
    HeapNode k = HeapNode(11, 5);
    HeapNode l = HeapNode(12, 9);

    Heap heap = Heap(3);
    heap.insert(a);
    heap.insert(b);
    heap.insert(c);
    heap.insert(d);
    heap.insert(e);
    heap.insert(f);
    heap.insert(h);
    heap.insert(i);
    heap.insert(j);
    heap.insert(k);
    heap.insert(l);

    std::cout << heap.extractMin().id << "\n"; 
    std::cout << heap.extractMin().id << "\n"; 
    std::cout << heap.extractMin().id << "\n"; 
    std::cout << heap.extractMin().id << "\n"; 
    std::cout << heap.extractMin().id << "\n"; 
    std::cout << heap.extractMin().id << "\n"; 
}
