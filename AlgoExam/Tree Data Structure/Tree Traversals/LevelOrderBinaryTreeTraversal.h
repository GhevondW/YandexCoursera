#ifndef _Level_Order_Binary_Tree_Traversal_h_
#define _Level_Order_Binary_Tree_Traversal_h_

#include <iostream>
#include <utility>
#include "Node.h"

/***
 * 
 * Algorithm: 
 There are basically two functions in this method. One is to print all nodes at a given level (printGivenLevel),
 and other is to print level order traversal of the tree (printLevelorder).
 printLevelorder makes use of printGivenLevel to print nodes at all levels one by one starting from root.
 * 
 * 
 * Time Complexity: 
 * O(n^2) in worst case. For a skewed tree, printGivenLevel() takes O(n) time where n is the number of nodes in the skewed tree.
 * So time complexity of printLevelOrder() is O(n) + O(n-1) + O(n-2) + .. + O(1) which is O(n^2). 
 *   
 * Space Complexity: 
 * O(n) in worst case. For a skewed tree,
 * printGivenLevel() uses O(n) space for call stack.
 * For a Balanced tree, call stack uses O(log n) space, (i.e., height of the balanced tree). 
 * 
 * */

/***
 * Method 2 (Using queue)
 *
 * Algorithm: 
 * For each node, first the node is visited and then it’s child nodes are put in a FIFO queue. 
 * 
 * printLevelorder(tree)
 *  a) Create an empty queue q
 *  b) temp_node = root //start from root
 *  c) Loop while temp_node is not NULL
 *      a) print temp_node->data.
 *      b) Enqueue temp_node’s children 
 *      (first left then right children) to q
 *      c) Dequeue a node from q.
 * 
 * Time Complexity: O(n) where n is number of nodes in the binary tree 
 * Space Complexity: O(n) where n is number of nodes in the binary tree 
 * 
 * */

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