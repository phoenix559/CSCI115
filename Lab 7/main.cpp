# include <iostream>
# include <fstream>
# include <string>
# include <utility>
# include "hash.h"



std::string extract_word(const std::string& line) {
    size_t gap_index = line.find("  ");
    if (gap_index != std::string::npos) {
        return line.substr(0, gap_index);
    }
    return line;
}

std::pair<std::string*, int> dict_to_array(const std::string& filename, int word_limit) {
    std::ifstream file_in(filename);
    if (!file_in.is_open()) {
        std::cerr << "Error: Could not open file: " << filename << std::endl;
        return {nullptr, 0};
    }

    std::string* word_array = new std::string[word_limit];
    int word_count = 0;
    std::string current_line = "";

    while (word_count < word_limit && std::getline(file_in, current_line)) {
        if (!current_line.empty()) {
            word_array[word_count] = extract_word(current_line);
            word_count++;
        }
    }

    file_in.close();
    return {word_array, word_count};
}

void display_table(Hash_Node** table, const int buckets) {
    int size = 0;
    Hash_Node* current = nullptr;
    for (int i = 0; i < buckets; i++) {
        if (table[i]) {
            size = table[i]->get_list_count() - 1;
        } else {
            size = 0;
        }

        std::cout << "======= BUCKET " << i << " =======" << std::endl;
        std::cout << "Number of collisions in bucket " << i << " = " << size << std::endl;

        // Use a dedicated cursor pointer so table[i] is NOT overwritten/destroyed
        current = table[i];
        while (current) {
            current->display();
            current = current->get_next();
        }
    }
}
int main() {
    // Update this to match your file location
    std::string filename = "/home/phoenix559/CLionProjects/CSCI 115/Lab 7/Oxford English Dictionary.txt";
    int const word_limit = 1000, buckets = 1009;
    int index = 0;
    Hash_Node* temp = nullptr;
    std::pair<std::string*, int> dictionary_array = dict_to_array(filename,word_limit);
    std::string* word_array = dictionary_array.first;
    int const word_count = dictionary_array.second;
    Hash_Node* table[buckets] = {};
    unsigned long h = 0;
    for (int i = 0; i < word_count; i++) {
        h = hash_djb2(word_array[i].c_str());
        index = h % buckets;
        table[index] = new Hash_Node(word_array[i], table[index]);
    }

    display_table(table, buckets);

    for (int i = 0; i < buckets; i++) {
        while (table[i]) {
            temp = table[i];
            table[i] = table[i]->get_next();
            delete temp;

        }
    }
    return 0;
}