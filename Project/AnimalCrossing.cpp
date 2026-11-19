//
// Created by phoenix559 on 11/15/26.
//

#include "AnimalCrossing.h"
#include <iostream>
#include <string>


void AnimalCrossing::generate_map(const std::string& filename) {
    std::string current_filename = filename;
    map = new Map();
    bool loaded = false;
    while (!loaded) {
        loaded = map->load_map(current_filename);
        if (!loaded) {
            std::cerr<<"Could not load map file "<<current_filename<<std::endl;
            std::cerr<<"Please enter valid map filepath: ";
            std::getline(std::cin, current_filename);
        }
    }
}

void AnimalCrossing::generate_graph() {
    int rows = map->get_row();
    int cols = map->get_col();
    int num_vertices = rows * cols;
    g = new Graph(num_vertices);
    int u_row = 0, u_col = 0, v = 0;
    for (int u = 0; u < num_vertices; u++) {
        u_row = u/cols;
        u_col = u%cols;
        // add North
        if (u_row >0) {
            v = u - cols;
            g->Add(u,v);
        }
        // add East
        if (u_col < cols-1) {
            v = u + 1;
            g->Add(u,v);
        }        
        // add South
        if (u_row<rows-1) {
            v = u + cols;
            g->Add(u,v);
        }
        // add West
        if (u_col > 0) {
            v = u - 1;
            g->Add(u,v);
        }
    }
    
}

int AnimalCrossing::random_number(int min, int max) const {
    return (rand() % (max - min + 1)) + min;
}

bool AnimalCrossing::is_valid_spawn(Animal* current_animal, std::pair<int, int> current_animal_position, const std::pair<int, int>* positions, int placed_count) const {
    int r = current_animal_position.first;
    int c = current_animal_position.second;
    char tile_terrain = 0;
    int size = 0;
    char* impassable_terrain = nullptr;
    int j = 0;
    bool is_passable = true;
    bool is_unique = true;

    if (r < 0 || r >= map->get_row() || c < 0 || c >= map->get_col()) {
        return false;
    }

    tile_terrain = map->terrain(r, c);
    size = current_animal->get_impassable_terrain_length();
    impassable_terrain = current_animal->get_impassable_terrain();

    do {
        is_passable = (impassable_terrain[j] != tile_terrain);
        j++;
    } while (is_passable && (j < size));

    j = 0;
    while (is_unique && (j < placed_count)) {
        is_unique = (current_animal_position != positions[j]);
        j++;
    }

    return is_passable && is_unique;
}
bool AnimalCrossing::parse_coordinates(const std::string& input, int& r, int& c) const {
    int open_paren = input.find('(');
    int comma = input.find(',');
    int close_paren = input.find(')');
    std::string r_str = "";
    std::string c_str = "";

    if (open_paren == std::string::npos || comma == std::string::npos || close_paren == std::string::npos) {
        return false;
    }
    if (!(open_paren < comma && comma < close_paren)) {
        return false;
    }

    r_str = input.substr(open_paren + 1, comma - (open_paren + 1));
    c_str = input.substr(comma + 1, close_paren - (comma + 1));

    try {
        r = std::stoi(r_str);
        c = std::stoi(c_str);
    }
    catch (...) {
        return false;
    }

    return true;
}
void AnimalCrossing::spawn_animals() {
    double spawn_rate = 1.0/50;
    int max_spawn = g->get_num_vertices() * spawn_rate;
    std::string spawn_choice = "";
    bool valid_choice = false;
    int r = 0, c = 0, min_c = 0, max_c = map->get_col() - 1, min_r = 0, max_r = map->get_row() - 1;
    Animal* current_animal = nullptr;
    std::pair<int, int>* positions = nullptr;
    std::pair<int, int> current_animal_position = {-1, -1};
    int animal_type = 0;
    bool is_valid = false;
    std::string coord_input = "";
    bool parsed = false;

    if (max_spawn < 1) {
        max_spawn = 1;
    }

    do {
        std::cout << "Choose how we will spawn the animals:" << std::endl;
        std::cout << "1: 4 animals, one of each type, placed on random locations" << std::endl;
        std::cout << "2: 4 animals, one of each type, placed on user selected locations" << std::endl;
        std::cout << "3: Up to " << max_spawn << " random animals, on random locations" << std::endl;
        std::cout << "Enter the number for your choice: ";
        std::getline(std::cin, spawn_choice);
        valid_choice = (spawn_choice == "1" || spawn_choice == "2" || spawn_choice == "3");
        if (!valid_choice) {
            std::cerr << "Invalid choice! Please try again." << std::endl;
        }
    } while (!valid_choice);

    if (spawn_choice == "1" || spawn_choice == "2") {
        animal_count = 4;
        animals = new Animal*[animal_count] {new Monkey(), new Bird(), new Frog(), new Fish()};
        positions = new std::pair<int, int>[animal_count] {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
        current_animal_position = {-1, -1};

        if (spawn_choice == "1") {
            for (int i = 0; i < animal_count; i++) {
                current_animal = animals[i];
                do {
                    r = random_number(min_r, max_r);
                    c = random_number(min_c, max_c);
                    current_animal_position = {r, c};
                    is_valid = is_valid_spawn(current_animal, current_animal_position, positions, i);
                } while (!is_valid);

                positions[i] = current_animal_position;
                current_animal->update_location(r, c);
            }
        }
        else {
            for (int i = 0; i < animal_count; i++) {
                map->display(animals,i);
                current_animal = animals[i];
                do {
                    std::cout << "Enter (r,c) [r: 0-" << max_r << ", c: 0-" << max_c << "] for the " << current_animal->get_name() << " starting location: ";
                    std::getline(std::cin, coord_input);
                    parsed = parse_coordinates(coord_input, r, c);
                    if (!parsed) {
                        is_valid = false;
                        std::cerr << "Invalid input! Please enter coordinates as (r,c)." << std::endl;
                    }
                    else {
                        current_animal_position = {r, c};
                        is_valid = is_valid_spawn(current_animal, current_animal_position, positions, i);
                        if (!is_valid) {
                            std::cerr << "Invalid or occupied location for " << current_animal->get_name() << "! Please try again." << std::endl;
                        }
                    }
                } while (!is_valid);

                positions[i] = current_animal_position;
                current_animal->update_location(r, c);
            }
            
        }
        delete [] positions;
    }
    else if (spawn_choice == "3") {
        do {
            std::cout << "Enter the number of animals to spawn (between 1 and " << max_spawn << "): ";
            std::string number_of_animals;
            std::getline(std::cin, number_of_animals);
            try {
                animal_count = stoi(number_of_animals);
            }
            catch (...){
                animal_count = 0;
            }
            is_valid = animal_count > 0 && animal_count <= max_spawn;
            if (!is_valid) {
                std::cerr << "Invalid input! Please try again." << std::endl;
            }
        }while (!is_valid);
        animals = new Animal*[animal_count];
        positions = new std::pair<int, int>[animal_count];
        current_animal_position = {-1, -1};

        for (int i = 0; i < animal_count; i++) {
            positions[i] = {-1, -1};
            animal_type = random_number(0, 3);
            if (animal_type == 0) {
                animals[i] = new Monkey();
            }
            else if (animal_type == 1) {
                animals[i] = new Bird();
            }
            else if (animal_type == 2) {
                animals[i] = new Frog();
            }
            else {
                animals[i] = new Fish();
            }

            current_animal = animals[i];
            do {
                r = random_number(min_r, max_r);
                c = random_number(min_c, max_c);
                current_animal_position = {r, c};
                is_valid = is_valid_spawn(current_animal, current_animal_position, positions, i);
            } while (!is_valid);

            positions[i] = current_animal_position;
            current_animal->update_location(r, c);
        }
        delete [] positions;
    }
    has_moved = new bool[animal_count];
    for (int i = 0; i < animal_count; i++) {
        has_moved[i] = false;
    }
}

void AnimalCrossing::apply_animal_weights(int current_animal_index) {
    int rows = map->get_row();
    int cols = map->get_col();
    int num_vertices = g->get_num_vertices();
    int u_row = 0, u_col = 0, v_row = 0, v_col = 0;
    int v = 0;
    std::pair <int,int> v_position;
    int w = 0;
    Animal* current_animal = animals[current_animal_index];
    Animal* temp_animal = nullptr;
    bool v_occupied = false;
    Node* neighbor = nullptr;
    char u_terrain = 0, v_terrain = 0;
    int animal_index = 0;
    
    for (int u = 0; u < num_vertices; u++) {
        neighbor = g->adjacent_vertices(u)->get_head(); // pulls first neighbor of the list
        // set u location on map (r,c)
        u_row = u/cols;
        u_col = u%cols;
        
        // look at terrain from u to v in current_animal and set weight for every v
        while (neighbor) { //loop until reaches end of neighbor list
            // set v location on map (r,c) 
            v = neighbor->get_vertex_id();
            v_row = v/cols;
            v_col = v%cols;
            v_position = {v_row,v_col};
            
            
            // reset v_occupied and ensure v is not occupied by another animal
            v_occupied = false;
            for (animal_index = 0; animal_index < animal_count; animal_index++) {
                temp_animal = animals[animal_index];
                if (animal_index != current_animal_index && v_position == temp_animal->get_position()) {
                    v_occupied = true;
                    w = INT_MAX;
                }
            }
            // set terrain for u and v if v isn't occupied by other animal.
            if (!v_occupied) {
                u_terrain = map->terrain(u_row,u_col);
                v_terrain = map->terrain(v_row,v_col);
                //get weight of edge u -> v
                w = current_animal->get_cost_of_edge(u_terrain, v_terrain);
            }
            //set weight
            neighbor->set_weight(w);
            neighbor = neighbor->get_next();
        }
    }
}
std::pair<int*,int> AnimalCrossing::reconstruct_path(const std::pair<bool,int*>path, int target) {
    // check that path exists
    
    if (!path.first) {
        std::cout<<"No path found!"<<std::endl;
        return {nullptr,0};
    }
    int num_vertices = g->get_num_vertices();
    int* pi = path.second;
    int* extracted_path = new int[num_vertices];
    int counter = -1; // set to -1, not 0, so that when it enters the while loop, if s = target its not off by 1
    int v = target;
    // extract path indices into array for easy traversal.
    while (v != -1) { // loops until it finds s (which is points to -1)
        counter++;
        extracted_path[counter] = v;
        v = pi[v];
    }
    int* reconstructed_path = new int[counter + 1];
    int i = 0;
    // invert extracted path
    for (int n = counter; n >= 0; n--) {
        reconstructed_path[i] = extracted_path[n];
        i++;
    }
    // deallocate pi
    delete [] pi;
    delete [] extracted_path;
    return {reconstructed_path,counter + 1}; // returns path going from s to target, and path size.
}
void AnimalCrossing::move_animal(int current_animal_index, std::pair<int*,int> reconstructed_path) {
    if (!reconstructed_path.first || reconstructed_path.second <= 0){
        return;
    }
    Animal* animal = animals[current_animal_index];
    int cols = map->get_col();
    int current_row = reconstructed_path.first[0] / cols;
    int current_col = reconstructed_path.first[0] % cols;
    std::pair<int,int> current_position = {current_row,current_col};
    if (current_position != animal->get_position()) {
        std::cout << "Source and " << animal->get_type() << " starting position are not the same. Ensure you chose the"
                                                            " correct animal" << std::endl;
        delete [] reconstructed_path.first;
        return;
    }
    std::string user_input;
    for (int i = 1; i < reconstructed_path.second; i++) {
        std::getline(std::cin,user_input);
        current_row = reconstructed_path.first[i] / cols;
        current_col = reconstructed_path.first[i] % cols;
        animal->update_location(current_row,current_col);
        map->display(animals,animal_count);
    }
    delete [] reconstructed_path.first;
}

AnimalCrossing::AnimalCrossing(const std::string &filename) {
    map_filename = filename;
    reset("");
}

AnimalCrossing::~AnimalCrossing() {
    clean_up();
}

void AnimalCrossing::clean_up() {
    
    delete map;
    map = nullptr;
    delete g;
    g = nullptr;
    for (int i = 0; i < animal_count; i++) {
        delete animals[i];
        animals[i] = nullptr;
    }
    delete [] animals;
    animals = nullptr;
    delete [] has_moved;
    has_moved = nullptr;
}

void AnimalCrossing::reset( std::string filename) {
    if (filename == "") {
        filename = get_filename();
    }

    // Create the map
    generate_map(filename);
    // Generate new graph that matches map structure
    generate_graph();
    // populate map
    spawn_animals();
    // display map
    map->display(animals,animal_count);
}

std::string AnimalCrossing::get_filename() {
    return map_filename;
}

void AnimalCrossing::navigate_to_target(int current_animal_index, int v) {
    int u_r = animals[current_animal_index]->get_position().first;
    int u_c = animals[current_animal_index]->get_position().second;
    int cols = map->get_col();
    int u = u_r * cols + u_c;
    apply_animal_weights(current_animal_index);
    std::pair<bool, int*>  shortest_path = g->Dijkstra(u,v);
    bool path_found = shortest_path.first;
    
    if (!path_found) {
        int v_r = v/cols;
        int v_c = v % cols;
        std::cerr << "There is no valid path for " << animals[current_animal_index]->get_name() << " to get from (" << 
            v_r << ", " << v_c << ") to (" << u_r << ", " << u_c << ")" << std::endl;
        delete [] shortest_path.second;
    }
    else {
        std::pair <int*,int> reconstructed_path = reconstruct_path(shortest_path,v);
        move_animal(current_animal_index, reconstructed_path);
    }
     
}

void AnimalCrossing::display_map() {
    map->display(animals,animal_count);
}

std::pair<int, int> AnimalCrossing::select_target_location() {
    std::string move_flag = "", selected_animal = "", coord_input = "";
    bool is_valid = false, parsed = false;
    int cols = map->get_col();
    int r = -1, c = -1;
    int animal_index = -1, target = -1;
    Animal* current_animal = nullptr;
    std::pair<int, int> target_coords = {-1,-1};
    std::pair<int,int> * positions = new std::pair<int,int>[animal_count];
    
    for (int i = 0; i < animal_count; i++) {
        positions[i] = animals[i]->get_position();
    }
    
    for (int i = 0; i < animal_count; i++) {
        if (!has_moved[i]) {
            move_flag = "";
        }    
        else {
            move_flag = "(has moved)";
        }
        std::cout << i + 1 << ": " << animals[i]->get_name() << " at (" << animals[i]->get_position().first << "," << animals[i]->get_position().second << ") "<< move_flag << std::endl;
    }
    do {
        std::cout << "Select the animal that will move next: " << std::endl;
        std::getline(std::cin,selected_animal);
        try {
            animal_index = std::stoi(selected_animal) - 1;
        }
        catch (...) {
            animal_index = -1;
        }
        is_valid = (animal_index >= 0 && animal_index < animal_count);
        if (!is_valid) {
            std::cerr << "Invalid entry. Choose a number between 1 and " << animal_count << std::endl;
        }
    }while (!is_valid);
    current_animal = animals[animal_index];
    
    is_valid = false;

    do {
        std::cout << "Select the location where " << animals[animal_index]->get_name() << " will move to." << std::endl;
        std::cout << "Enter (r,c) [r: 0-" << map->get_row() - 1 << ", c: 0-" << map->get_col() - 1 << "]";
        std::getline(std::cin, coord_input);
        parsed = parse_coordinates(coord_input, r, c);
        if (!parsed) {
            is_valid = false;
            std::cerr << "Invalid input! Please enter coordinates as (r,c)." << std::endl;
        }
        else {
            target_coords = {r, c};
            is_valid = is_valid_spawn(current_animal, target_coords, positions, animal_count);
            if (!is_valid) {
                std::cerr << "Invalid or occupied location for " << current_animal->get_name() << "! Please try again." << std::endl;
            }
        }
    } while (!is_valid);
    target = r * cols + c;
    delete [] positions;
    return {animal_index, target};
}

void AnimalCrossing::game_loop() {
    bool play_again = false, is_valid = true;
    
    std::pair<int, int> selected = {-1,-1};
    int animal_index = -1;
    int target_location = -1;
    std::string user_input = "";
    
    
    do {
        for (int i = 0; i < animal_count; i++) {
            selected = select_target_location();
            animal_index = selected.first;
            target_location = selected.second;
            navigate_to_target(animal_index, target_location);
            has_moved[animal_index] = true;
        }
        do {
            std::cout << "Would you like to try another simulation?: " << std::endl;
            std::cout << "1: Yes" << std::endl;
            std::cout << "2: No" << std::endl;
            getline(std::cin,user_input);
            
                if (user_input == "1") {
                    play_again = true;
                    is_valid = true;
                    clean_up();
                    reset();
                }
                else if (user_input == "2") {
                    play_again = false;
                    is_valid = true;
                }
                else {
                    is_valid = false;
                    std::cerr << "Invalid input! Please try again." << std::endl;
                }
                
        } while (!is_valid);
    }while (play_again);
    
}

