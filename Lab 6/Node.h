//
// Created by phoenix559 on 10/1/26.
//

#ifndef CSCI115_NODE_H
#define CSCI115_NODE_H
using MyType = int;

class Node {
private:
    int data;
    Node* next;
    Node* prev;
public:
    Node();
    Node(int data);
    ~Node();
    MyType get_data() const;
    void set_data(MyType arg_data);
    Node *get_next() const;
    void set_next(Node *arg_next);
    Node *get_prev() const;
    void set_prev(Node *arg_prev);
    void display() const;
};
#endif //CSCI115_NODE_H
