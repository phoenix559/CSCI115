//
// Created by phoenix559 on 10/16/26.
//
# include "TreeNode.h"
#include <iostream>

TreeNode::TreeNode(int insert_data, TreeNode *parent_node, TreeNode *left_child, TreeNode *right_child) {
    data = insert_data;
    parent = parent_node;
    left = left_child;
    right = right_child;
}
TreeNode* TreeNode::get_parent() const {
    return parent;
}
TreeNode* TreeNode::get_left() const {
    return left;
}
TreeNode* TreeNode::get_right() const {
    return right;
}

TreeNode *& TreeNode::get_left() {
    return left;
}

TreeNode *& TreeNode::get_right() {
    return right;
}

int TreeNode::get_level() const {
    return level;
}

int TreeNode::get_data() const {
    return data;
}
void TreeNode::set_data(int insert_data) {
    data = insert_data;
}
void TreeNode::set_parent(TreeNode *parent_node) {
    parent = parent_node;
}

void TreeNode::set_left(TreeNode *left_child) {
    left = left_child;
}
void TreeNode::set_right(TreeNode *right_child) {
    right = right_child;
}

void TreeNode::update_level(int updated_level) {
    level = updated_level;
}

void TreeNode::print() {
    //std::cout << data << std::endl;
    std::cout << "Level: " << level << "\t\tData: " << data << std::endl;
}
