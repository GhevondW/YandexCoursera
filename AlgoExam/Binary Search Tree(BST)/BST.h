#ifndef _BST_H_
#define _BST_H_

#include <utility>
#include <iostream>
#include <memory>
#include <functional>

/***
 *
 * The following is the definition of Binary Search Tree(BST) according to Wikipedia
 * Binary Search Tree is a node-based binary tree data structure which has the following properties:
 *
 *  1)The left subtree of a node contains only nodes with keys lesser than the node’s key.
 *  2)The right subtree of a node contains only nodes with keys greater than the node’s key.
 *  3)The left and right subtree each must also be a binary search tree.
 *  There must be no duplicate nodes.
 *
 * Example
 *
 *                                        8
 *                                      /   \
 *                                     3     10
 *                                   /  \       \
 *                                  1    6      14
 *                                     /   \    /
 *                                    4    7   13
 *
 * The above properties of Binary Search Tree provides an ordering among keys so that the operations like search,
 * minimum and maximum can be done fast. If there is no ordering, then we may have to compare every key to search for a given key.
 *
 * */


template<class T>
class BST
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
    BST(/* args */) = default;
    ~BST() = default;

    auto Size() const { return _size; }
    auto Empty() const { return _size == 0; }

    //Checks the existence of the object
    bool Find(const _Type& data) const; //O(log(n))
    
    //Inserts the new element
    void Insert(const _Type& data); //O(log(n))
    // void Insert(_Type&& data);

    //Delete the node by key
    //This operation does not allocate new memory it only moves the node
    void Delete(const _Type& data); //O(log(n))

    //Inorder Traversal with callback
    void Inorder(std::function<void(const _Type&)> callback) const; //O(n)

private:

    //Inorder traversal function with callback
    void _Inorder(_Node* ref, std::function<void(const _Type&)> callback) const;
    
    //Find the node by key
    const _Node* _Find(const _Type&) const;

    //Find the node by key
    _Node* _Find(const _Type&);

    //Find the minimum value node in tree
    _UptrNode _ExtractMinValueNode(_Node* root);

private:
    size_t _size{0};
    std::unique_ptr<_Node> _root{nullptr};
};


/***
 *
 * For searching a value, if we had a sorted array we could have performed a binary search.
 *
 * Search operation in binary search tree will be very similar.
 * Let’s say we want to search for the number, what we’ll do is we’ll start at the root, and then we will compare
 * the value to be searched with the value of the root if it’s equal we are done with the search if it’s lesser we
 * know that we need to go to the left subtree because in a binary search tree all the elements in the left subtree
 * are lesser and all the elements in the right subtree are greater. Searching an element in the binary search tree
 * is basically this traversal in which at each step we will go either towards left or right and hence in at each step
 * we discard one of the sub-trees. If the tree is balanced, we call a tree balanced if for all nodes the difference
 * between the heights of left and right subtrees is not greater than one, we will start with a search space of ‘n’nodes
 * and when we will discard one of the sub-trees we will discard ‘n/2’ nodes so our search space will be reduced to ‘n/2’
 * and then in the next step we will reduce the search space to ‘n/4’ and we will go on reducing like this till we find the
 * element or till our search space is reduced to only one node. The search here is also a binary search and that’s why the
 * name binary search tree.
 *
 * */

template<class T>
bool BST<T>::Find(const _Type& value) const
{
    return _Find(value) != nullptr;
}

template<class T>
auto BST<T>::_Find(const _Type& value) const -> const typename BST<T>::_Node*
{
    _Node* current = _root.get();
    while (current != nullptr)
    {
        if(current->data == value) break;
        
        if(current->data > value)
            current = current->left.get();
        else
            current = current->right.get();
    }
    return current;
}

template<class T>
auto BST<T>::_Find(const _Type& value) -> typename BST<T>::_Node*
{
    _Node* current = _root.get();
    while (current != nullptr)
    {
        if(current->data == value) break;
        
        if(current->data > value)
            current = current->left.get();
        else
            current = current->right.get();
    }
    return current;
}

/***
 *
 * Insertion of a key
 * A new key is always inserted at the leaf.
 * We start searching a key from the root until we hit a leaf node. Once a leaf node is found,
 * the new node is added as a child of the leaf node.
 *
 * */

template<class T>
void BST<T>::Insert(const _Type& value)
{
    if(Find(value)) return;
    
    if(_root == nullptr){
        _root = std::make_unique<_Node>();
        _root->data = value;
    }
    else{
        auto new_node = std::make_unique<_Node>();
        new_node->data = value;

        _Node* current = _root.get();

        while (true)
        {
            const _Type& ref = current->data;
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
            else{
                if(current->right == nullptr)
                {
                    new_node->parent = current;
                    current->right = std::move(new_node);
                    break;
                }
                current = current->right.get();
            }
        }
    }
    ++_size;
}

//Delete the node by key

/***
 *
 * There are three cases for deleting a node from a binary search tree.
 * Case I
 * In the first case, the node to be deleted is the leaf node. In such a case, simply delete the node from the tree.
 *
 * Case II
 * In the second case, the node to be deleted lies has a single child node. In such a case follow the steps below:
 * 1. Replace that node with its child node.
 * 2. Remove the child node from its original position.
 *
 * Case III
 * In the third case, the node to be deleted has two children. In such a case follow the steps below:
 * 1. Get the inorder successor of that node.
 * 2. Replace the node with the inorder successor.
 * 3. Remove the inorder successor from its original position.
 *
 * */

template<class T>
void BST<T>::Delete(const _Type& data)
{
    _Node* node = _Find(data);
    if(node == nullptr) return;

    _Node* p = node->parent;

    if(node->left == nullptr){
        std::unique_ptr<_Node> new_node = std::move(node->right);
        if(new_node != nullptr){
            new_node->parent = p;
        }
        
        if(p == nullptr){
            _root = std::move(new_node);
        }
        else{
            if(p->left.get() == node)
                p->left = std::move(new_node);
            else
                p->right = std::move(new_node);
        }
    }
    else if(node->right == nullptr){
        std::unique_ptr<_Node> new_node = std::move(node->left);
        if(new_node != nullptr){
            new_node->parent = p;
        }
        
        if(p == nullptr){
            _root = std::move(new_node);
        }
        else{
            if(p->left.get() == node)
                p->left = std::move(new_node);
            else
                p->right = std::move(new_node);
        }
        if(new_node != nullptr){
            new_node->parent = p;
        }
    }
    else{
        std::unique_ptr<_Node> extracted_min{_ExtractMinValueNode(node->right.get())};

        extracted_min->left = std::move(node->left);
        if(extracted_min->left != nullptr){
            extracted_min->left->parent = extracted_min.get();
        }
        extracted_min->right = std::move(node->right);
        if(extracted_min->right != nullptr){
            extracted_min->right->parent = extracted_min.get();
        }
        extracted_min->parent = p;
        if(p == nullptr){
            _root = std::move(extracted_min);
        }
        else{
            if(p->left.get() == node)
                p->left = std::move(extracted_min);
            else
                p->right = std::move(extracted_min);
        }
    }
    --_size;
}

template<class T>
auto BST<T>::_ExtractMinValueNode(_Node* root) -> BST<T>::_UptrNode
{
    _Node* current = root;

    // Find the leftmost leaf
    while (current && current->left != nullptr)
        current = current->left.get();

    _UptrNode right = std::move(current->right);
    _UptrNode ret{nullptr};
    _Node* p = current->parent;

    if(right != nullptr)
    {
        right->parent = p;
    }

    if(p->left.get() == current){
        ret = std::move(p->left);
        p->left = std::move(right);
    }
    else{
        ret = std::move(p->right);
        p->right = std::move(right);
    }

    return ret;
}

//Basic Inorder traversal
template<class T>
void BST<T>::Inorder(std::function<void(const _Type&)> callback) const
{
    _Inorder(_root.get(), callback);
}

template<class T>
void BST<T>::_Inorder(_Node* ref, std::function<void(const _Type&)> callback) const
{
    if(ref == nullptr) return;
    _Inorder(ref->left.get(), callback);
    callback(ref->data);
    _Inorder(ref->right.get(), callback);
}

#endif
