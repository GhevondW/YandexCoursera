#include <iostream>
#include "Node.h"
#include "Inorder.h"
#include "LeftRotate.h"
#include "RightRotate.h"
#include "AVLTree.h"
using namespace std;

/***
 * https://www.programiz.com/dsa/avl-tree
 * 
 * AVL tree is a self-balancing binary search tree in which each node maintains
 * extra information called a balance factor whose value is either -1, 0 or +1.
 * AVL tree got its name after its inventor Georgy Adelson-Velsky and Landis.
 * 
 * Balance Factor
 * Balance factor of a node in an AVL tree is the difference between the height of the left subtree and that of the right subtree of that node.
 *
 * Balance Factor = (Height of Left Subtree - Height of Right Subtree) or (Height of Right Subtree - Height of Left Subtree)
 * The self balancing property of an avl tree is maintained by the balance factor. The value of balance factor should always be -1, 0 or +1.
 * An example of a balanced avl tree is:
 * 
 * 
 *                                  v = value, bf = Balance Factor
 * 
 *                                              (v:33, bf:1)
 *                                               /         \
 *                                     (v:9, bf:-1)        (v:53, bf:-1)
 *                                      /        \                   \
 *                            (v:8, bf:0)       (v:21, bf:1)        (v:61, bf:0)
 *                                               /
 *                                      (v:11, bf:0)
 * 
 * 
 * 
 * Operations on an AVL tree
 * Various operations that can be performed on an AVL tree are:
 *
 * Rotating the subtrees in an AVL Tree
 * In rotation operation, the positions of the nodes of a subtree are interchanged.
 * 
 * There are two types of rotations:
 * 
 * 1) See Left Rotate -> LeftRotate.h
 * 2) See Right Rotate -> RightRotate.h
 * 3) See Algorithm to insert a newNode -> AVLTree.h
 * 
 * */

int main()
{
    cout<<"AVL Tree"<<endl;
/*
    shared_ptr<Node> root = make_shared<Node>(15);
    root->left = make_unique<Node>(10, root.get());
    root->right = make_unique<Node>(25, root.get());
    root->right->right = make_unique<Node>(30, root->right.get());
    root->right->right->right = make_unique<Node>(35, root->right->right.get());
    root->right->left = make_unique<Node>(16, root->right.get());
    root->left->left = make_unique<Node>(8, root->left.get());
    root->left->left->left = make_unique<Node>(5, root->left->left.get());

    if(LeftRotate(root->right.get())) cout<<"True Left"<<endl;

    if(RightRotate(root->left.get())) cout<<"True Right"<<endl;

    PreorderCheckParents(root.get(), nullptr);

    Inorder(root.get(), [](int a)
    {
        cout<<a<<", ";
    });
    cout<<endl;
*/

    AVLTree<int> tree;

    tree.Insert(33);
    tree.Insert(53);
    tree.Insert(13);
    tree.Insert(61);
    tree.Insert(11);
    tree.Insert(21);
    tree.Insert(8);

    // PreorderCheckParents(, nullptr);

    tree.Inorder([](const int& a, int b)
    {
        cout<<"("<<a<<", "<<b<<"), ";
    });
    cout<<endl;

    return 0;
}