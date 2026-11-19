
#include "Map.h"
#include <iostream>
#include "Animal.h"
#include <cstdlib> // Required for system()
#include <ctime>
#include "/home/phoenix559/CLionProjects/CSCI 115/Lab 11/Graph.h"
#include "AnimalCrossing.h"

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
void display_all_animals(Animal** animal, int animal_count) {
    std::cout << std::endl;
    for (int i = 0; i < animal_count; i++) {
        (animal[i])->display();
        std::cout << std::endl;
    }
}
int random_number(int min = 0, int max = 19) {
    return (rand() % (max - min + 1)) + min;
}
void update_all_animals(Animal** animal, int animal_count) {
    std::pair<int,int> position = {random_number(),random_number()};
    std::pair<int,int> positions[animal_count];
    int r = random_number(), c = random_number();
    for (int i = 0; i < animal_count; i++) {
        r = random_number();
        c = random_number();
        position = {r,c};
        for (int j = 0; j < animal_count; j++) {
            while (position.first == positions[j].first && position.second == positions[j].second) {
                r = random_number();
                c = random_number();
                position = {r,c};
            }
        }    
        positions[i] = position;
    }
    for (int i = 0; i < animal_count; i++) {
        animal[i]->update_location(positions[i].first,positions[i].second);
    }
}
int main() {
    std::srand(std::time(nullptr));
    
    //Update filename to address of map.
    std::string filename = "/home/phoenix559/CLionProjects/CSCI 115/Project/map1.txt";
    AnimalCrossing game = AnimalCrossing(filename);
    
}
