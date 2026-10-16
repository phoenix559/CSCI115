//
// Created by phoenix559 on 10/8/26.
//

#ifndef CSCI115_HASH_H
#define CSCI115_HASH_H
# include <string>

unsigned long hash_djb2(const char *str);

class Hash_Node {
private:
    std::string data;
    Hash_Node* next = nullptr;
    Hash_Node* prev = nullptr;
    int list_count = 1;
    int word_count = 1;

public:
    Hash_Node();
    Hash_Node(const std::string& text, Hash_Node* head = nullptr);
    ~Hash_Node();
    void set_data(const std::string &text);
    void set_next(Hash_Node* current_head);
    void set_prev(Hash_Node* new_head);

    std::string get_data() const;
    Hash_Node* get_next() const;
    Hash_Node* get_prev() const;
    int get_list_count() const;
    void set_list_count(int head_list_count);
    int get_word_count() const;
    void increase_word_count();
    void display();
};


#endif //CSCI115_HASH_H
