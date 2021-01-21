#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <utility>
#include <iostream>
#include <memory>
#include <functional>
#include <stack>

template<typename T>
class AVLTree
{
    using _Type = T;
    struct _Node
    {
        int                     bf{};//Balance Factor      
        _Type                   data{};
        _Node*                  parent{nullptr};
        std::unique_ptr<_Node>  left{nullptr};
        std::unique_ptr<_Node>  right{nullptr};
    };
    
    using _UptrNode = std::unique_ptr<_Node>;
    using _Callback = std::function<void(const _Type&, int)>;

public:
    AVLTree(/* args */) = default;
    ~AVLTree() = default;

    size_t  Size() const { return _size; }

    void    Insert(_Type);
    void    Inorder(_Callback) const;

private:

    //Calculates the max height of the tree
    size_t  _Height(_Node* root) const;
    void    _Inorder(_Node* root, _Callback) const;
    void    _UpdateBalanceFactors(std::stack<_Node*>& path);

private:
    size_t                  _size{};
    std::unique_ptr<_Node>  _root;
};

/***
 * 
 * Algorithm to insert a newNode
 * A (newNode) is always inserted as a leaf node with balance factor equal to 0.
 * 
 * 1) Let the initial tree be:
 * 
 *                                  v = value, bf = Balance Factor
 * 
 *                                              (v:33, bf:1)
 *                                               /         \
 *                                     (v:13, bf:1)        (v:53, bf:-1)
 *                                      /        \                   \
 *                            (v:11, bf:1)       (v:21, bf:0)        (v:61, bf:0)
 *                             /                 
 *                    (v:8, bf:0)
 * 
 * 2) Let the node to be inserted be: 9
 * 3) Do inset operation as usual BST insert
 * 
 * 
 *                                  v = value, bf = Balance Factor
 * 
 *                                              (v:33, bf:1)
 *                                               /         \
 *                                     (v:13, bf:1)        (v:53, bf:-1)
 *                                      /        \                   \
 *                            (v:11, bf:1)       (v:21, bf:0)        (v:61, bf:0)
 *                             /                 
 *                    (v:8, bf:0)
 *                              \
 *                              (v:9, bf:0)
 * 
 * 4) Update Balance Factors
 * 
 *                                  v = value, bf = Balance Factor
 * 
 *                                              (v:33, bf:2)
 *                                               /         \
 *                                     (v:13, bf:2)        (v:53, bf:-1)
 *                                      /        \                   \
 *                            (v:11, bf:2)       (v:21, bf:0)        (v:61, bf:0)
 *                             /                 
 *                    (v:8, bf:-1)
 *                              \
 *                              (v:9, bf:0)
 * 
 * 
 * */

template<class T>
void AVLTree<T>::Insert(_Type new_value)
{
    std::unique_ptr<_Node> new_node = std::make_unique<_Node>();
    new_node->data = std::move(new_value);

    if(_root == nullptr){
        _root = std::move(new_node);
        return;
    }


    const _Type& value = new_node->data;
    _Node* current = _root.get();

    std::stack<_Node*> path;

    while (current != nullptr)
    {
        const _Type& ref = current->data;
        path.push(current);
        if(ref > value)
        {
            if(current->left == nullptr)
            {
                new_node->parent = current;
                current->left = std::move(new_node);
                break;
            }
            current = current->left.get();
        }
        else if(ref < value){
            if(current->right == nullptr)
            {
                new_node->parent = current;
                current->right = std::move(new_node);
                break;
            }
            current = current->right.get();
        }
        else{
            return;
        }
    }

    _UpdateBalanceFactors(path);

    ++_size;
}

template<class T>
void AVLTree<T>::Inorder(_Callback callback) const
{
    if(_root == nullptr) std::cout<<"No Root"<<std::endl;
    _Inorder(_root.get(), callback);
}

//PRIVATE

template<class T>
void AVLTree<T>::_Inorder(_Node* root, _Callback callback) const
{
    if(root == nullptr) return;
    _Inorder(root->left.get(), callback);
    callback(root->data, root->bf);
    _Inorder(root->right.get(), callback);
}

template<class T>
size_t AVLTree<T>::_Height(_Node* root) const
{
    if(root == nullptr) return 0;

    size_t left_height = 1 + _Height(root->left.get());
    size_t right_height = 1 + _Height(root->right.get());

    return left_height > right_height ? left_height : right_height;
}

template<class T>
void AVLTree<T>::_UpdateBalanceFactors(std::stack<_Node*>& path)
{
    while (!path.empty())
    {
        _Node* top = path.top();
        size_t lh = _Height(top->left.get());
        size_t rh = _Height(top->right.get());

        top->bf = lh - rh;

        path.pop();
    }
}

#endif