#ifndef _RIGHT_ROTATE_H_
#define _RIGHT_ROTATE_H_

#include "Node.h"


/***
 * 
 * In right-rotation, the arrangement of the nodes on the left is transformed into the arrangements on the right node.
 * Algorithm
 * 
 * 1. Let the initial tree be:
 *                                                  p
 *                                                  |
 *                                                 (y)
 *                                                /   \
 *                                              (x)    a
 *                                             /   \
 *                                            g     b
 * 
 * 
 * 2. If (x) has a right subtree, assign (y) as the parent of the right subtree of (x)
 * 
 *                                                  p
 *                                                  |
 *                                                 (y)
 *                                                /   \
 *                                               b     a        (x)
 *                                                             /   \
 *                                                            g     
 * 
 * 3. If the parent of (y) is NULL, make (x) as the root of the tree.
 * 4. Else if (y) is the right child of its parent (p), make (x) as the right child of (p).
 * 5. Else assign (x) as the left child of (p).
 * 
 *                                                  
 *                                                  
 *                                                 (y)           p
 *                                                /   \          |
 *                                               b     a        (x)
 *                                                             /   \
 *                                                            g     
 * 
 * 6. Make x as the parent of y.
 * 
 *                                                  p
 *                                                  |
 *                                                 (x)
 *                                                /   \
 *                                               g     (y)
 *                                                    /   \
 *                                                   b     a
 * 
 * */

bool RightRotate(Node* current) //O(1)
{
    if(current == nullptr || current->left == nullptr) return false;
    std::unique_ptr<Node> extracted_top{nullptr};
    std::unique_ptr<Node> extracted_left{nullptr};

    Node* p = current->parent;
    if(p == nullptr) return false;

    bool right = p->right.get() == current;
    if(right)
        extracted_top = std::move(p->right);
    else
        extracted_top = std::move(p->left);

    extracted_top->parent = nullptr;
    
    extracted_left = std::move(extracted_top->left);
    extracted_left->parent = nullptr;

    extracted_top->left = std::move(extracted_left->right);
    if(extracted_top->left != nullptr){
        extracted_top->left->parent = extracted_top.get();
    }

    extracted_left->parent = p;
    extracted_left->right = std::move(extracted_top);
    extracted_left->right->parent = extracted_left.get();
    if(right)
        p->right = std::move(extracted_left);
    else
        p->left = std::move(extracted_left);

    return true;
}

#endif