//
// Created by phoenix559 on 10/24/26.
//
#include "Map.h"
#include <iostream>
#include "Animal.h"
#include <cstdlib> // Required for system()
#include <ctime>

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
void display_all_animals(Animal** animal) {
    std::cout << std::endl;
    for (int i = 0; i < 4; i++) {
        (animal[i])->display();
        std::cout << std::endl;
    }
}
int random_number(int min = 0, int max = 19) {
    return (rand() % (max - min + 1)) + min;
}
void update_all_animals(Animal** animal) {
    std::pair<int,int> position = {random_number(),random_number()};
    std::pair<int,int> positions[4];
    int r = random_number(), c = random_number();
    for (int i = 0; i < 4; i++) {
        r = random_number();
        c = random_number();
        position = {r,c};
        for (int j = 0; j < 4; j++) {
            while (position.first == positions[j].first && position.second == positions[j].second) {
                r = random_number();
                c = random_number();
                position = {r,c};
            }
        }    
        positions[i] = position;
    }
    for (int i = 0; i < 4; i++) {
        animal[i]->update_location(positions[i].first,positions[i].second);
    }
    
}
int main() {
    std::srand(std::time(nullptr));
    std::string filename = "/home/phoenix559/CLionProjects/CSCI 115/Project/map1.txt";
    Map map = Map();
    map.load_map(filename);
    map.display();
    
    Animal* animal [4] = {new Monkey(5,6), new Bird(15,8), new Frog(10,10), new Fish (0,19)};
    display_all_animals(animal);
    map.display(animal,4);
    //clearScreen();
    update_all_animals(animal);
    display_all_animals(animal);
    map.display(animal,4);

}
