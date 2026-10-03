//
// Created by phoenix559 on 10/1/26.
//
#include "Linked_Lists.h"


void LinkedList::delete_node(Node *arg_head) {
    Node* prev = arg_head->get_prev();
    Node * next = arg_head->get_next();
    prev->set_next(next);
    next->set_prev(prev);
    delete arg_head;
}

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {
}

LinkedList::LinkedList(Node *arg_head) {
    head = new Node(arg_head->get_data());
    head->set_next(nullptr);
    head->set_prev(nullptr);
    tail = head;
}

LinkedList::LinkedList(int arg_data) {
    head = new Node(arg_data);
    head->set_next(nullptr);
    head->set_prev(nullptr);
    tail = head;
}

LinkedList::~LinkedList() {
    Node* temp = nullptr;
    while (head != nullptr) {
        temp = head->get_next();
        delete head;
        head = temp;
    }
    head = nullptr;
}

Node * LinkedList::get_head() const {
    return head;
}

void LinkedList::set_head(Node *arg_head) {
    head = arg_head;
}

Node * LinkedList::get_tail() const {
    return tail;
}

void LinkedList::set_tail(Node *arg_tail) {
    tail = arg_tail;
}

void LinkedList::insert_head(int element) {
    Node* temp = new Node(element);
    if (head == nullptr) {
        head = temp;
        tail = temp;
    }
    else if (head == tail){
        head = temp;
        head->set_next(tail);
        tail->set_prev(head);

    }

}

void LinkedList::insert(Node **head, int element) {
}

void LinkedList::insert_tail(int element) {
}

void LinkedList::delete_first(int element) {
}

void LinkedList::delete_last(int element) {
}

void LinkedList::delete_all(int element) {
}


int main() {
    Node * def = new Node();
    def->display();
    Node *

    return 0;
}