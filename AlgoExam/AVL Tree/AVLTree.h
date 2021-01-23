#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <utility>
#include <iostream>
#include <memory>
#include <functional>
#include <stack>
#include <vector>

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
    size_t                  _Height(_Node* root) const;
    void                    _Inorder(_Node* root, _Callback) const;
    //Input - The nodes for balance factor calculation
    //Output - The nodes which are needed to be balanced
    std::vector<_Node*>     _UpdateBalanceFactors(const std::vector<_Node*>& path);
    void                    _BalanceNodes(const std::vector<_Node*>& nodes);
    void                    _RightRotate(_Node* current);
    void                    _LeftRotate(_Node* current);

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

    std::vector<_Node*> path;

    while (current != nullptr)
    {
        const _Type& ref = current->data;
        path.push_back(current);
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

    //The nodes which are needed to be balanced
    auto balance = _UpdateBalanceFactors(path);
    
    _BalanceNodes(balance);
    
    //in the end of balanceing this vector should contain 0 elements
    auto res = _UpdateBalanceFactors(path);

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

//This is the simple method for balance factors calculation
template<class T>
std::vector<typename AVLTree<T>::_Node*> AVLTree<T>::_UpdateBalanceFactors(const std::vector<_Node*>& path)
{
    std::vector<_Node*> ret;
    auto current = std::begin(path);
    while (current != std::end(path))
    {
        _Node* top = *current;
        size_t lh = _Height(top->left.get());
        size_t rh = _Height(top->right.get());

        top->bf = (int)(lh - rh);
        if(top->bf > 1 || top->bf < -1){
            ret.push_back(top);
        }
        
        ++current;
    }
    return ret;
}

template<class T>
void AVLTree<T>::_BalanceNodes(const std::vector<_Node*>& nodes)
{
    auto current = nodes.rbegin();
    while (current != nodes.rend()) {
        
        _Node* ref = *current;
        int bf = ref->bf;
        
        if(bf > 1){
            //Right Rotate
            _Node* left = ref->left.get();
            _Node* left_left = left->left.get();
            _Node* left_right = left->right.get();
            if(left_left != nullptr){
                _RightRotate(ref);
                return;
            }
            
            if(left_right != nullptr){
                _LeftRotate(left);
                _RightRotate(ref);
                return;
            }
        }
        else{
            //Left Rotate
            _Node* right = ref->right.get();
            _Node* right_left = right->left.get();
            _Node* right_right = right->right.get();
            if(right_right != nullptr){
                _LeftRotate(ref);
                return;
            }
            
            if(right_left != nullptr){
                _RightRotate(right);
                _LeftRotate(ref);
                return;
            }
        }
        
        ++current;
    }
}

template<class T>
void AVLTree<T>::_RightRotate(_Node* current)
{
    if(current == nullptr || current->left == nullptr) return;
    std::unique_ptr<_Node> extracted_top{nullptr};
    std::unique_ptr<_Node> extracted_left{nullptr};

    _Node* p = current->parent;
    bool root = (p == nullptr);
    bool right{false};
    if(!root){
        right = p->right.get() == current;
        if(right)
            extracted_top = std::move(p->right);
        else
            extracted_top = std::move(p->left);
    }
    else{
        extracted_top = std::move(_root);
    }
    
    extracted_top->parent = nullptr;
    
    extracted_left = std::move(extracted_top->left);
    extracted_left->parent = nullptr;

    extracted_top->left = std::move(extracted_left->right);
    if(extracted_top->left != nullptr){
        extracted_top->left->parent = extracted_top.get();
    }

    extracted_left->parent = p;
    extracted_left->right = std::move(extracted_top);
    extracted_left->right->parent = extracted_left.get();
    
    if(!root){
        if(right)
            p->right = std::move(extracted_left);
        else
            p->left = std::move(extracted_left);
    }
    else{
        extracted_left->parent = nullptr;
        _root = std::move(extracted_left);
    }
}

template<class T>
void AVLTree<T>::_LeftRotate(_Node* current)
{
    if(current == nullptr || current->right == nullptr) return;
    std::unique_ptr<_Node> extracted_top{nullptr};
    std::unique_ptr<_Node> extracted_right{nullptr};

    _Node* p = current->parent;
    bool root = (p == nullptr);
    bool right{false};
    if(!root){
        right = p->right.get() == current;
        if(right)
            extracted_top = std::move(p->right);
        else
            extracted_top = std::move(p->left);
    }
    else{
        extracted_top = std::move(_root);
    }
    
    extracted_top->parent = nullptr;
    
    extracted_right = std::move(extracted_top->right);
    extracted_right->parent = nullptr;

    extracted_top->right = std::move(extracted_right->left);
    if(extracted_top->right != nullptr){
        extracted_top->right->parent = extracted_top.get();
    }

    extracted_right->parent = p;
    extracted_right->left = std::move(extracted_top);
    extracted_right->left->parent = extracted_right.get();
    
    if(!root){
        if(right)
            p->right = std::move(extracted_right);
        else
            p->left = std::move(extracted_right);
    }
    else{
        extracted_right->parent = nullptr;
        _root = std::move(extracted_right);
    }
}

#endif