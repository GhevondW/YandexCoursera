//
//  Tree.h
//  RedBlackTree
//
//  Created by Ghevond Gevorgyan on 25.01.21.
//

#ifndef Tree_h
#define Tree_h

#include <iostream>

template<class T>
class Tree
{
public:
    using _Type = T;
    struct Node
    {
        Node() = default;
        explicit Node(const _Type& val)
        :data(val)
        {}
        ~Node() = default; //{ std::cout<<"Node Dtor"<<std::endl; }
        _Type data{};
        Node* parent{nullptr};
        Node* left{nullptr};
        Node* right{nullptr};
        bool  red{true};
    };
    
    struct TreePrinter
    {
        void operator()(const Tree& tree)
        {
            std::cout<<"-----PRINT-----"<<std::endl;
            const Node* root = tree._root;
            _Inorder(root);
            std::cout<<"---PRINT End---"<<std::endl;
        }
        
    private:
        void _Inorder(const Node* root) const
        {
            if(root == nullptr) return;
            _Inorder(root->left);
            std::cout<<"("<<root->data<<", "<<root->red<<") "<<std::endl;
            _Inorder(root->right);
        }
    };
    
public:
    
    Tree() = default;
    Tree(const Tree& other) = delete;
    Tree(Tree&& other) = delete;
    ~Tree(){
        _Destroy(_root);
        _root = nullptr;
    }
    
    Tree& operator=(const Tree&) = delete;
    Tree& operator=(Tree&&) = delete;
    
public:
    
    void    Insert(const _Type& data);
    bool    CheckParents() const;
    
private:
    
    void    _Destroy(Node* root);
    Node*   _InsertLeaf(const _Type& data);
    bool    _CheckParents(Node* root, Node* parent = nullptr) const;
    
private:
    Node* _root{nullptr};
};

//PUBLIC

template<class T>
void Tree<T>::Insert(const _Type& data)
{
    if(_root == nullptr)
    {
        _root = new Node(data);
        _root->red = false;
    }
    else{
        _InsertLeaf(data);
    }
}

template<class T>
bool Tree<T>::CheckParents() const
{
    return _CheckParents(_root);
}

//PRIVATE

template<class T>
void Tree<T>::_Destroy(Node* root)
{
    if(root == nullptr) return;
    _Destroy(root->left);
    _Destroy(root->right);
    delete root;
}

template<class T>
auto Tree<T>::_InsertLeaf(const _Type& data) -> typename Tree<T>::Node*
{
    Node* current = _root;
    while (current) {
        if(current->data > data){
            if(current->left == nullptr)
            {
                current->left = new Node{data};
                current->left->parent = current;
                return current->left;
            }
            current = current->left;
        }
        else if(current->data < data){
            if(current->right == nullptr)
            {
                current->right = new Node{data};
                current->right->parent = current;
                return current->right;
            }
            current = current->left;
        }
        else{
            return nullptr;
        }
    }
    return nullptr;
}

template<class T>
bool Tree<T>::_CheckParents(Node* root, Node* parent /*= nullptr*/) const
{
    if(root == nullptr) return true;
    if(root->parent != parent) return false;
    auto left = _CheckParents(root->left, root);
    auto right = _CheckParents(root->right, root);
    return left && right;
}

#endif /* Tree_h */
