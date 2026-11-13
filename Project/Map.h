//
// Created by phoenix559 on 10/24/26.
//

#ifndef CSCI115_MAP_H
#define CSCI115_MAP_H
#include <climits>
#include <string>
#include "Animal.h"
class MyQueue {};
class Map {
private:
    int col = 0;
    int row = 0;
    char* grid = nullptr;



    // methods
    Animal* get_animal_at(int row, int col, Animal** animals, int num_animals);
    void clear();
public:
    Map() = default;
    Map(int col, int row, char* gird);
    ~Map();
    bool load_map (const std::string &filename);
    char terrain (int c, int r);
    void update_character_locations(Animal* animal);
    //void display();
    void display(Animal** animals = nullptr, int num_animals = 0);
};


#endif //CSCI115_MAP_H
