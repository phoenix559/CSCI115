//
// Created by phoenix559 on 11/15/26.
//

#ifndef CSCI115_ANIMALCROSSING_H
#define CSCI115_ANIMALCROSSING_H
#include "Map.h"
#include "Animal.h"
#include "/home/phoenix559/CLionProjects/CSCI 115/Lab 11/Graph.h"

class AnimalCrossing {
private:
    Map* map = nullptr;
    Graph* g = nullptr;
    Animal** animals = nullptr;
    int animal_count = 4;
    bool* has_moved = nullptr;
    std::string map_filename;
    
    void generate_map(const std::string& filename);
    void generate_graph();
    int random_number(int min = 0, int max = 19) const;
    bool is_valid_spawn(Animal* current_animal, std::pair<int, int> current_animal_position, const std::pair<int, 
        int>* positions, int placed_count) const; 
    bool parse_coordinates(const std::string& input, int& r, int& c) const;
    void spawn_animals();
    void apply_animal_weights(int current_animal_index);
    std::pair<int*,int> reconstruct_path(const std::pair<bool, int*> path, int target);
    void move_animal(int current_animal_index, std::pair<int*, int> reconstructed_path);
public:
    AnimalCrossing(const std::string &filename);
    ~AnimalCrossing();
    void clean_up();
    void reset( std::string filename = "");
    std::string get_filename();
    void navigate_to_target(int current_animal_index, int v);
    void display_map();
    std::pair<int, int> select_target_location();
    void game_loop();
    
};


#endif //CSCI115_ANIMALCROSSING_H
