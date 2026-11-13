#include "PriorityQueue.h"
#include "Graph.h"
#include <iostream>
#include <climits>


Graph::Graph(int num_vertices)
{
	this->num_vertices = num_vertices;
	Pointing = new List*[num_vertices];
	for (int i = 0; i < num_vertices; i = i + 1)
	{
		Pointing[i] = new List();
	}
}

Graph::~Graph()
{
	for (int i = 0; i < num_vertices; i = i + 1)
	{
		delete Pointing[i];
	}
	delete[] Pointing;
	Pointing = nullptr;
}

bool Graph::check_exist(int u, int v)
{
	if (u < 0 || u >= num_vertices || v < 0 || v >= num_vertices)
	{
		return false;
	}
	return Pointing[u]->contains(v);
}

void Graph::Add(int u, int v, int w)
{
	if (u >= 0 && u < num_vertices && v >= 0 && v < num_vertices)
	{
		bool already_exists = check_exist(u, v);
		if (already_exists == false)
		{
			Pointing[u]->insert(v,w);
		}
	}
}

void Graph::Remove(int u, int v)
{
	if (u >= 0 && u < num_vertices && v >= 0 && v < num_vertices)
	{
		Pointing[u]->remove(v);
	}
}

int Graph::retrieve_edge(int u, int v)
{
	if (u >= 0 && u < num_vertices && v >= 0 && v < num_vertices) {
		return Pointing[u]->get_weight(v);
	}
	return -1;
}

List* Graph::adjacent_vertices(int u)
{
	if (u >= 0 && u < num_vertices)
	{
		return Pointing[u];
	}
	return nullptr;
}

void Graph::Print()
{
	std::cout << "--- Adjacency List ---" << std::endl;
	for (int i = 0; i < num_vertices; i = i + 1)
	{
		std::cout << "Vertex " << i << ": [ ";
		Pointing[i]->report();
		std::cout << " ]" << std::endl;
	}
}
/*
void Graph::BFS(int start_vertex)
{
	if (start_vertex < 0 || start_vertex >= num_vertices)
	{
		std::cout << "Invalid starting vertex!" << std::endl;
		return;
	}

	bool* visited = new bool[num_vertices];
	for (int i = 0; i < num_vertices; i = i + 1)
	{
		visited[i] = false;
	}

	Queue q;

	visited[start_vertex] = true;
	q.enqueue(start_vertex);

	std::cout << "BFS Traversal starting from vertex " << start_vertex << ": ";

	while (q.is_empty() == false)
	{
		int curr = q.dequeue();
		std::cout << curr << " ";

		List* neighbors = Pointing[curr];
		Node* curr_neighbor = neighbors->get_head();

		while (curr_neighbor != nullptr)
		{
			int neighbor_val = curr_neighbor->get_vertex_id();
			if (visited[neighbor_val] == false)
			{
				visited[neighbor_val] = true;
				q.enqueue(neighbor_val);
			}
			curr_neighbor = curr_neighbor->get_next();
		}
	}

	std::cout << std::endl;

	delete[] visited;
}
*/
int Graph::get_num_vertices()
{
	return num_vertices;
}

void Graph::print_dijkstra_results(int source_vertex, int* distance, int* predecessor)
{
	std::cout << "\nDijkstra Results (Source = " << source_vertex << "):" << std::endl;

	std::cout << "Vertex:      ";
	for (int i = 0; i < num_vertices; i = i + 1)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	std::cout << "Distance:    ";
	for (int i = 0; i < num_vertices; i = i + 1)
	{
		if (distance[i] == INT_MAX)
		{
			std::cout << "INF\t";
		}
		else
		{
			std::cout << distance[i] << "\t";
		}
	}
	std::cout << std::endl;

	std::cout << "Predecessor: ";
	for (int i = 0; i < num_vertices; i = i + 1)
	{
		std::cout << predecessor[i] << "\t";
	}
	std::cout << std::endl;
}

void Graph::Dijkstra(int source_vertex)
{
	if (source_vertex < 0 || source_vertex >= num_vertices)
	{
		std::cout << "Invalid source vertex!" << std::endl;
		return;
	}

	int* distance = new int[num_vertices];
	int* predecessor = new int[num_vertices];
	bool* visited = new bool[num_vertices];
	bool* in_queue = new bool[num_vertices];

	PriorityQueue pq(num_vertices);

	for (int i = 0; i < num_vertices; i = i + 1)
	{
		distance[i] = INT_MAX;
		predecessor[i] = -1;
		visited[i] = false;
		in_queue[i] = false;
	}

	distance[source_vertex] = 0;

	PQNode* start_node = new PQNode();
	start_node->vertex_id = source_vertex;
	start_node->distance = 0;
	pq.enqueue(start_node);
	in_queue[source_vertex] = true;

	while (pq.is_empty() == false)
	{
		PQNode* curr_pq = pq.dequeue();
		int u = curr_pq->vertex_id;
		delete curr_pq;
		in_queue[u] = false;

		if (visited[u] == false)
		{
			visited[u] = true;

			List* neighbors = adjacent_vertices(u);
			Node* curr_edge = neighbors->get_head();

			while (curr_edge != nullptr)
			{
				int v = curr_edge->get_vertex_id();
				int weight = curr_edge->get_weight();

				if (visited[v] == false && distance[u] != INT_MAX)
				{
					int new_cost = distance[u] + weight;
					if (new_cost < distance[v])
					{
						distance[v] = new_cost;
						predecessor[v] = u;

						if (in_queue[v] == true)
						{
							pq.decrease_key(v, new_cost);
						}
						else
						{
							PQNode* next_node = new PQNode();
							next_node->vertex_id = v;
							next_node->distance = new_cost;
							pq.enqueue(next_node);
							in_queue[v] = true;
						}
					}
				}
				curr_edge = curr_edge->get_next();
			}
		}
	}

	print_dijkstra_results(source_vertex, distance, predecessor);

	delete[] distance;
	delete[] predecessor;
	delete[] visited;
	delete[] in_queue;
}

void Graph::Dijkstra(int source_vertex, int destination_vertex)
{
	if (source_vertex < 0 || source_vertex >= num_vertices ||
		destination_vertex < 0 || destination_vertex >= num_vertices)
	{
		std::cout << "Invalid source or destination vertex!" << std::endl;
		return;
	}

	int* distance = new int[num_vertices];
	int* predecessor = new int[num_vertices];
	bool* visited = new bool[num_vertices];
	bool* in_queue = new bool[num_vertices];

	PriorityQueue pq(num_vertices);

	for (int i = 0; i < num_vertices; i = i + 1)
	{
		distance[i] = INT_MAX;
		predecessor[i] = -1;
		visited[i] = false;
		in_queue[i] = false;
	}

	distance[source_vertex] = 0;

	PQNode* start_node = new PQNode();
	start_node->vertex_id = source_vertex;
	start_node->distance = 0;
	pq.enqueue(start_node);
	in_queue[source_vertex] = true;

	bool reached_destination = false;

	while (pq.is_empty() == false && reached_destination == false)
	{
		PQNode* curr_pq = pq.dequeue();
		int u = curr_pq->vertex_id;
		delete curr_pq;
		in_queue[u] = false;

		if (u == destination_vertex)
		{
			visited[u] = true;
			reached_destination = true;
		}
		else if (visited[u] == false)
		{
			visited[u] = true;

			List* neighbors = adjacent_vertices(u);
			Node* curr_edge = neighbors->get_head();

			while (curr_edge != nullptr)
			{
				int v = curr_edge->get_vertex_id();
				int weight = curr_edge->get_weight();

				if (visited[v] == false && distance[u] != INT_MAX)
				{
					int new_cost = distance[u] + weight;
					if (new_cost < distance[v])
					{
						distance[v] = new_cost;
						predecessor[v] = u;

						if (in_queue[v] == true)
						{
							pq.decrease_key(v, new_cost);
						}
						else
						{
							PQNode* next_node = new PQNode();
							next_node->vertex_id = v;
							next_node->distance = new_cost;
							pq.enqueue(next_node);
							in_queue[v] = true;
						}
					}
				}
				curr_edge = curr_edge->get_next();
			}
		}
	}

	std::cout << "\n[Version 2: Source " << source_vertex << " -> Destination " << destination_vertex << "]";
	print_dijkstra_results(source_vertex, distance, predecessor);

	delete[] distance;
	delete[] predecessor;
	delete[] visited;
	delete[] in_queue;
}

void Graph::Dijkstra(int source_vertex, int* destinations, int num_destinations)
{
	if (source_vertex < 0 || source_vertex >= num_vertices || destinations == nullptr || num_destinations <= 0)
	{
		std::cout << "Invalid source or destination list!" << std::endl;
		return;
	}

	int* distance = new int[num_vertices];
	int* predecessor = new int[num_vertices];
	bool* visited = new bool[num_vertices];
	bool* in_queue = new bool[num_vertices];
	bool* is_target = new bool[num_vertices];

	PriorityQueue pq(num_vertices);

	for (int i = 0; i < num_vertices; i = i + 1)
	{
		distance[i] = INT_MAX;
		predecessor[i] = -1;
		visited[i] = false;
		in_queue[i] = false;
		is_target[i] = false;
	}

	int remaining_targets = 0;
	for (int i = 0; i < num_destinations; i = i + 1)
	{
		int d = destinations[i];
		if (d >= 0 && d < num_vertices && is_target[d] == false)
		{
			is_target[d] = true;
			remaining_targets = remaining_targets + 1;
		}
	}

	distance[source_vertex] = 0;

	PQNode* start_node = new PQNode();
	start_node->vertex_id = source_vertex;
	start_node->distance = 0;
	pq.enqueue(start_node);
	in_queue[source_vertex] = true;

	while (pq.is_empty() == false && remaining_targets > 0)
	{
		PQNode* curr_pq = pq.dequeue();
		int u = curr_pq->vertex_id;
		delete curr_pq;
		in_queue[u] = false;

		if (visited[u] == false)
		{
			visited[u] = true;

			if (is_target[u] == true)
			{
				remaining_targets = remaining_targets - 1;
			}

			if (remaining_targets > 0)
			{
				List* neighbors = adjacent_vertices(u);
				Node* curr_edge = neighbors->get_head();

				while (curr_edge != nullptr)
				{
					int v = curr_edge->get_vertex_id();
					int weight = curr_edge->get_weight();

					if (visited[v] == false && distance[u] != INT_MAX)
					{
						int new_cost = distance[u] + weight;
						if (new_cost < distance[v])
						{
							distance[v] = new_cost;
							predecessor[v] = u;

							if (in_queue[v] == true)
							{
								pq.decrease_key(v, new_cost);
							}
							else
							{
								PQNode* next_node = new PQNode();
								next_node->vertex_id = v;
								next_node->distance = new_cost;
								pq.enqueue(next_node);
								in_queue[v] = true;
							}
						}
					}
					curr_edge = curr_edge->get_next();
				}
			}
		}
	}

	std::cout << "\n[Version 3: Source " << source_vertex << " -> Multiple Destinations]";
	print_dijkstra_results(source_vertex, distance, predecessor);

	delete[] distance;
	delete[] predecessor;
	delete[] visited;
	delete[] in_queue;
	delete[] is_target;
}
