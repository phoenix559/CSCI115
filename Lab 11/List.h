//
// Created by phoenix559 on 11/12/26.
//

#ifndef CSCI115_LIST_H
#define CSCI115_LIST_H


class Node
{
public:
    Node(int id = 0, int w = 1, Node* next = nullptr, Node* prev = nullptr);
    ~Node();
    void set_vertex_id(int id);
    void set_weight(int w);
    void set_next(Node* next_node);
    void set_prev(Node* prev_node);
    void set_head(Node* temp);
    Node* get_next();
    Node* get_prev();
    int get_vertex_id();
    int get_weight();
private:
    int vertex_id;
    int weight;
    Node* prev;
    Node* next;
    Node* head_node;
};


class List
{
public:
    List();
    ~List();

    void insert(int v, int w = 1);
    bool remove(int v);
    bool contains(int v);
    void report();

    Node* get_head();
    Node* get_tail();
    int get_size();
    int get_weight(int v);

private:
    Node* head_node;
    Node* tail_node;
    int size;
};

#endif //CSCI115_LIST_H
