
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
        Set newSet = Set(i); 
        setList.push_back(&newSet); 
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




}
