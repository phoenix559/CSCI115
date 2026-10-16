#include "hash.h"

#include <iostream>
#include <ostream>

unsigned long hash_djb2(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
Hash_Node::Hash_Node() {
    data = "";
    next = nullptr;
    prev = nullptr;
    list_count = 0;
    word_count = 0;
}

Hash_Node::Hash_Node(const std::string& text, Hash_Node* head) {
    int head_list_count = 0;
    data = text;
    next = head;
    if (head) {
        head->set_prev (this);
        set_list_count(head->get_list_count());
    }
    prev = nullptr;
}

Hash_Node::~Hash_Node() {
    data = "";
    next = nullptr;
    prev = nullptr;
    list_count = 0;
    word_count = 0;
}

void Hash_Node::set_data(const std::string& text) {
    data = text;
    return ;
}

void Hash_Node::set_next(Hash_Node *current_head) {
    next = current_head;
}

void Hash_Node::set_prev(Hash_Node *new_head) {
    prev = new_head;
}

std::string Hash_Node::get_data() const{
    return data;
}

Hash_Node* Hash_Node::get_next() const{
    return next;
}

Hash_Node* Hash_Node::get_prev() const{
    return prev;
}

int Hash_Node::get_list_count() const {
    return list_count;
}

void Hash_Node::set_list_count(int head_list_count) {
    head_list_count++;
    list_count = head_list_count;
}

int Hash_Node::get_word_count() const {
    return word_count;
}

void Hash_Node::increase_word_count() {
    word_count++;
}

void Hash_Node::display() {
    std::cout << "data = " << data << std::endl;
    std::cout << "word count = " << word_count << std::endl;
    std::cout << "list count = " << list_count << std::endl;
}

