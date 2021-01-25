//
//  main.cpp
//  RedBlackTree
//
//  Created by Ghevond Gevorgyan on 23.01.21.
//

#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    std::cout << "Red-Black Tree:" << std::endl;
    
    Tree<int>::TreePrinter printer{};
    
    
    Tree<int> tree;
    
    tree.Insert(30);
    tree.Insert(10);
    tree.Insert(65);
    tree.Insert(25);
    
    printer(tree);
    
    return 0;
}
