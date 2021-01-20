#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <utility>
#include <iostream>
#include <memory>
#include <functional>

template<typename T>
class AVLTree
{
    using _Type = T;
    struct _Node
    {
        _Type data{};
        _Node* parent{nullptr};
        std::unique_ptr<_Node> left{nullptr};
        std::unique_ptr<_Node> right{nullptr};
    };
    using _UptrNode = std::unique_ptr<_Node>;

public:
    AVLTree(/* args */);
    ~AVLTree();

private:
    size_t                  _size{};
    std::unique_ptr<_Node>  _root;
};



#endif