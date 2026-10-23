//
// Created by phoenix559 on 10/21/26.
//

#ifndef CSCI115_TREEQUEUE_H
#define CSCI115_TREEQUEUE_H
#include "TreeNode.h"
class TreeQueue {
private:
    struct QueueNode {
        TreeNode* tree_node = nullptr;
        QueueNode* next = nullptr;
        QueueNode(TreeNode* value);
    };
    QueueNode* head = nullptr;
    QueueNode* tail = nullptr;
public:
    TreeQueue() = default;
    TreeQueue(TreeNode* value);
    void push(TreeNode* value);
    void pop();
    TreeNode* peek() const;
    void print();
};
#endif //CSCI115_TREEQUEUE_H
