//
// Created by phoenix559 on 10/30/26.
//

#include "Animal.h"
#include <iostream>
#include <ostream>

void Animal::set_cost_of_edges() {
    
    // From Mountain            TO
    cost_of_edges[0][0] = 2; // Mountain
    cost_of_edges[0][1] = 1; // Plain
    cost_of_edges[0][2] = 1; // Forest
    cost_of_edges[0][3] = 1; // Desert
    cost_of_edges[0][4] = 10; // Ocean
    
    // From Plain               To
    cost_of_edges[1][0] = 5; // Mountain
    cost_of_edges[1][1] = 1; // Plain
    cost_of_edges[1][2] = 3; // Forest
    cost_of_edges[1][3] = 2; // Desert
    cost_of_edges[1][4] = 2; // Ocean    
    
    // From Forest               TO
    cost_of_edges[0][0] = 6; // Mountain
    cost_of_edges[0][1] = 2; // Plain
    cost_of_edges[0][2] = 3; // Forest
    cost_of_edges[0][3] = 2; // Desert
    cost_of_edges[0][4] = 5; // Ocean
    
    // From Desert               To
    cost_of_edges[1][0] = 10; // Mountain
    cost_of_edges[1][1] = 2; // Plain
    cost_of_edges[1][2] = 3; // Forest
    cost_of_edges[1][3] = 2; // Desert
    cost_of_edges[1][4] = 3; // Ocean    

    // From Ocean                 TO
    cost_of_edges[0][0] = 10; // Mountain
    cost_of_edges[0][1] = 3; // Plain
    cost_of_edges[0][2] = 3; // Forest
    cost_of_edges[0][3] = 3; // Desert
    cost_of_edges[0][4] = 1; // Ocean
    

}

int Animal::terrain_index(char terrain) {
    if (terrain == '^')
        return 0;
    else if (terrain == '.')
        return 1;
    else if (terrain == '"')
        return 2;
    else if (terrain == ' ')
        return 3;
    else if (terrain == '~')
        return 4;
    else 
        return -1;
}

Animal::Animal(char arg_type, int r, int c) {
    type = arg_type;
    position = {r,c};
}

Animal::~Animal() {
}

std::pair<int, int> Animal::get_position() const {
    return position;
}

void Animal::update_location(int r, int c) {
    position.first = r;
    position.second = c;
}

char Animal::get_type() const {
    return type;
}

int Animal::get_cost_of_edge(char from, char to) {
    int from_index = terrain_index(from);
    int to_index = terrain_index(to);
    return cost_of_edges[from_index][to_index];
}

void Animal::display() {
    std::cout << type << " is located at " << position.first << " " << position.second << std::endl;
    
}


void Monkey::set_cost_of_edges (){
    // From Mountain            TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = 1; // Plain
    cost_of_edges[0][2] = 1; // Forest
    cost_of_edges[0][3] = 1; // Desert
    cost_of_edges[0][4] = INT_MAX; // Ocean
    
    // From Plain               To
    cost_of_edges[1][0] = INT_MAX; // Mountain
    cost_of_edges[1][1] = 1; // Plain
    cost_of_edges[1][2] = 3; // Forest
    cost_of_edges[1][3] = 2; // Desert
    cost_of_edges[1][4] = INT_MAX; // Ocean    
    
    // From Forest               TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = 2; // Plain
    cost_of_edges[0][2] = 3; // Forest
    cost_of_edges[0][3] = 2; // Desert
    cost_of_edges[0][4] = INT_MAX; // Ocean
    
    // From Desert               To
    cost_of_edges[1][0] = INT_MAX; // Mountain
    cost_of_edges[1][1] = 2; // Plain
    cost_of_edges[1][2] = 3; // Forest
    cost_of_edges[1][3] = 2; // Desert
    cost_of_edges[1][4] = INT_MAX; // Ocean    

    // From Ocean                 TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = 3; // Plain
    cost_of_edges[0][2] = 3; // Forest
    cost_of_edges[0][3] = 3; // Desert
    cost_of_edges[0][4] = INT_MAX; // Ocean
    
}

Monkey::Monkey():Animal('M') {
    Monkey::set_cost_of_edges();
}

Monkey::Monkey(int r, int c):Animal('M', r, c) {
    Monkey::set_cost_of_edges();
}

Monkey::~Monkey() {
}

void Monkey::display() {
    std::cout << "Animal: Monkey (" << type << ") Position: ("<< position.first << ", " << position.second << ")";
    std::cout << "| Impassable Terrain: Mountains (^), Ocean (~)"<<std::endl;
}

void Bird::set_cost_of_edges (){
    // From Mountain            TO
    cost_of_edges[0][0] = 2; // Mountain
    cost_of_edges[0][1] = 1; // Plain
    cost_of_edges[0][2] = 1; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 10; // Ocean
    
    // From Plain               To
    cost_of_edges[1][0] = 5; // Mountain
    cost_of_edges[1][1] = 1; // Plain
    cost_of_edges[1][2] = 3; // Forest
    cost_of_edges[1][3] = INT_MAX; // Desert
    cost_of_edges[1][4] = 2; // Ocean    
    
    // From Forest               TO
    cost_of_edges[0][0] = 6; // Mountain
    cost_of_edges[0][1] = 2; // Plain
    cost_of_edges[0][2] = 3; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 5; // Ocean
    
    // From Desert               To
    cost_of_edges[1][0] = 10; // Mountain
    cost_of_edges[1][1] = 2; // Plain
    cost_of_edges[1][2] = 3; // Forest
    cost_of_edges[1][3] = INT_MAX; // Desert
    cost_of_edges[1][4] = 3; // Ocean    

    // From Ocean                 TO
    cost_of_edges[0][0] = 10; // Mountain
    cost_of_edges[0][1] = 3; // Plain
    cost_of_edges[0][2] = 3; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 1; // Ocean
    
}

Bird::Bird():Animal('B') {
    Bird::set_cost_of_edges();
}

Bird::Bird(int r, int c):Animal('B', r, c) {
    Bird::set_cost_of_edges();
}

Bird::~Bird() {
}

void Bird::display() {
    std::cout << "Animal: Bird (" << type << ") Position: ("<< position.first << ", " << position.second << ")";
    std::cout << "| Impassable Terrain: Desert (.)"<<std::endl;
}

void Frog::set_cost_of_edges (){
    // From Mountain            TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = 1; // Plain
    cost_of_edges[0][2] = 1; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 10; // Ocean
    
    // From Plain               To
    cost_of_edges[1][0] = INT_MAX; // Mountain
    cost_of_edges[1][1] = 1; // Plain
    cost_of_edges[1][2] = 3; // Forest
    cost_of_edges[1][3] = INT_MAX; // Desert
    cost_of_edges[1][4] = 2; // Ocean    
    
    // From Forest               TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = 2; // Plain
    cost_of_edges[0][2] = 3; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 5; // Ocean
    
    // From Desert               To
    cost_of_edges[1][0] = INT_MAX; // Mountain
    cost_of_edges[1][1] = 2; // Plain
    cost_of_edges[1][2] = 3; // Forest
    cost_of_edges[1][3] = INT_MAX; // Desert
    cost_of_edges[1][4] = 3; // Ocean    

    // From Ocean                 TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = 3; // Plain
    cost_of_edges[0][2] = 3; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 1; // Ocean
    
}

Frog::Frog():Animal('G') {
    Frog::set_cost_of_edges();
}

Frog::Frog(int r, int c):Animal('G', r, c) {
    Frog::set_cost_of_edges();
}

Frog::~Frog() {
}

void Frog::display() {
    std::cout << "Animal: Frog (" << type << ") Position: ("<< position.first << ", " << position.second << ")";
    std::cout << "| Impassable Terrain: Mountains (^), Desert (.)"<<std::endl;
}


void Fish::set_cost_of_edges (){
    // From Mountain            TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = INT_MAX; // Plain
    cost_of_edges[0][2] = INT_MAX; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 10; // Ocean
    
    // From Plain               To
    cost_of_edges[1][0] = INT_MAX; // Mountain
    cost_of_edges[1][1] = INT_MAX; // Plain
    cost_of_edges[1][2] = INT_MAX; // Forest
    cost_of_edges[1][3] = INT_MAX; // Desert
    cost_of_edges[1][4] = 2; // Ocean    
    
    // From Forest               TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = INT_MAX; // Plain
    cost_of_edges[0][2] = INT_MAX; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 5; // Ocean
    
    // From Desert               To
    cost_of_edges[1][0] = INT_MAX; // Mountain
    cost_of_edges[1][1] = INT_MAX; // Plain
    cost_of_edges[1][2] = INT_MAX; // Forest
    cost_of_edges[1][3] = INT_MAX; // Desert
    cost_of_edges[1][4] = 3; // Ocean    

    // From Ocean                 TO
    cost_of_edges[0][0] = INT_MAX; // Mountain
    cost_of_edges[0][1] = INT_MAX; // Plain
    cost_of_edges[0][2] = INT_MAX; // Forest
    cost_of_edges[0][3] = INT_MAX; // Desert
    cost_of_edges[0][4] = 1; // Ocean
    
}

Fish::Fish():Animal('F') {
    Fish::set_cost_of_edges();
}

Fish::Fish(int r, int c):Animal('F', r, c) {
    Fish::set_cost_of_edges();
}

Fish::~Fish() {
}

void Fish::display() {
    std::cout << "Animal: Fish (" << type << ") Position: ("<< position.first << ", " << position.second << ")";
    std::cout << "| Impassable Terrain: Mountains (^), Plains ( ), Desert (.), Forest (\")"<<std::endl;
}
