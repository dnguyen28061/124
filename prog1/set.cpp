#include<stdio.h> 
#include<vector> 
#include"set.h"

struct TreeNode {
    int item;         // The data in this node.
    TreeNode *left;   // Pointer to the left subtree.
    TreeNode *right;  // Pointer to the right subtree.
    std::vector<TreeNode*> children; 
}; 

Set Set::Set(int x){

};     

// return the name of the group containing x 
int Set::find(int x){

};    

void Set::makeUnion(int x, int y){

}; // replace two sets containing x and y by their union.

void Set::link(int x, int y){

}; // connect two nodes with union by rank 