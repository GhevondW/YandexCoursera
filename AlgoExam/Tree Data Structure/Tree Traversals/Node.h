#ifndef _NODE_H_
#define _NODE_H_

#include <utility>
#include <memory>

struct Node
{
    int data{};
    std::unique_ptr<Node> left{nullptr};
    std::unique_ptr<Node> right{nullptr};

    Node() = default;
    Node(int d):data(d){}

};


#endif