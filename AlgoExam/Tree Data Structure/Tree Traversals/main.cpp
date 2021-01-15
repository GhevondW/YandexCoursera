#include <iostream>
#include "Node.h"
#include "Inorder.h"
#include "Postorder.h"
#include "Preorder.h"
#include "LevelOrderBinaryTreeTraversal.h"
using namespace std;

/***
 * Unlike linear data structures (Array, Linked List, Queues, Stacks, etc) 
 * which have only one logical way to traverse them, trees can be traversed 
 * in different ways. Following are the generally used ways for traversing trees.
 * 
 * Depth First Traversals:
 * (a) Inorder (Left, Root, Right) : 4 2 5 1 3                        1
 * (b) Preorder (Root, Left, Right) : 1 2 4 5 3                      /  \
 * (c) Postorder (Left, Right, Root) : 4 5 2 3 1                    2    3
 *                                                                 / \   
 *                                                                4   5
 *
 *
 * Algorithm Inorder(tree)
 * 1. Traverse the left subtree, i.e., call Inorder(left-subtree)
 * 2. Visit the root.
 * 3. Traverse the right subtree, i.e., call Inorder(right-subtree)
 * Time Complexity: O(n)
 * 
 * 
 * Algorithm Preorder(tree)
 * 1. Visit the root.
 * 2. Traverse the left subtree, i.e., call Preorder(left-subtree)
 * 3. Traverse the right subtree, i.e., call Preorder(right-subtree) 
 * Time Complexity: O(n)
 * 
 * 
 * Algorithm Postorder(tree)
 * 1. Traverse the left subtree, i.e., call Postorder(left-subtree)
 * 2. Traverse the right subtree, i.e., call Postorder(right-subtree)
 * 3. Visit the root.
 * Time Complexity: O(n)
 * 
 * 
 ***/
int main()
{
    cout<<"Tree Traversal"<<endl;

/***
 *  Example
 *                         10
 *                       /    \
 *                      20     9
 *                     /  \   /  \
 *                    6    5  4   nullptr
 *                          \
 *                          12
 */

    std::shared_ptr<Node> root = std::make_shared<Node>(10);
    
    root->left                  = std::make_unique<Node>(20);
    root->left->left            = std::make_unique<Node>(6);
    root->left->right           = std::make_unique<Node>(5);
    root->right                 = std::make_unique<Node>(9);
    root->right->left           = std::make_unique<Node>(4);
    root->left->right->right    = std::make_unique<Node>(12);

    cout<<"Inorder"<<endl;
    Inorder(root.get());

    cout<<"Postorder"<<endl;
    Postorder(root.get());

    cout<<"Preorder"<<endl;
    Preorder(root.get());

    auto copy = Copy(root.get());

    cout<<"Inorder Copy"<<endl;
    Inorder(copy.get());

    auto height = Height(root.get());
    cout<<"Height:"<<height<<endl;

    cout<<"LevelOrderTraversal"<<height<<endl;
    LevelOrderTraversal(root.get());

    return 0;
}