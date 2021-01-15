#ifndef _Level_Order_Binary_Tree_Traversal_h_
#define _Level_Order_Binary_Tree_Traversal_h_

#include <iostream>
#include <utility>
#include "Node.h"

size_t Height(Node* node)
{
    if(node == nullptr) return 0;

    size_t left = 1 + Height(node->left.get());
    size_t right = 1 + Height(node->right.get());
    return left > right ? left : right;
}

void PrintLevel(Node* node, size_t level)
{
    if(node == nullptr) return;
    if(level == 0)
    {
        std::cout << node->data << ", ";
    }
    else{
        PrintLevel(node->left.get(), level - 1);
        PrintLevel(node->right.get(), level - 1);
    }
}

void LevelOrderTraversal(Node* ref)
{
    if(ref == nullptr) return;
    auto height = Height(ref);
    for (size_t i = 0; i < height; i++)
    {
        PrintLevel(ref, i);
        std::cout<<std::endl;
    }   
}

#endif