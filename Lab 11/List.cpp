#include <iostream>
#include "List.h"

// ================= Node Implementation =================

Node::Node(int id, int w, Node* next_node, Node* prev_node)
{
	set_vertex_id(id);
	set_weight(w);
	set_next(next_node);
	set_prev(prev_node);
	head_node = nullptr;
}

Node::~Node()
{
}

void Node::set_vertex_id(int id) { vertex_id = id; }
void Node::set_weight(int w) { weight = w; }
void Node::set_next(Node* next_node) { next = next_node; }
void Node::set_prev(Node* prev_node) { prev = prev_node; }
Node* Node::get_next() { return next; }
Node* Node::get_prev() { return prev; }
int Node::get_vertex_id() { return vertex_id; }
int Node::get_weight() {return weight; }
void Node::set_head(Node* temp) { head_node = temp; }

// ================= List Implementation =================
List::List()
{
	head_node = nullptr;
	tail_node = nullptr;
	size = 0;
}

List::~List()
{
	Node* curr = head_node;
	while (curr != nullptr)
	{
		Node* next_temp = curr->get_next();
		delete curr;
		curr = next_temp;
	}
	head_node = nullptr;
	tail_node = nullptr;
	size = 0;
}

void List::insert(int v,int w)
{
	Node* new_node = new Node(v, w, nullptr, tail_node);
	if (head_node == nullptr)
	{
		head_node = new_node;
		tail_node = new_node;
	}
	else
	{
		tail_node->set_next(new_node);
		tail_node = new_node;
	}
	size = size + 1;
}

bool List::contains(int v)
{
	return (get_weight(v) != -1);
}

bool List::remove(int v)
{
	bool removed = false;
	Node* curr = head_node;
	while (curr != nullptr && removed == false)
	{
		if (curr->get_vertex_id() == v)
		{
			if (curr == head_node && curr == tail_node)
			{
				head_node = nullptr;
				tail_node = nullptr;
			}
			else if (curr == head_node)
			{
				head_node = curr->get_next();
				head_node->set_prev(nullptr);
			}
			else if (curr == tail_node)
			{
				tail_node = curr->get_prev();
				tail_node->set_next(nullptr);
			}
			else
			{
				Node* p = curr->get_prev();
				Node* n = curr->get_next();
				p->set_next(n);
				n->set_prev(p);
			}

			delete curr;
			size = size - 1;
			removed = true;
		}
		else
		{
			curr = curr->get_next();
		}
	}
	return removed;
}

void List::report()
{
	Node* curr = head_node;
	while (curr != nullptr)
	{
		std::cout << curr->get_vertex_id() << "(w: " << curr->get_weight() << ")";
		if (curr->get_next() != nullptr)
		{
			std::cout << " -> ";
		}
		curr = curr->get_next();
	}
}

Node* List::get_head() { return head_node; }
Node* List::get_tail() { return tail_node; }
int List::get_size() { return size; }

int List::get_weight(int v)
{
	int result_weight = -1;
	bool found = false;
	Node* curr = head_node;

	while (curr != nullptr && found == false)
	{
		if (curr->get_vertex_id() == v)
		{
			result_weight = curr->get_weight();
			found = true;
		}
		else
		{
			curr = curr->get_next();
		}
	}

	return result_weight;
}

