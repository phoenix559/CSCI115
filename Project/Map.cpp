//
// Created by phoenix559 on 10/24/26.
//

#include "Map.h"
#include <iostream>
#include <fstream>
#include <strings.h>


Animal * Map::get_animal_at(int row, int col, Animal **animals, int num_animals) {
    Animal* animal = nullptr;
    if (animals) {
        for (int i = 0; i < num_animals; i++) {
            animal = animals[i];
            if (animal) {
                int animal_row = animal->get_position().first;
                int animal_col = animal->get_position().second;
                if (animal_row == row && animal_col == col) {
                    return animal;
                }
            }
        }
    }
    return nullptr;
}

void Map::clear() {
    col = 0;
    row = 0;
    delete [] grid;
    grid = nullptr;
}

Map::Map(int row, int col, char *gird) {
}

Map::~Map() {
    clear();
}

bool Map::load_map(const std::string &filename) {
    std::ifstream file(filename);
    std::string line = "";

    // verify that the file opened.
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << filename << std::endl;
        return false;
    }
    // clear the map data if/when we code a "new map" option.
    clear();

    // Verify proper file formatting and determine/validate row and column dimensions
    int c = col;
    int r = 0;
    bool is_valid = true;

    while (is_valid && std::getline(file, line)) {
        c = line.length();

        if (col == 0 && c != 0) {
            col = c;
        } else if (c == 0) {
            std::cerr << "Formatting error: empty line detected at row " << r << std::endl;
            is_valid = false;
        } else if (c != col) {
            std::cerr << "Formatting error: column length mismatch at row " << r << std::endl;
            std::cerr << "Expected column length: " << col << " Row " << r << " length: " << c << std::endl;
            is_valid = false;
        }

        int i = 0;
        while (is_valid && i < c) {
            char ch = line[i];
            if (ch != '^' && ch != '.' && ch != '"' && ch != '~' && ch != ' ') {
                std::cerr << "Formatting error: invalid character '" << ch << "' detected at " << r << ", " << i << std::endl;
                is_valid = false;
            }
            i++;
        }

        if (is_valid) {
            r++;
        }
    }

    if (row == 0) {
        row = r;
    } else if (is_valid && r != row) {
        std::cerr << "Formatting error: file row count (" << r << ") does not match expected row count of " << row << std::endl;
        is_valid = false;
    }

    if (!is_valid || r == 0 || col == 0) {
        file.close();
        return false;
    }

    grid = new char[col * row];

    // Reset text getline (errors and reset to beginning of file)
    file.clear();
    file.seekg(0, std::ios::beg);

    // fill grid
    r = 0;
    int index = 0;
    while (std::getline(file, line) && r< row) {
        for (c = 0; c < line.length() && c < col; c++ ) {
            index = r * col + c;
            grid[index] = line[c];
        }
        r ++;
    }
    return true;
}

char Map::terrain(int r, int c) {
    return grid[r * col + c];
}

void Map::update_character_locations(Animal* animal) {
}

/*void Map::display() {
    int c = 0;
    int index = 0;
    for (int r = 0; r < row; r++) {
        for (c = 0; c < col; c++) {
            index = r * col + c;
            std::cout << grid[index] << "  ";
        }
        std::cout << std::endl;
    }
}*/
/*
void Map::display(Animal* animals) {
    int animal_row = -1, animal_col = -1;
    char animal_type = 0;
    std::cout << "     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19" << std::endl;
    std::cout << "   ---------------------------------------------------------------" << std::endl;
    if (animals) {
        std::pair<int,int> location = animals->get_position();
        animal_row = location.first;
        animal_col = location.second;
        animal_type = animals->get_type();
    }
    int c = 0;
    int index = 0;
    for (int r = 0; r < row; r++) {
        if (r < 10)
            std::cout << " " << r << " | ";
        else 
            std::cout << r << " | ";
        for (c = 0; c < col; c++) {
            if (animal_row == r && animal_col == c) {
                std::cout << animal_type << "  ";   
            }
            else {
                index = r * col + c;
                std::cout << grid[index] << "  ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "   ---------------------------------------------------------------" << std::endl;
}*/

void Map::display(Animal** animals, int num_animals) {
    int animal_row = -1, animal_col = -1;
    char animal_type = 0;
    Animal* animal = nullptr;
    std::cout << "     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19" << std::endl;
    std::cout << "   ---------------------------------------------------------------" << std::endl;

    int c = 0;
    int index = 0;
    for (int r = 0; r < row; r++) {
        if (r < 10)
            std::cout << " " << r << " | ";
        else 
            std::cout << r << " | ";
        for (c = 0; c < col; c++) {
            if (animals) {
                animal = get_animal_at(r,c,animals,num_animals);
                if (animal) {
                    std::pair<int,int> location = animal->get_position();
                    animal_row = location.first;
                    animal_col = location.second;
                    animal_type = animal->get_type();
                    std::cout << animal_type << "  "; 
                }
                else {
                    index = r * col + c;
                    std::cout << grid[index] << "  ";
                }
            }
            else {
                index = r * col + c;
                std::cout << grid[index] << "  ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "   ---------------------------------------------------------------" << std::endl;
}

int Map::get_row() const {return row;}

int Map::get_col() const {return col;}
