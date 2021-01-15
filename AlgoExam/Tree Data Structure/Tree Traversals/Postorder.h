#ifndef _POSTORDER_H_
#define _POSTORDER_H_

#include "Node.h"
#include <iostream>


/***
 *
 * Postorder Traversal (Practice):
 * 
 * Algorithm Postorder(tree)
 *    1. Traverse the left subtree, i.e., call Postorder(left-subtree)
 *    2. Traverse the right subtree, i.e., call Postorder(right-subtree)
 *    3. Visit the root.
 * Uses of Postorder
 * Postorder traversal is used to delete the tree. 
 * Please see the question for deletion of tree for details. 
 * Postorder traversal is also useful to get the postfix expression of an expression tree. 
 * Please see http://en.wikipedia.org/wiki/Reverse_Polish_notation to for the usage of postfix expression. 
 * Time Complexity: O(n)
 **/

void Postorder(Node* ref)
{
    if(ref == nullptr) return;
    Postorder(ref->left.get());
    Postorder(ref->right.get());
    std::cout << ref->data << std::endl;
}

#endif