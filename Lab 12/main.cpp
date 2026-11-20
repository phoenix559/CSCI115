
#include "../Lab 11/Graph.h"
#include "../Lab 11/PriorityQueue.h"
#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <utility>

std::pair<int**,int**> floyd_warshall(Graph* g) {
    const int n = g->get_num_vertices();
    int ** cost_matrix = new int*[n];
    int ** PI = new int*[n];
    List * neighbors = nullptr;
    Node* curr = nullptr;
    int k = 0, u = 0, v = 0, w = 0;
    int u_k_v = 0, u_v = 0;
    
    // create the matrices
    for (int i = 0; i < n; i++) {
        cost_matrix[i] = new int[n];
        PI[i] = new int[n];
        for (int j = 0; j < n; j++) {
            if (j == i) {
                cost_matrix[i][j] = 0;
            }
            else {
                cost_matrix[i][j] = INT_MAX;
            }
            PI[i][j] = -1;
        }
    }
    
    // fill matrices.
    for (u = 0; u < n; u++) {
        neighbors = g->adjacent_vertices(u);
        if (neighbors) {
            curr = neighbors->get_head();
            while (curr) {
                v = curr->get_vertex_id();
                w = curr->get_weight();
                cost_matrix[u][v] = w;
                PI[u][v] = u;
                curr = curr->get_next();
            }
        }
    }
    
    // check all pairs
    for (k = 0; k < n; k++) {
        for (u = 0; u < n; u++) {
            if (k != u && cost_matrix[u][k] != INT_MAX) {
                for (v = 0; v < n; v++) {
                    if (v != u && v != k && cost_matrix[k][v] != INT_MAX) {
                        u_k_v = cost_matrix[u][k] + cost_matrix[k][v];
                        u_v = cost_matrix[u][v];
                        if (u_k_v < u_v) {
                            cost_matrix[u][v] = u_k_v;
                            PI[u][v] = PI[k][v];
                        }
                    }   
                }
            }
        }
    }
    
    return {cost_matrix, PI};
}

Graph* build_graph(int n, double p) {
    Graph* g = new Graph(n);
    int u = 0, v = 0, w = 0;
    int min = 0, max = 100;
    double roll;
    for (u = 0; u < n; u++) {
        
        for (v = u + 1; v < n; v++) {
            roll = ((double)rand() / RAND_MAX);
            if (roll < p) {
                w = rand()%(max - min + 1) + min;
                g->Add(u,v,w);
                g->Add(v,u,w);
            }
        }
    }
    
    return g;
}int main() {
    srand(time(nullptr));
    double p[4] = {0.1, 0.3, 0.5, 0.9}; // probability for an edge
    int n[3] = {50, 100, 250};       // |V|

    std::cout << "n,p,Dijkstra_ms,FloydWarshall_ms" << std::endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            Graph* g = build_graph(n[i], p[j]);

            // Start Dijkstra timer (all-pairs = n single-source runs)
            std::chrono::high_resolution_clock::time_point dj_begin = std::chrono::high_resolution_clock::now();
            for (int u = 0; u < n[i]; u++) {
                int* dj_result = g->Dijkstra(u);
                delete[] dj_result;
            }
            std::chrono::high_resolution_clock::time_point dj_end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> dj_duration = dj_end - dj_begin;
            double dj_time = dj_duration.count();

            // Start Floyd-Warshall timer
            std::chrono::high_resolution_clock::time_point fw_begin = std::chrono::high_resolution_clock::now();
            std::pair<int**, int**> floyd = floyd_warshall(g);
            std::chrono::high_resolution_clock::time_point fw_end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> fw_duration = fw_end - fw_begin;
            double fw_time = fw_duration.count();

            // Print CSV results to console
            std::cout << n[i] << "," << p[j] << "," << dj_time << "," << fw_time << std::endl;

            // Deallocate Floyd-Warshall matrices and graph
            int** cost_matrix = floyd.first;
            int** PI = floyd.second;
            for (int k = 0; k < n[i]; k++) {
                delete[] cost_matrix[k];
                delete[] PI[k];
            }
            delete[] cost_matrix;
            delete[] PI;
            delete g;
        }
    }

    return 0;
}