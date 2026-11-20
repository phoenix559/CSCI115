//
// Created by phoenix559 on 11/5/26.
//

#ifndef CSCI115_PRIORITY_QUEUE_H
#define CSCI115_PRIORITY_QUEUE_H
#include <climits>
#define MAX_CAPACITY 512

struct PQNode {
    int vertex_id = 0;
    int distance = 0;
    PQNode(int vertex_id = 0, int distance = 0);
};

class PriorityQueue {
private:
    PQNode ** data = nullptr;
    int size = 0;
    int capacity = MAX_CAPACITY;
    void sift_up(int index);
    void sift_down(int index);
public:
    PriorityQueue() = default;
    PriorityQueue(int max_capacity, PQNode *arg_data = nullptr);
    ~PriorityQueue();
    void enqueue(PQNode* v);
    PQNode* dequeue();
    void decrease_key(int target_vertex_id, int new_cost);;
    bool is_empty();
    int get_size();
};


#endif //CSCI115_PRIORITY_QUEUE_H

