
#include<stdio.h>
#include<iostream> 
#include<vector>
#include<cassert>
#include<chrono>
#include<random>
#include<deque>
#include<unordered_map>
#include<climits>

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

    bool notNull() {
        return (this->heap.size() > 0); 
    };

    HeapNode peek(){ 
        return this->heap[0]; 
    }; 

    // returns min element from heap and removes it from heap 
    HeapNode extractMin(){ 
        if (this->heap.size() == 0) {
            throw std::invalid_argument("Heap Size 0!");
        }
        HeapNode min = this->heap.front();
        HeapNode top = this->heap.back();
        this->heap.pop_back();
        if (this->heap.size() == 0) {
            return min;
        }
        this->heap.pop_front();
        this->heap.push_front(top);
        heapifyDown(0); 
        return min; 
    }; 
    // inserts element into the heap 
    void insert(HeapNode elt){ 
        this->map[elt.id] = this->heap.size();
        this->heap.push_back(elt);
        heapifyUp(this->heap.size() - 1); 
    }; 

    // Decreases key of the given element
    void decreaseKey(int newKey, int vertex){ 
        this->heap[this->map[vertex]].val = newKey;
        heapifyUp(this->map[vertex]);
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
        // printf("%d", this->parent == this); 
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

// Construct graph with numNodes in dimensions from 2-4.
float randomgen(); 
struct Vertex{
    public: 
    int id; 
    std::vector<float>coordinates; 
    Vertex(int idNum, int numDimensions){ 
        id = idNum; 
        for (int i = 0; i < numDimensions; i++){ 
            float coord = randomgen(); 
            coordinates.push_back(coord); 
        }
    }
}; 

float euclideanDist(std::vector<float>p1, std::vector<float>p2); 
struct Graph{ 
    public: 
    // adjacency matrix, where arr[i][j] is the weight from node i to j 
    std::vector<std::vector<float>>verticesNeighbors; 
    std::vector<Vertex>verticesList;
    std::vector<Set *>setList; 
    Graph(int numNodes, int dimensions){
        for (int i = 0; i < numNodes; ++i){ 
            verticesList.push_back(Vertex(i, dimensions)); 
        }
        // iterate through each vertice pair find its edge weight 
        for(int i = 0; i < numNodes; ++i){ 
            // array that stores all outgoing edge weights from vertex i 
            std::vector<float>vertexNeighbors; 
            for(int j = 0; j < numNodes; ++j){ 
                // if already calculated edge weight, then just retrieve from neighbor 
                if(j < i){ 
                    vertexNeighbors.push_back(verticesNeighbors[j][i]); 
                }
                else{ 
                    float dist = euclideanDist(verticesList[i].coordinates, verticesList[j].coordinates);
                    vertexNeighbors.push_back(dist); 
                }  
            }
            verticesNeighbors.push_back(vertexNeighbors); 
        }
        // create sets for all vertices 
        for(int i = 0; i < numNodes; ++i){ 
            setList.push_back(new Set(i)); 
        }
    }
    ~Graph(){
        for(int i = 0; i < setList.size(); ++i){ 
            delete setList[i]; 
        }
    }
      
};


float randomgen(){
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(mt);
};

float euclideanDist(std::vector<float>p1, std::vector<float>p2) { 
    if (p1.size() != p2.size()){ 
        printf("p1 = %lu, p2 = %lu\n", p1.size(), p2.size()); 
    }
    assert(p1.size() == p2.size());
    float dist = 0.0;
    for (int i = 0; i < p1.size(); i++){
        dist += pow((p1[i] - p2[i]), 2.0);
    }
    return dist;
}

float returnEdgeWeight(Graph* graph, int* arr){ 
    int arrSize = sizeof(arr) / sizeof(arr[0]); 
    float weightSum = 0.0; 
    for (int i = 1; i < arrSize; ++i){ 
        assert(arr[i] != -1); 
        weightSum += graph->verticesNeighbors[i][arr[i]]; 
    }
    return (weightSum); 
}

int main(int argc, char* argv[]){ 
    if (argc != 5) {
        throw std::invalid_argument("Usage: ./randmst 0 numpoints trials dimension");
    }
    int numpoints = atoi(argv[2]);
    int trials = atoi(argv[3]);
    int dimension = atoi(argv[4]);

    Graph* newGraph = new Graph(numpoints, dimension); 

    int dist[numpoints] = {INT_MAX}; 
    int prev[numpoints] = {-1};
    std::fill_n(dist, numpoints, INT_MAX); 
    std::fill_n(prev, numpoints, -1);
    Heap h = Heap((numpoints - 1 / 2));
    std::unordered_map<int, int>map;

    //Can you modify the set implementation so we can initialize this as empty? If not, we can work around it but it's cleaner this way.   
    Set* s = new Set(-1);

    HeapNode node = HeapNode(0, 0);
    h.insert(node);
    map[0] = 1;
    dist[0] = 0;
    while (h.notNull()) {
        HeapNode v = h.extractMin(); 

        // Does this replace the set s with the union of set s and set v_set? If not can you change it to do so
        s->makeUnion(newGraph->setList[v.id]);
        assert(s->find()->vertex == newGraph->setList[v.id]->find()->vertex);

        for (int i = 0; i < numpoints; i++) { 
            // This line should say: if (i is in the disjoint set of all vertices minus the set s). Can you implement the set difference operation? {
            if (newGraph->setList[v.id]->find()->vertex != newGraph->setList[i]->find()->vertex){
                if (i != v.id && dist[i] > newGraph->verticesNeighbors[v.id][i]) {
                    dist[i] = newGraph->verticesNeighbors[v.id][i];
                    prev[i] = v.id;
                    if (map.find(i) != map.end()) {
                        h.decreaseKey(dist[i],i);
                    } 
                    else {
                        HeapNode newnode = HeapNode(i, dist[i]);
                        h.insert(newnode);
                        map[i] = 1;
                    }
                }
            }

        }

    }
    std::cout << returnEdgeWeight(newGraph, prev) << "\n"; 
    delete newGraph;
    delete s; 
}

// float 
