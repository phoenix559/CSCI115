//
// Created by phoenix559 on 10/29/26.
//
#include <string>
#include <iostream>
#include <fstream>

/*
Implement the Huffman encoding and decoding functions by considering a sequence of characters in a string as an input.

https://cmps-people.ok.ubc.ca/ylucet/DS/Huffman.html

Your code should be in a single file and provide a demo of the encoding and decoding functions.

Your code should be well structured and commented. 
 
 */
class EncoderNode {
private:
    char data = 0;
    int frequency = 0;
    EncoderNode* left_child = nullptr;
    EncoderNode* right_child = nullptr;
    EncoderNode* parent = nullptr;
public:
    EncoderNode() = default;
    EncoderNode(char arg_data, int arg_frequency, EncoderNode* arg_left = nullptr, EncoderNode* arg_right = nullptr,
        EncoderNode* arg_parent = nullptr):data(arg_data), frequency(arg_frequency), left_child(arg_left),
        right_child(arg_right), parent(arg_parent) {};
    ~EncoderNode() = default;
    char get_data(){return data;}
    int get_frequency(){return frequency;}
    EncoderNode* get_parent(){return parent;}
    EncoderNode* get_right_child(){return right_child;}
    EncoderNode* get_left_child(){return left_child;}
    void set_right_child(EncoderNode* arg_right_child){right_child = arg_right_child;}
    void set_left_child(EncoderNode* arg_left_child){left_child = arg_left_child;}
    void set_parent(EncoderNode* arg_parent){parent = arg_parent;}
};

class EncoderQueue {
private:
    EncoderNode* head = nullptr;
public:
    EncoderQueue() = default;
    EncoderQueue(EncoderNode* arg_head):head(arg_head){};
    ~EncoderQueue();
    
    EncoderNode* get_head();
    void insert(EncoderNode* encoder_node);
    void pop();
    int peek();
    void print();
};

EncoderNode * EncoderQueue::get_head() {
}


int main() {
    std::string input_string;
    int len = 0;
    int chars[256] = {}; 
    unsigned char index = 0;
    
    std::cout << "What string are we encoding?\n";
    std::getline(std::cin, input_string);
    len = input_string.length();
    
    std::cout << "\"" << input_string << "\" has total of " << len << " characters."  << std::endl;
    int count = 0;
    for (int i = 0; i < len; i++) {
        index = input_string[i];
        chars[index]++;
        
    }
    EncoderNode * temp = nullptr;
    int j = 0;
    for (int i = 0; i < 256; i++) { 
        if (chars[i] != 0) {
            std::cout << char(i) << ": " << chars[i] << std::endl;
            count++;
            //temp = new EncoderNode(char(i), chars[i]);
        }
    }
    std::cout << "\"" << input_string << "\" has " << count << " unique characters."  << std::endl;

    
    
    // input string
    // parse string and store into array of 126 chars, incrementing the value of the cell by 1.  
    // 
    return 0;
}
