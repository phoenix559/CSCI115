add_executable(Project
        main.cpp
        Map.cpp
        Map.h
        Animal.cpp
        Animal.h
        AnimalCrossing.cpp
        AnimalCrossing.h
        "../Lab 11/Graph.cpp"
        "../Lab 11/Graph.h"
        "../Lab 11/List.cpp"
        "../Lab 11/List.h"
        "../Lab 11/PriorityQueue.cpp"
        "../Lab 11/PriorityQueue.h"
)

target_include_directories(Project PRIVATE "../Lab 11")