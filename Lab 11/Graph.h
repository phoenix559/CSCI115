#ifndef CSCI115_GRAPH_H
#define CSCI115_GRAPH_H

#include <utility>

#include "List.h"

class Graph
{
public:
    Graph(int num_vertices = 0);
    ~Graph();

    bool check_exist(int u, int v);
    void Add(int u, int v, int w = 1);
    void Remove(int u, int v);
    int retrieve_edge(int u, int v);
    List* adjacent_vertices(int u) const;
    void Print();
    //void BFS(int start_vertex);

    int get_num_vertices() const;
   

    int* Dijkstra(int source_vertex);
    std::pair<bool,int*> Dijkstra(int source_vertex, int destination_vertex);
    void Dijkstra(int source_vertex, int* destinations, int num_destinations);

private:
    int num_vertices;
    List** Pointing; // Dynamic array of List pointers (adjacency list)3
    void print_dijkstra_results(int source_vertex, int* distance, int* predecessor);
};

#endif //CSCI115_GRAPH_H
