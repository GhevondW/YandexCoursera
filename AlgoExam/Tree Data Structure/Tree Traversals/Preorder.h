#ifndef _PREORDER_H_
#define _PREORDER_H_

#include "Node.h"
#include <iostream>

/***
 * 
 * Preorder Traversal (Practice):
 *
 * Algorithm Preorder(tree)
 *    1. Visit the root.
 *    2. Traverse the left subtree, i.e., call Preorder(left-subtree)
 *    3. Traverse the right subtree, i.e., call Preorder(right-subtree) 
 * Uses of Preorder
 * Preorder traversal is used to create a copy of the tree. 
 * Preorder traversal is also used to get prefix expression on of an expression tree.
 * Please see http://en.wikipedia.org/wiki/Polish_notation to know why prefix expressions are useful.
 *
 **/

void Preorder(Node* ref)
{
    if(ref == nullptr) return;
    std::cout << ref->data << std::endl;
    Preorder(ref->left.get());
    Preorder(ref->right.get());
}

void _Copy(Node* to, Node* from)
{
    if(from == nullptr || to == nullptr) return;
    to->data = from->data;
    if(from->left != nullptr)
    {
        to->left = std::make_unique<Node>();
        _Copy(to->left.get(), from->left.get());
    }

    if(from->right != nullptr)
    {
        to->right = std::make_unique<Node>();
        _Copy(to->right.get(), from->right.get());
    }
}

std::shared_ptr<Node> Copy(Node* root)
{
    if(root == nullptr) return nullptr;
    std::shared_ptr<Node> ret = std::make_shared<Node>();
    _Copy(ret.get(), root);
    return ret;
}

#endif