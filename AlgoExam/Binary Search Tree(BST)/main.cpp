#include <iostream>
#include <set>
#include "BST.h"
using namespace std;

/***
 * 
 * Binary Search Tree
 * 
 * 1) BST.h
 *    a) Find
 *    b) Insert
 *    c) Inorder Traversal
 * 
 * */

int main()
{
    cout<< "BST" << endl;

    BST<int> set;

    set.Insert(8);
    set.Insert(3);
    set.Insert(10);
    set.Insert(1);
    set.Insert(6);
    set.Insert(14);
    set.Insert(4);
    set.Insert(7);
    set.Insert(13);

    set.Inorder([](const int& a)
    {
        cout<<a<<endl;
    });

    cout<<set.Size()<<endl;

    return 0;
}