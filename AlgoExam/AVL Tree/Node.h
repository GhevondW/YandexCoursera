#ifndef _NODE_H_
#define _NODE_H_

#include <memory>

struct Node
{
    Node() = default;
    Node(int val, Node* p = nullptr):value(val), parent(p){}
    int value{};
    Node* parent{nullptr};
    std::unique_ptr<Node> left{nullptr};
    std::unique_ptr<Node> right{nullptr};
};


#endif