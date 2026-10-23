//
// Created by phoenix559 on 10/16/26.
//

#ifndef CSCI115_BST_H
#define CSCI115_BST_H
#include "TreeNode.h"

class BinaryTree {
private:
    TreeNode *root = nullptr;
    int height = 1;;
    bool is_bst = true;
    void insert_recursively(int value, TreeNode* &subroot,TreeNode* parent);
    void print_by_level(TreeNode* &subroot);
public:
    BinaryTree() = default;
    BinaryTree(TreeNode* &insert_root);
    void insert_iterative(int value);
    void insert(int value);
    bool search(int key);
    void rotate(TreeNode *&root);
    void rotate_left(TreeNode *&root);
    void rotate_right(TreeNode *&root);
    bool check_bst_status ();
    void delete_iterative(int value);
    void delete_recursively(TreeNode *&root,int value);
    void print_root();
    void print_by_level();
    TreeNode* get_root() const;
    TreeNode* &get_root();
    int get_height() const;
    bool get_is_bst() const;

};

#endif //CSCI115_BST_H
