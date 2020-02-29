
#include<stdio.h>
#include<iostream> 
#include<vector>
#include<cassert>
#include<chrono>
#include<random>
#include<deque>
#include<unordered_map>
#include<climits>
#include<float.h>
#include<iterator>
#include<math.h> 
#include<numeric>

// generates MSTs and calculates the average weight of the MST based on number of vertices 
// usage: ./ 0 numpoints, numtrials, dimension 

// argc == number of arguments provided (4 by default). Access these elements by indexing into argv array 

// Construct graph with numNodes in dimensions from 0, 2, 3, 4.
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

struct Node{
    public: 
    Node* next = nullptr; 
    Node* prev = nullptr;
    int id; 
    Vertex* vert = nullptr; 
    float distToMST;  
    Node(int num, Vertex* vertex){
        id = num; 
        distToMST = FLT_MAX; 
        vert = vertex; 
    }   
}; 
float euclideanDist(std::vector<float>p1, std::vector<float>p2); 
struct Graph{ 
    public: 
    Node* nonMstVert;
    Graph(int numNodes, int dimensions){
        nonMstVert = new Node(0, new Vertex(0, dimensions)); 
        nonMstVert->distToMST = 0; 
        Node* dummy = nonMstVert; 
        for(int i = 1; i < numNodes; ++i){ 
            dummy->next = new Node(i, new Vertex(i, dimensions)); 
            dummy->next->prev = dummy; 
            dummy = dummy->next;  
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
    return sqrt(dist);
}

/* 
@params: graph 
         node: node in the set of nodes not in MST. 
               Removes this node and updates the set of nodes not in MST. 
*/ 
void removeNode(Node* node, Graph* graph){
    // in the middle 
    if (node->next && node->prev){
        node->prev->next = node->next; 
        node->next->prev = node->prev;     
    }
    // first pointer 
    else if (node->next && node->prev == nullptr){ 
        node->next->prev = nullptr; 
        graph->nonMstVert = node->next; 
    }
    // last pointer 
    else if (node->next == nullptr && node->prev){
        node->prev->next = nullptr; 
    }
    else{
        graph->nonMstVert = nullptr; 
    }

}
/*
@params: graph, MSTNode: current node in the MST
Traverses through the nodes that are not already in the MST. Updates distance if closer to MSTNode. 
@return: node closest to MST. 
*/ 
Node* traverseAndGetMin(Graph* graph, Node* MSTNode, int dimension){
    // have traversed all nodes 
    if (graph->nonMstVert == nullptr){
        return nullptr; 
    }
    Node* closestNodeToMST = graph->nonMstVert;  
    Node* nonMstNode = graph->nonMstVert; 
    while (nonMstNode != nullptr){
        float newDistToMST; 
        if(dimension == 0){
            newDistToMST = randomgen(); 
        }
        else{
            newDistToMST = euclideanDist(MSTNode->vert->coordinates, nonMstNode->vert->coordinates); 
        }
        if (newDistToMST < nonMstNode->distToMST) {
            nonMstNode->distToMST = newDistToMST; 
        }
        if (nonMstNode->distToMST < closestNodeToMST->distToMST){
            closestNodeToMST = nonMstNode; 
        }
        nonMstNode = nonMstNode->next; 
    }
    removeNode(closestNodeToMST, graph); 
    return closestNodeToMST; 
}
float runTests(int numpoints, int dimension){ 
    Graph* graph = new Graph(numpoints, dimension); 
    float totalWeight = 0.0; 

    // Remove first node of the MST and update the doubly linked list 
    Node* currNode = graph->nonMstVert; 
    graph->nonMstVert = graph->nonMstVert->next; 
    graph->nonMstVert->prev = nullptr; 
    
    while(currNode != nullptr){ 
        totalWeight += currNode->distToMST; 
        currNode = traverseAndGetMin(graph, currNode, dimension); 
    }
    return totalWeight; 
}

int main(int argc, char* argv[]){ 
    if (argc != 5) {
        throw std::invalid_argument("Usage: ./randmst 0 numpoints trials dimension");
    }
    int numpoints = atoi(argv[2]);
    int trials = atoi(argv[3]);
    int dimension = atoi(argv[4]);
    assert(dimension == 0 || dimension == 2 || dimension == 3 || dimension == 4); 
    float weightOfTrials = 0.0; 
    for (int i = 0; i < trials; ++i){ 
        weightOfTrials += runTests(numpoints, dimension); 
        
    } 
    float averageWeight = weightOfTrials / trials; 
    std::cout << averageWeight << " " << numpoints  << " " << trials  << " " << dimension << "\n";
}
