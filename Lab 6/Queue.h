//
// Created by phoenix559 on 10/1/26.
//

#ifndef CSCI115_QUEUE_H
#define CSCI115_QUEUE_H
#include "Node.h"

class Queue {
private:
    Node* head;
    Node* tail;
public:
    Node* get_head();
    void insert(int value);
    void pop();
    int peek();
    void print();
};
#endif //CSCI115_QUEUE_H
