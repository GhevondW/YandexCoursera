//
//  main.cpp
//  Tree
//
//  Created by Ghevond Gevorgyan on 11.02.21.
//

#include <iostream>
#include "BPTree.h"
#include "BTree.h"

int main(int argc, const char * argv[]) {
    
    BPTree node;
    node.insert(5);
    node.insert(15);
    node.insert(25);
    node.insert(35);
    node.insert(45);
    node.insert(55);
    node.insert(40);
    node.insert(30);
    node.insert(20);
    node.display(node.getRoot());
    
    node.search(15);
    
    std::cout<<"--------------------------------------"<<std::endl;
    
    geek::BTree t(3); // A B-Tree with minium degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
  
    cout << "Traversal of the constucted tree is ";
    t.traverse();
  
    int k = 6;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
  
    k = 15;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
  
    return 0;
}
