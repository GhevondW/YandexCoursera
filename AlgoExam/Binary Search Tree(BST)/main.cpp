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
 *    d) Delete
 * 
 * */

int main()
{
    cout<< "BST" << endl;

    BST<int> set;

    set.Insert(8);
    set.Insert(3);
    set.Insert(1);
    set.Insert(1);
    set.Insert(6);
    set.Insert(4);
    set.Insert(7);
    set.Insert(30);
    set.Insert(25);
    set.Insert(28);

    set.Inorder([](const int& a)
    {
        cout<<a<<", ";
    });
    cout<<endl;

    cout<<"Size"<<endl;
    cout<<set.Size()<<endl;

    cout<<"Find"<<endl;
    cout<<set.Find(6)<<endl;
    cout<<set.Find(66)<<endl;

    set.Delete(8);
    set.Delete(1);
    set.Delete(6);
    set.Delete(25);
    set.Delete(3);
    set.Delete(4);
    set.Delete(7);

    set.Inorder([](const int& a)
    {
        cout<<a<<", ";
    });
    cout<<endl;

    set.Delete(28);

    set.Inorder([](const int& a)
    {
        cout<<a<<", ";
    });
    cout<<endl;

    set.Delete(30);

    set.Inorder([](const int& a)
    {
        cout<<a<<", ";
    });
    cout<<endl;

    return 0;
}