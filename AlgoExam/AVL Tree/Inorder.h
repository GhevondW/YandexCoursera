#ifndef _INORDER_H_
#define _INORDER_H_

#include <functional>
#include <iostream>
#include "Node.h"

void Inorder(Node* root, std::function<void(int)> callback)
{
    if(root == nullptr) return;

    Inorder(root->left.get(), callback);
    callback(root->value);
    Inorder(root->right.get(), callback);
}

void PreorderCheckParents(Node* root, Node* parent)
{
    if(root == nullptr) return;
    if(root->parent == parent){
        std::cout<<"OK:"<<root->value<<std::endl;
    }
    else{
        std::cout<<"Error:"<<root->value<<std::endl;
    }

    PreorderCheckParents(root->left.get(), root);
    PreorderCheckParents(root->right.get(), root);
}

#endif