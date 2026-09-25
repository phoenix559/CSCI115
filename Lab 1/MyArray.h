//
// Created by phoenix559 on 9/3/26.
//

#ifndef LAB_1_MYARRAY_H
#define LAB_1_MYARRAY_H

#include <stdexcept>


class MyArray {
protected:
    int* data = nullptr;
    int length = 0; // current size of the array
    int capacity = 0; // preset capacity
    void check_size();
    void shift_right(int endIndex);
    void shift_left(int startIndex);
    int recursive_helper(int value, int low, int high);

public:
    MyArray();
    MyArray(int initial_capacity, int value);
    MyArray(const MyArray& other);
    ~MyArray();
    int* get_data();
    int get_length();
    int get_capacity();

    // Methods
    // inserts
    void push_back(int);
    void push_front(int);
    void insert_sorted(int value);

    // deletes
    void pop_front();
    void pop_back();
    void delete_at(int index);
    void delete_first_value(int value);
    void delete_all_value(int value);

    // search
    int linear_search(int value);
    int binary_search_iterative(int value);
    int binary_search_recursive(int value);

    // other
    int count_values(int value);
    void print();
    void resize(int amount_add);
    void resize_double ();

    // sorting
    void selection_sort();
    void insertion_sort();
    void bubble_sort();
    void reverse();
    bool isSorted (int direction, bool allow_duplicates);

    // copying
    MyArray subarray(int start, int end);
    MyArray unique();

    //overloading
    int& operator[](int index); // recommended addition from gemini for "more natural array syntax"
    MyArray& operator=(const MyArray& other);

};
#endif //LAB_1_MYARRAY_H