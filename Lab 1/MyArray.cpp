#include "MyArray.h"
#include <iostream>



MyArray::MyArray()
{
    data = nullptr;
    length = 0;
    capacity = 0;
}

MyArray::MyArray(int initial_capacity, int value)
{
    if (initial_capacity <= 0) {
        throw std::invalid_argument("initial_capacity must be greater than 0");
    }
    length = initial_capacity;
    capacity = initial_capacity;
    data =  new int [capacity]; //instantiate new array with predetermined "capacity"

    for (int i = 0; i < capacity; i++) {
        data[i] = value; // sets value of element[0]
    }
}

MyArray::MyArray(const MyArray& other): MyArray()
{
    if (other.data != nullptr) {
        length = other.length;
        capacity = other.capacity;
        data = new int [capacity];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }
}

MyArray::~MyArray()
{
    delete[] data;
    data = nullptr;
    length = 0;
    capacity = 0;
}

int * MyArray::get_data()
{
    return data;
}

int MyArray::get_length()
{
    return length;
}

int MyArray::get_capacity()
{
    return capacity;
}
void MyArray::shift_right(int endIndex) {
    for (int i = length - 1; i >= endIndex; i--) {
        data[i+1] = data[i];
    }
}
void MyArray::shift_left(int startIndex) {
    for (int i = startIndex; i < length -1; i++) {
        data[i] = data[i + 1];
    }
}
void MyArray::push_back(int value)
{
    check_size();
    data[length] = value;
    length++;
}

void MyArray::push_front(int value)
{
    check_size();
    shift_right(0);
    data[0] = value;
    length++;
}

void MyArray::insert_sorted(int value)
{
    check_size();
    int index = 0;
    while (index < length && data[index] < value) {
        index++;
    }
    shift_right(index);
    data[index] = value;
    length++;
}

void MyArray::pop_front()
{
    if (length > 0) {
        shift_left(0);
        length--;
    }
}

void MyArray::pop_back()
{
    if (length > 0) {
        length--;
    }
}

void MyArray::delete_at(int index) {
    if (length > 0 && index >= 0 && index < length ) {
        shift_left(index);
        length--;
    }
}

void MyArray::delete_first_value(int value)
{
    int index = linear_search(value);
    if (index != -1) {
        delete_at(index);
    }
}

void MyArray::delete_all_value(int value) {
    int writeIndex = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] != value) {
            data[writeIndex] = data[i];
            writeIndex++;
        }
    }
    length = writeIndex;
}

int MyArray::linear_search(int value)
{
    for (int i = 0; i < length; i++) {
        if (data[i] == value) {
            return i;
        }
    }
    return -1;
}

int MyArray::binary_search_iterative(int value) {
    int low = 0, high = length - 1, mid = 0;
    while (low <= high) {
        mid = (high + low) / 2;
        if (data[mid] == value) {
            return mid;
        }
        if (data[mid] > value) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return -1;
}

int MyArray::binary_search_recursive(int value) {
    if (length == 0) {
        return -1;
    }
    return recursive_helper(value,0,length-1);
}
int MyArray::recursive_helper(int value, int low, int high){
    if (low > high) {
        return -1;
    }
    int mid = (low + high) / 2;
    if (data[mid] == value) {
        return mid;
    }
    if (data[mid] > value) {
        return recursive_helper(value, low, mid - 1);
    }
    return recursive_helper(value, mid + 1, high);
}

int MyArray::count_values(int value) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (data[i] == value) {
            count++;
        }
    }
    return count;
}
void MyArray::insertion_sort() {
    int step = 0;
    bool done = false;
    for (int i = 0; i < length - 1; i++) {
        int j = i + 1;
    }
}
void MyArray::bubble_sort() {

}
void MyArray::selection_sort()
{
    for (int i = 0; i < length; i++) {
        int min_index = i;
        for (int j = i + 1; j < length; j++) {
            if (data[j] < data[min_index]) {
                min_index = j;
            }
        }
        int temp = data[min_index];
        data[min_index] = data[i];
        data[i] = temp;
    }
}

void MyArray::reverse() {
    int temp = 0;
    int left = 0, right = length - 1;
    while (left < right) {
        temp = data[left];
        data[left] = data[right];
        data[right] = temp;
        left++;
        right--;
    }
}

MyArray MyArray::subarray(int start, int end) {
    if (start < 0 || end >= length || start > end) {
        throw std::out_of_range("start out of range");
    }
    int newCapacity = end - start + 1;
    int writeIndex = 0;
    MyArray newArray = MyArray(newCapacity,0);
    for (int i = start; i <= end; i++) {
        newArray.data[writeIndex] = data[i];
        writeIndex++;
    }
    return newArray;
}

MyArray MyArray::unique() {
    MyArray newArray = MyArray();
    for (int i = 0; i < length; i++) {
        int value = data[i];
        int found = newArray.linear_search(value);
        if (found == -1) {
            newArray.push_back(value);
        }
    }
    return newArray;
}

void MyArray::print()
{
    std::cout << "data = (";
        for (int i = 0; i < length; i++) {
            std::cout << data[i];
            if (i != length - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ")" << std::endl;


    std::cout << "length = " << length << std::endl;
    std::cout << "capacity = " << capacity << std::endl;
}

int & MyArray::operator[](int index)
{
    if (index < 0 || index >= length) {
        throw std::out_of_range("index out of range");
    }
    return data[index];
}

MyArray & MyArray::operator=(const MyArray &other) {
    /*Step 1: Check for Self-Assignment

        Check if the current object's address matches the incoming object's address (this == &other).

        If they are the same instance (e.g., arr1 = arr1;), do nothing and return *this immediately to avoid deleting your own memory before copying.
*/
    if (this == &other) {
        return *this;
    }
    /*Step 2: Free Existing Dynamic Memory

        Because the current object already has its own allocated heap memory, release it using delete[] data;.
*/
    delete[] data;
    /*Step 3: Deep Copy the State and Data

        Copy length and capacity from other.

        If other.data is not null, allocate a new heap array: data = new int[capacity];.

        Copy every element from other.data into data using a loop (or set data = nullptr if other.data is empty).
*/
    length = other.length;
    capacity = other.capacity;
    if (other.data != nullptr) {
        data = new int[capacity];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }
    else {
        data = nullptr;
    }
    /*
    Step 4: Return a Reference to the Current Object

        End the function by returning *this (enabling chained assignment like a = b = c;).
        */
    return *this;
}

void MyArray::resize(int add_amount = 100) {
    int new_capacity = capacity + add_amount;
    int* new_data  = new int [new_capacity];
    for (int i = 0; i < length; i++) {
        new_data[i] = data[i];
    }
    delete [] data;
    data = new_data;
    capacity = new_capacity;
}
void MyArray::resize_double () {
    int new_capacity = capacity * 2;
    int* new_data  = new int [new_capacity];
    for (int i = 0; i < length; i++) {
        new_data[i] = data[i];
    }
    delete [] data;
    data = new_data;
    capacity = new_capacity;
}


void MyArray::check_size()
{
    if (length == capacity) {
        resize();
    }
}