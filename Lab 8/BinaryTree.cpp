//
// Created by phoenix559 on 10/16/26.
//
/* Warm-up at the beginning of the lab (type of question that could be in the second midterm of the final)

Write the Delete function for a BST with an iterative function
Write the Delete function for a BST with a recursive function

We consider a binary search tree.

1. Implement a function that determines if a binary tree is a binary search tree (type of question that could be in the
second midterm of the final)

2. Implement a function to traverse the tree per level (see document provided on Canvas)

From BST to AVL:

3. Implement the rotation functions (rotate left, rotate right, left then right, right then left)

4. We consider  this sequence of elements:

20,10,15:   Display the tree (per level) before and after the necessary rotations to make this tree balanced
10,5,1:   Display the tree (per level) before and after the necessary rotations to make this tree balanced
10, 20, 30: Display the tree (per level) before and after the necessary rotations to make this tree balanced
10, 20, 50: Display the tree (per level) before and after the necessary rotations to make this tree balanced



Code to be submitted: Question 3/4 only. The code should run and display the 4 cases in the 2 conditions: before/after
the necessary rotations that should be determined automatically based on the balance between the right and left subtrees.
*/

#include "BinaryTree.h"
#include "TreeQueue.h"

BinaryTree::BinaryTree(TreeNode *&insert_root) {
    root = insert_root;
}

void BinaryTree::insert_iterative(int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
    }
    else {
        // traverse tree
        TreeNode* temp = root;
        TreeNode* parent = nullptr;
        int direction = 0;
        while (temp != nullptr) {
            if (value < temp->get_data()) {
                parent = temp;
                temp = temp->get_left();
                direction = -1;
            }
            else {
                parent = temp;
                temp = temp->get_right();
                direction = 1;
            }
        }
        // insert value
        temp = new TreeNode(value, parent);
        if (direction == -1) {
            parent->set_left(temp);
        }
        else if(direction == 1) {
            parent->set_right(temp);
        }
    }
}

void BinaryTree::insert(int value) {
    insert_recursively(value, root, nullptr);
}

void BinaryTree::insert_recursively(int value, TreeNode *&subroot, TreeNode *parent) {
    if (!subroot) {
        subroot = new TreeNode(value,parent);
        if (parent) {
            subroot->update_level(parent->get_level() + 1);
        }

        return;
    }
    if (value < subroot->get_data()) {
        insert_recursively(value, subroot->get_left(), subroot);
    }
    else {
        insert_recursively(value, subroot->get_right(), subroot);
    }
}

void BinaryTree::print_by_level(TreeNode *&subroot) {
    if (!subroot) {
        return;
    }
    TreeQueue* temp = new TreeQueue();

}

bool BinaryTree::search(int key) {
    return true;
}

void BinaryTree::rotate(TreeNode *&root) {
}

void BinaryTree::rotate_left(TreeNode *&root) {
}

void BinaryTree::rotate_right(TreeNode *&root) {
}

bool BinaryTree::check_bst_status() {
}

void BinaryTree::delete_iterative(int value) {
}

void BinaryTree::delete_recursively(TreeNode *&root, int value) {
}

void BinaryTree::print_root() {
    if (root) {
        root->print();
    }
}

void BinaryTree::print_by_level() {
    print_by_level(root);
}

TreeNode * BinaryTree::get_root() const {
    return root;
}

TreeNode *& BinaryTree::get_root() {
    return root;
}

int BinaryTree::get_height() const {
    return height;
}

bool BinaryTree::get_is_bst() const {
    return is_bst;
};
