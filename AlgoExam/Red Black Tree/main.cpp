//
//  main.cpp
//  RedBlackTree
//
//  Created by Ghevond Gevorgyan on 23.01.21.
//

#include <iostream>
#include "Tree.h"

using namespace std;

/*
 
 Red-Black tree is a self-balancing binary search tree in which each node contains an extra bit for denoting the color of the node, either red or black.

 A red-black tree satisfies the following properties:

 1. Red/Black Property: Every node is colored, either red or black.
 2. Root Property: The root is black.
 3. Leaf Property: Every leaf (NIL) is black.
 4. Red Property: If a red node has children then, the children are always black.
 5. Depth Property: For each node, any simple path from this node to any of its descendant leaf has the same black-depth (the number of black nodes).
 
 An example of a red-black tree is:
 
 //Always make null child nodes as black leaves
 
 [] - red nodes
 () - black nodes
 /\ - this means that the node has two empty black leaves
 
                                                       (33)
                                                     /      \
                                                [13]           (53)
                                             /      \         /      \
                                          (11)      (21)      [41]     [61]
                                           /\     /      \     /\       /\
                                                 [15]    [31]
                                                  /\      /\
 */

int main(){
    std::cout << "Red-Black Tree:" << std::endl;
    
    Tree<int>::TreePrinter printer{};
    
    
    Tree<int> tree;
    
    tree.Insert(30);
    tree.Insert(25);
    tree.Insert(20);
    tree.Insert(15);
    tree.Insert(10);
    
    printer(tree);
    
    std::cout<<"Parents:"<<tree.CheckParents()<<std::endl;
    
    return 0;
}
