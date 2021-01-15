#ifndef _INORDER_H_
#define _INORDER_H_

#include "Node.h"
#include <iostream>

/***
 * 
 * 
 * Inorder Traversal (Practice):
 * Algorithm Inorder(tree)
 *   1. Traverse the left subtree, i.e., call Inorder(left-subtree)
 *   2. Visit the root.
 *   3. Traverse the right subtree, i.e., call Inorder(right-subtree)
 * 
 * Uses of Inorder
 * In case of binary search trees (BST), Inorder traversal gives nodes in non-decreasing order.
 * To get nodes of BST in non-increasing order, a variation of Inorder traversal where Inorder traversal s reversed can be used.
 *
 **/

void Inorder(Node* ref)
{
    if(ref == nullptr) return;
    Inorder(ref->left.get());
    std::cout << ref->data << std::endl;
    Inorder(ref->right.get());
}

#endif