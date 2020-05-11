/* Author: Thomas Woeste
 * Program: trees.cpp
 * Date: 2/14/2020
 * Purpose: The purpose of this program is to implement a binary search tree using a struct to represent
 *          a tree node that has X,Y, and Z data. It also has a pointer to a left and right tree node. 
 *          There are functions to make a new node with the correct data, search the tree for a key,
 *          insert a node into a tree, print a node, and copy a node into a new tree. There are also 3
 *          functions to interate through the tree in different orders. 
*/

#include <iostream>

using namespace std; 

//This represents a leaf on the tree. It has a pointer to a left and right child
struct treeNode {
    int Xdata;
    int Ydata;
    int Zdata;
    treeNode *left;
    treeNode *right;
}; //treeNode

//The makeNode function creates a new treeNode making its left and right child's null 
treeNode* makeNode(int Xdata, int Ydata, int Zdata) {
    treeNode* answer = new treeNode;
    answer->Xdata = Xdata;
    answer->Ydata = Ydata;
    answer->Zdata = Zdata;
    answer->left = answer->right = NULL;
    return answer;
} //makeNode()

//Searches the tree until it finds the closets node to the search key. 
treeNode* searchTree(treeNode* tree, int key){
    //search function is based on the Ydata of the nodes
    //Base Case
    if(tree == NULL){
        return NULL;
    }
    else if(tree->Ydata == key){
        return tree;
    }
    else if(key < tree->Ydata){
        if(tree->left == NULL) {
            return tree; 
        }
        return (searchTree(tree->left,key));
    }
    else {
        if(tree->right == NULL){
            return tree;
        }
        return (searchTree(tree->right,key));
    }
} //searchTree()

//Function to insert a node into the tree based on the x value.
void insertTreeX(treeNode* tree, int Xvalue, int Yvalue, int Zvalue) {
    treeNode* parent = NULL;
    treeNode* newNode = makeNode(Xvalue, Yvalue, Zvalue);

    //Goes down the tree and takes the left child if it is a tie or less
    //Otherwise it takes the right child until it finds the place to insert
    //into the tree
    while(tree != NULL) {
        parent = tree;
        if(Xvalue <= tree->Xdata)
            tree = tree->left;
        else
            tree = tree->right;
    }
    if(Xvalue <= parent->Xdata)
        parent->left = newNode;
    else
        parent->right = newNode;
} //insertTreeX()

//Function to insert a node into the tree based on the y value.
void insertTreeY(treeNode* tree, int Xvalue, int Yvalue, int Zvalue) {
    treeNode* parent = NULL;
    treeNode* newNode = makeNode(Xvalue, Yvalue, Zvalue);
    //Goes down the tree and takes the left child if it is a tie or less
    //Otherwise it takes the right child until it finds the place to insert
    //into the tree
    while(tree != NULL) {
        parent = tree;
        if(Yvalue <= tree->Ydata)
            tree = tree->left;
        else
            tree = tree->right;
    }
    if(Yvalue <= parent->Ydata)
        parent->left = newNode;
    else
        parent->right = newNode;
} //insertTreeY()

//This function visits each node in the passed in tree then copys the node to the 
//other passed in tree.
void visitCopy(treeNode* tree, treeNode* treeCopy) {
    if(treeCopy == NULL){
        treeCopy = makeNode(tree->Xdata, tree->Ydata, tree->Zdata);
    }
    else{
        insertTreeY(treeCopy, tree->Xdata, tree->Ydata, tree->Zdata);
    }
} //visitCopy()

//This function takes the given pointer to a treeNode and prints each data point.
void visitPrint(treeNode* tree) {
    cout << "(" << tree->Xdata << ", " << tree->Ydata << ", " << tree->Zdata << ")" << endl;
} //visitPrint()

//This function goes down the left side of the tree then prints the tree from bottom up.
//Then goes down the right side from top to bottom. If the tree is empty it does not print
//anything. 
void symmetric(treeNode* tree) {
    if(tree == NULL) {}
    else{
        symmetric(tree->left);
        visitPrint(tree);
        symmetric(tree->right);
    }
} //symmetric()

//This function copys the passed in tree to newTree first starting with the first node.
//Then goes down the left side of the tree copying from the top down then down the right side.
void preorder(treeNode* tree, treeNode* newTree) {
    if(tree == NULL) {}
    else{
        visitCopy(tree, newTree);
        preorder(tree->left, newTree);
        preorder(tree->right, newTree);
    }
} //preorder()

//This function Starts the preorder function above so it can go down each side properly
void startPreOrder(treeNode* tree, treeNode* newTree) {
    preorder(tree->left, newTree);
    preorder(tree->right, newTree);
} //startPreOrder()

//This function starts going down all the way down the right side of the tree then prints
//all the nodes on the right then down the left.
void postorder(treeNode* tree) {
    if(tree == NULL) {}
    else{
        postorder(tree->left);
        postorder(tree->right);
        visitPrint(tree);
    }
} //postorder()




const int ARGUMENTS = 2;

int main(int argc, char* argv[]) {
    //Error cheching to make sure 1 Argument is ran with the program.
    if(argc != ARGUMENTS){
         cout << "Warning: need exactly"  << ARGUMENTS - 1 << " command line arguments." << endl;
         return 1;
    }
    //Converts the argv value ot a int.
    const int NUMDATA = atoi(argv[1]);
    
    //The tree is empty if you want to run the program with 0 nodes
    if(NUMDATA == 0) {
        cout << "The tree is empty" << endl;
        return 0;
    }

    //Makes sure to build the tree with atleast 0 data element.
    if(NUMDATA < 0){
        return 1;
    }

    int xData = 0;
    int yData = 0;
    int zData = 0;
    
    //Input the data for the first node of the tree
    cin >> xData >> yData >> zData;
    treeNode* T1 = makeNode(xData,yData,zData);
    //Inserts the rest of the data into the tree.
    for(int itr = 2; itr <= NUMDATA; itr++){
        cin >> xData >> yData >> zData;
        insertTreeX(T1, xData, yData, zData);
    }
    //Prints the tree in symmetric order
    symmetric(T1);

    //Makes a new tree with the same first node as the old tree.
    treeNode* T2 = makeNode(T1->Xdata,T1->Ydata,T1->Zdata);
    //Copys the elemets of T1 into T2 in PreOrder
    startPreOrder(T1,T2);
    //Prints the elements of T2 in postorder
    postorder(T2);
    
    //Inputs the new key to compare T2 to. 
    int newData = 0;
    cin >> newData;
    //Creates a new node that points to the closest node in T2 that is close to the imputed key
    treeNode* closestNode = searchTree(T2,newData);
    visitPrint(closestNode);
    
    return 0;
} //main()







