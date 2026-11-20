//
// Created by phoenix559 on 11/5/26.
//

#include "PriorityQueue.h"


PQNode::PQNode(int vertex_id, int distance) {
	this->vertex_id = vertex_id;
	this->distance = distance;
}

void PriorityQueue::sift_up(int index) {
	int current = index;
	bool still_sifting = true;

	while (current > 0 && still_sifting == true) {
		int parent_index = (current - 1) / 2;
		if (data[current]->distance < data[parent_index]->distance) {
			PQNode* temp = data[current];
			data[current] = data[parent_index];
			data[parent_index] = temp;
			current = parent_index;
		}
		else {
			still_sifting = false;
		}
	}
}

void PriorityQueue::sift_down(int index) {
	int current = index;
	bool still_sifting = true;

	while (still_sifting == true) {
		int left_child = (2 * current) + 1;
		int right_child = (2 * current) + 2;
		int smallest = current;

		if (left_child < size && data[left_child]->distance < data[smallest]->distance) {
			smallest = left_child;
		}

		if (right_child < size && data[right_child]->distance < data[smallest]->distance) {
			smallest = right_child;
		}

		if (smallest != current) {
			PQNode* temp = data[current];
			data[current] = data[smallest];
			data[smallest] = temp;
			current = smallest;
		}
		else {
			still_sifting = false;
		}
	}
}


PriorityQueue::PriorityQueue(int max_capacity, PQNode* arg_data):capacity(max_capacity) {
	data = new PQNode*[capacity];
	data[0] = arg_data;

}

PriorityQueue::~PriorityQueue() {
	delete[] data;
}
void PriorityQueue::enqueue(PQNode* v) {
	if (size < capacity) {
		data[size] = v;
		sift_up(size);
		size = size + 1;
	}
    
}
PQNode* PriorityQueue::dequeue() {
	if (size == 0) {
		return nullptr;
	}
	PQNode* min_node = data[0];
	data[0] = data[size - 1];
	size = size - 1;
	sift_down(0);
	return min_node;
}

void PriorityQueue::decrease_key(int target_vertex_id, int new_cost)
{
	if (data == nullptr || size <= 0)
	{
		return;
	}

	int found_index = -1;
	int i = 0;
	while (i < size && found_index == -1)
	{
		if (data[i] != nullptr && data[i]->vertex_id == target_vertex_id)
		{
			found_index = i;
		}
		else
		{
			i = i + 1;
		}
	}

	if (found_index != -1)
	{
		data[found_index]->distance = new_cost;
		sift_up(found_index);
	}
}

bool PriorityQueue::is_empty() {
	return (size==0);
}

int PriorityQueue::get_size() {
		return size;
}