
#include<stdio.h>
#include<iostream> 
#include<vector> 

// generates MSTs and calculates the average weight of the MST based on number of vertices 
// usage: ./ 0 numpoints, numtrials, dimension 

// argc == number of arguments provided (4 by default). Access these elements by indexing into argv array 

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

    Set find(){
        // printf("%d", this->parent == this); 
        if (this->parent != this){
            Set parent = this->parent->find(); 
            this->parent = &parent; 
        }
        return *this; 
    };    

    void makeUnion(Set nodeToUnionWith){
        
        Set parent1 = this->find(); 
        Set parent2 = nodeToUnionWith.find(); 
        
        parent1.link(parent2); 
    }; 
    // replace two sets containing x and y by their union.   
    void link(Set nodeToLinkWith){
        
        Set smallRankNode = *this; 
        Set largeRankNode = nodeToLinkWith; 
        
        if (smallRankNode.rank > largeRankNode.rank){ 
            Set temp = smallRankNode; 
            smallRankNode = largeRankNode; 
            largeRankNode = temp; 
        }
        // only increase rank when ranks are equal. 
        if(smallRankNode.rank == largeRankNode.rank){ 
            largeRankNode.rank++; 
        }
        // point smaller rank node to larger rank node. 
        smallRankNode.parent = &largeRankNode; 
    }; // connect two nodes with union by rank 
};



int main(int argc, char* argv[]){ 
    printf("no seg");
    std::vector<Set>newSet; 
    newSet.push_back(Set(5)); 
    newSet.push_back(Set(4)); 
    newSet[0].makeUnion(newSet[1]); 
    std::cout << newSet[0].find().vertex << "\n"; 
    std::cout << newSet[1].find().vertex << "\n"; 

}
