//
// Created by phoenix559 on 10/16/26.
//
#include "BinaryTree.h"
#include <iostream>

int main() {
    BinaryTree* myTree = new BinaryTree();
    myTree->insert(20);
    myTree->insert(10);
    myTree->insert(15);
    TreeNode * temp = myTree->get_root();
    for (int i = 1; i <= 3; i++) {
        temp -> print();
        if (temp->get_left()) {
            temp = temp -> get_left();
        }
        else {
            temp = temp ->get_right();
        }
    }
    return 0;
}