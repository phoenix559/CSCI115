#include <iostream>
#include "Graph.h"

int main() {
    // Allocate size 6 so vertices 1..5 match the diagram directly (index 0 unused)
    Graph g(6);

    // Undirected weighted edges from image.png
    g.Add(1, 2, 2);
    g.Add(2, 1, 2);

    g.Add(1, 4, 5);
    g.Add(4, 1, 5);

    g.Add(2, 3, 14);
    g.Add(3, 2, 14);

    g.Add(2, 4, 5);
    g.Add(4, 2, 5);

    g.Add(2, 5, 4);
    g.Add(5, 2, 4);

    g.Add(3, 5, 34);
    g.Add(5, 3, 34);

    g.Add(4, 5, 58);
    g.Add(5, 4, 58);

    // Step 3a: Verify graph by displaying it in the console
    g.Print();

    // Step 3b: Run Dijkstra from source vertex 1
    g.Dijkstra(1);

    return 0;
}