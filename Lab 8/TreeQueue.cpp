//
// Created by phoenix559 on 10/21/26.
//
#include "TreeQueue.h"

TreeQueue::QueueNode::QueueNode(TreeNode *value) {
    tree_node = value;
    next = nullptr;
}


TreeQueue::TreeQueue(TreeNode *value) {
    head = tail = new QueueNode(value);
}

void TreeQueue::push(TreeNode *value) {
    QueueNode* temp = new QueueNode(value);
    if (head) {
        tail->next = temp;
        tail = temp;
    }
    else {
        head = tail = temp;
    }
}

void TreeQueue::pop() {
    if (head) {
        QueueNode* temp = head;
        head = temp->next;
        delete temp;
    }

}

TreeQueue::QueueNode* TreeQueue::peek() const {
    return head->tree_node;
}

void TreeQueue::print() {
    head->tree_node->print();
}
