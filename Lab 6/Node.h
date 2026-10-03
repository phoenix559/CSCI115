//
// Created by phoenix559 on 10/1/26.
//

#ifndef CSCI115_NODE_H
#define CSCI115_NODE_H
class Node {
private:
    int data;
    Node* next;
    Node* prev;
public:
    Node();
    Node(int data);
    ~Node();
    int get_data() const;
    void set_data(int arg_data);
    Node *get_next() const;
    void set_next(Node *arg_next);
    Node *get_prev() const;
    void set_prev(Node *arg_prev);
    void display() const;
};
#endif //CSCI115_NODE_H
