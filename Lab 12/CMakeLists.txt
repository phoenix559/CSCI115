add_executable(floyd_warshall
        main.cpp
        "../Lab 11/Graph.cpp"
        "../Lab 11/Graph.h"
        "../Lab 11/List.cpp"
        "../Lab 11/List.h"
        "../Lab 11/PriorityQueue.cpp"
        "../Lab 11/PriorityQueue.h")

target_include_directories(floyd_warshall PRIVATE "../Lab 11")