//
// Created by phoenix559 on 10/1/26.
//

#ifndef CSCI115_LINKED_LISTS_H
#define CSCI115_LINKED_LISTS_H
#include "Node.h"
class LinkedList {
private:
    Node* head;
    Node* tail;
    void delete_node(Node* arg_head);
public:
    LinkedList();
    LinkedList(Node* arg_head);
    LinkedList(int arg_element);
    ~LinkedList();
    Node* get_head() const;
    Node* get_tail() const;

    // insert methods
    void insert_head(int element);
    void insert(Node** head, int element);
    void insert_tail(int element);
    // delete methods
    void pop_front();
    void pop_back();
    void delete_first_occurrence(int element);
    void delete_last_occurrence(int element);
    void delete_all_occurrence(int element);
};

#endif //CSCI115_LINKED_LISTS_H
