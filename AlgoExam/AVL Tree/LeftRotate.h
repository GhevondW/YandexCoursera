#ifndef _LEFT_ROTATE_H_
#define _LEFT_ROTATE_H_

#include "Node.h"


/***
 * 
 * In left-rotation, the arrangement of the nodes on the right is transformed into the arrangements on the left node.
 * Algorithm
 * 
 * 1. Let the initial tree be:
 *                                                  p
 *                                                  |
 *                                                 (x)
 *                                                /   \
 *                                               a     (y)
 *                                                    /   \
 *                                                   b     g
 * 
 * 
 * 2. If (y) has a left subtree, assign (x) as the parent of the left subtree of (y).
 * 
 *                                                  p
 *                                                  |
 *                                                 (x)
 *                                                /   \
 *                                               a     b        (y)
 *                                                             /   \
 *                                                                  g
 * 
 * 3. If the parent of (x) is NULL, make (y) as the root of the tree.
 * 4. Else if (x) is the left child of (p), make (y) as the left child of (p).
 * 5. Else assign (y) as the right child of (p).
 * 
 *                                                  
 *                                                  
 *                                                 (x)           p
 *                                                /   \          |
 *                                               a     b        (y)
 *                                                             /   \
 *                                                                  g
 * 
 * 6. Make (y) as the parent of (x).
 * 
 *                                                  p
 *                                                  |
 *                                                 (y)
 *                                                /   \
 *                                              (x)    g
 *                                             /   \
 *                                            a     b
 * 
 * */

bool LeftRotate(Node* current)
{
    if(current == nullptr || current->right == nullptr) return false;
    std::unique_ptr<Node> extracted_right = std::move(current->right);
    extracted_right->parent = nullptr;

    std::unique_ptr<Node> extracted_top{nullptr};

    Node* p = current->parent;
    if(p == nullptr) return false;

    bool left = p->left.get() == current;
    if(left){
        extracted_top = std::move(p->left);
    }
    else{
        extracted_top = std::move(p->right);
    }
    extracted_top->parent = nullptr;

    extracted_top->right = std::move(extracted_right->left);
    if(extracted_top->right.get()) 
        extracted_top->right->parent = extracted_top.get();


    extracted_right->parent = p;
    extracted_top->parent = extracted_right.get();
    if(left){
        p->left = std::move(extracted_right);
        p->left->left = std::move(extracted_top);
    }
    else{
        p->right = std::move(extracted_right);
        p->right->left = std::move(extracted_top);
    }
    return true;
}

#endif