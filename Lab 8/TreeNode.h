//
// Created by phoenix559 on 10/16/26.
//

#ifndef CSCI115_TREENODE_H
#define CSCI115_TREENODE_H
class TreeNode {
private:
    int data = 0;
    TreeNode *parent = nullptr;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    int level = 1;

public:
    TreeNode() = default;
    TreeNode(int insert_data, TreeNode *parent_node = nullptr, TreeNode *left_child = nullptr,
        TreeNode *right_child = nullptr);
    TreeNode* get_parent() const;
    TreeNode* get_left() const;
    TreeNode* get_right() const;
    TreeNode* &get_left();
    TreeNode* &get_right();
    int get_level() const;
    int get_data() const;
    void set_data(int insert_data);
    void set_parent(TreeNode *parent_node);
    void set_left(TreeNode *left_child);
    void set_right(TreeNode *right_child);
    void update_level(int updated_level);

    void print();
};

#endif //CSCI115_TREENODE_H
