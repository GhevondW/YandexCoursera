//
//  Tree.h
//  RedBlackTree
//
//  Created by Ghevond Gevorgyan on 25.01.21.
//

#ifndef Tree_h
#define Tree_h

#include <iostream>
//https://www.programiz.com/dsa/red-black-tree

template<class T>
class Tree
{
public:
    using _Type = T;
    struct Node
    {
        Node() = default;
        Node(bool b, Node* p)
        :red(b),
        parent(p)
        {}
        explicit Node(const _Type& val)
        :data(val)
        {}
        ~Node() = default; //{ std::cout<<"Node Dtor"<<std::endl; }
        bool  red{true};
        Node* parent{nullptr};
        _Type data{};
        Node* left{nullptr};
        Node* right{nullptr};
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
            if(root->left != nullptr){
                std::cout<<"("<<root->data<<", "<<root->red<<") "<<std::endl;
            }
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
    void    _Balance(Node* node);
    void    _LeftRotate(Node* node);
    void    _RightRotate(Node* node);
    
private:
    Node* _root{nullptr};
};

//PUBLIC

/*
 https://www.programiz.com/dsa/red-black-tree
 Algorithm to insert a node
 Following steps are followed for inserting a new element into a red-black tree:
 
 1. Let y be the leaf (ie. NIL) and x be the root of the tree.
 2. Check if the tree is empty (ie. whether x is NIL). If yes, insert newNode as a root node and color it black.
 3. Else, repeat steps following steps until leaf (NIL) is reached.
  a. Compare newKey with rootKey.
  b. If newKey is greater than rootKey, traverse through the right subtree.
  c. Else traverse through the left subtree.
 4. Assign the parent of the leaf as a parent of newNode.
 5. If leafKey is greater than newKey, make newNode as rightChild.
 6. Else, make newNode as leftChild.
 7. Assign NULL to the left and rightChild of newNode.
 8. Assign RED color to newNode.
 9. Call InsertFix-algorithm to maintain the property of red-black tree if violated.
 
 Algorithm to maintain red-black property after insertion
 
 This algorithm is used for maintaining the property of a red-black tree if the insertion of a newNode violates this property.

 1. Do the following while the parent of newNode p is RED.
 2. If p is the left child of grandParent gP of z, do the following.
 Case-I:
  a. If the color of the right child of gP of z is RED, set the color of both the children of gP as BLACK and the color of gP as RED.
  b. Assign gP to newNode.
 Case-II:
  c. Else if newNode is the right child of p then, assign p to newNode.
  d. Left-Rotate newNode.
 Case-III:
  e. Set color of p as BLACK and color of gP as RED.
  f. Right-Rotate gP.
 3. Else, do the following.
  q. If the color of the left child of gP of z is RED, set the color of both the children of gP as BLACK and the color of gP as RED.
  b. Assign gP to newNode.
  c. Else if newNode is the left child of p then, assign p to newNode and Right-Rotate newNode.
  d. Set color of p as BLACK and color of gP as RED.
  e. Left-Rotate gP.
 4. Set the root of the tree as BLACK.
 
 */

template<class T>
void Tree<T>::Insert(const _Type& data)
{
    if(_root == nullptr)
    {
        _root = new Node(data);
        _root->left = new Node{false, _root};
        _root->right = new Node{false, _root};
        _root->parent = nullptr;
        _root->red = false;
    }
    else{
        auto new_node = _InsertLeaf(data);
        if(new_node->parent->parent == nullptr) return;
        
        _Balance(new_node);
        
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
    Node* pos = current;
    while (current != nullptr) {
        pos = current;
        if(current->data > data){
            current = current->left;
        }
        else if(current->data < data){
            current = current->right;
        }
        else{
            return nullptr;
        }
    }
    
    pos->data = data;
    pos->red = true;
    pos->left = new Node(false, pos);
    pos->right = new Node(false, pos);
    
    return pos;
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

template<class T>
void Tree<T>::_Balance(Node* node)
{
    Node* temp{nullptr};
    while (node->parent->red == true) {
        if (node->parent == node->parent->parent->right){
            temp = node->parent->parent->left;
            if(temp->red){
                temp->red = false;
                node->parent->red = false;
                node->parent->parent->red = true;
                node = node->parent->parent;
            }
            else{
                if (node == node->parent->left) {
                    node = node->parent;
                    _RightRotate(node);
                }
                node->parent->red = false;
                node->parent->parent->red = true;
                _LeftRotate(node->parent->parent);
            }
        }
        else{
            temp = node->parent->parent->right;
            if (temp->red) {
                temp->red = false;
                node->parent->red = false;
                node->parent->parent->red = true;
                node = node->parent->parent;
            }
            else{
                if (node == node->parent->right) {
                    node = node->parent;
                    _LeftRotate(node);
                }
                node->parent->red = false;
                node->parent->parent->red = true;
                _RightRotate(node->parent->parent);
            }
        }
        
        if (node == _root) {
            break;
        }
    }
    _root->red = false;
}

//See the rotation algorithms description in AVT tree implementation
template<class T>
void Tree<T>::_LeftRotate(Node* x)
{
    if(x == nullptr) return;
    
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }
    
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->_root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template<class T>
void Tree<T>::_RightRotate(Node* x)
{
    if(x == nullptr) return;
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->_root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

#endif /* Tree_h */
