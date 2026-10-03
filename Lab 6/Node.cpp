#include "Node.h"

#include <iostream>
#include <ostream>
//
// Created by phoenix559 on 10/1/26.
//
Node::Node() {
    data = 0;
    next = nullptr;
    prev = nullptr;
}
Node::Node(int arg_data) {
    data = arg_data;
    next = nullptr;
    prev = nullptr;
}
Node::~Node() {

}

int Node::get_data() const {
    return data;
}

void Node::set_data(int arg_data) {
    data = arg_data;
}

Node* Node::get_next() const {
    return next;
}
void Node::set_next(Node *arg_next) {
    next = arg_next;
}
Node* Node::get_prev() const {
    return prev;
}
void Node::set_prev(Node *arg_prev) {
    prev = arg_prev;
}

void Node::display() const {
    std::cout << "Node element:" << data << std::endl;
    std::cout << "Next Node address:" << next << std::endl;
    std::cout << "Next Node data:" << next->get_data() << std::endl;
    std::cout << "Prev Node address:" << prev << std::endl;
    std::cout << "Prev Node data:" << prev->get_data() << std::endl;
}
