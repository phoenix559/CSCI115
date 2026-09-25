//
// Created by phoenix559 on 9/19/26.
//
#include "../Lab 1/MyArray.h"
#include <iostream>

void MyArray::insertion_sort() {
    int temp = 0;
    for (int i = 1; i < length; i++){
        int j = i;
        while (j >= 1 && data[j] < data[j - 1] ) {
            temp = data[j];
            data[j] = data[j-1];
            data[j-1] = temp;
            j--;
        }
    }
}
void MyArray::bubble_sort() {
    bool done = false;
    int j = 0;
    int temp = 0;
    while (!done) {
        done = true;
        for (int i = 0; i < length - 1 - j; i++) {
            if (data[i] > data[i+1]) {
                done = false;
                temp = data [i+1];
                data[i+1] = data[i];
                data[i] = temp;
            }
        }
        j++;
    }
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
bool MyArray::isSorted (int direction, bool allow_duplicates) {
    // direction = +1 if sorted smaller to larger, -1 if larger to smaller
    if (length == 0||length == 1)
        return true;
    int i = 0;
    bool sorted = true, sorting_condition = true;
    while (i < length - 1 && sorted) {
        if (allow_duplicates) // non descending order
            sorting_condition = direction * data[i] <= direction * data[i + 1];
        else // strictly ascending order
            sorting_condition = direction * data[i] < direction * data[i + 1];

        if (!sorting_condition) {
            sorted = false;
        }
        i++;
    }
    return sorted;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "MyArray.h"

// Case 1: Random array of size n
MyArray generate_case1_array(int n) {
    MyArray case1_array(n, 0);
    for (int i = 0; i < n; i++) {
        case1_array[i] = std::rand() % 100000;
    }
    return case1_array;
}

// Case 2: Sorted array of size n (0 to n - 1)
MyArray generate_case2_array(int n) {
    MyArray case2_array(n, 0);
    for (int i = 0; i < n; i++) {
        case2_array[i] = i;
    }
    return case2_array;
}

// Case 3: 90% sorted array (uses Case 2 baseline, swaps 10%)
MyArray generate_case3_array(int n) {
    MyArray case3_array = generate_case2_array(n);
    int total_swaps = n / 10;
    for (int i = 0; i < total_swaps; i++) {
        int index1 = std::rand() % n;
        int index2 = std::rand() % n;
        int temp = case3_array[index1];
        case3_array[index1] = case3_array[index2];
        case3_array[index2] = temp;
    }
    return case3_array;
}

// Case 4: 50% sorted array (uses Case 2 baseline, swaps 50%)
MyArray generate_case4_array(int n) {
    MyArray case4_array = generate_case2_array(n);
    int total_swaps = n / 2;
    for (int i = 0; i < total_swaps; i++) {
        int index1 = std::rand() % n;
        int index2 = std::rand() % n;
        int temp = case4_array[index1];
        case4_array[index1] = case4_array[index2];
        case4_array[index2] = temp;
    }
    return case4_array;
}

double time_bubble_sort(MyArray source_array, int case_number) {
    // Deep copy so original array remains unsorted
    MyArray test_array = source_array;
    int n = test_array.get_length();

    std::cout << "\nCase " << case_number << " bubble sort (Size " << n << ")" << std::endl;
    std::chrono::high_resolution_clock::time_point begin_time = std::chrono::high_resolution_clock::now();
    std::cout << "beginning time recorded." << std::endl;

    test_array.bubble_sort();

    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
    std::cout << "end time recorded." << std::endl;

    std::chrono::duration<double, std::milli> duration = end_time - begin_time;
    double total_time = duration.count();
    std::cout << "total time: " << total_time << " ms" << std::endl;

    if (test_array.isSorted(1, true)) {
        std::cout << "verification: SORTED" << std::endl;
    } else {
        std::cout << "verification: FAILED" << std::endl;
    }

    return total_time;
}

double time_selection_sort(MyArray source_array, int case_number) {
    // Deep copy so original array remains unsorted
    MyArray test_array = source_array;
    int n = test_array.get_length();

    std::cout << "\nCase " << case_number << " selection sort (Size " << n << ")" << std::endl;
    std::chrono::high_resolution_clock::time_point begin_time = std::chrono::high_resolution_clock::now();
    std::cout << "beginning time recorded." << std::endl;

    test_array.selection_sort();

    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
    std::cout << "end time recorded." << std::endl;

    std::chrono::duration<double, std::milli> duration = end_time - begin_time;
    double total_time = duration.count();
    std::cout << "total time: " << total_time << " ms" << std::endl;

    if (test_array.isSorted(1, true)) {
        std::cout << "verification: SORTED" << std::endl;
    } else {
        std::cout << "verification: FAILED" << std::endl;
    }

    return total_time;
}

double time_insertion_sort(MyArray source_array, int case_number) {
    // Deep copy so original array remains unsorted
    MyArray test_array = source_array;
    int n = test_array.get_length();

    std::cout << "\nCase " << case_number << " insertion sort (Size " << n << ")" << std::endl;
    std::chrono::high_resolution_clock::time_point begin_time = std::chrono::high_resolution_clock::now();
    std::cout << "beginning time recorded." << std::endl;

    test_array.insertion_sort();

    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
    std::cout << "end time recorded." << std::endl;

    std::chrono::duration<double, std::milli> duration = end_time - begin_time;
    double total_time = duration.count();
    std::cout << "total time: " << total_time << " ms" << std::endl;

    if (test_array.isSorted(1, true)) {
        std::cout << "verification: SORTED" << std::endl;
    } else {
        std::cout << "verification: FAILED" << std::endl;
    }

    return total_time;
}

void run_all_benchmarks() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int sizes[4] = {100, 1000, 10000, 100000};
    int total_sizes = 4;

    for (int i = 0; i < total_sizes; i++) {
        int n = sizes[i];

        std::cout << "\n==========================================" << std::endl;
        std::cout << "TESTING ARRAY SIZE: " << n << std::endl;
        std::cout << "==========================================" << std::endl;

        // Case 1: Random
        MyArray case1_array = generate_case1_array(n);
        double c1_bubble = time_bubble_sort(case1_array, 1);
        double c1_selection = time_selection_sort(case1_array, 1);
        double c1_insertion = time_insertion_sort(case1_array, 1);

        // Case 2: Sorted
        MyArray case2_array = generate_case2_array(n);
        double c2_bubble = time_bubble_sort(case2_array, 2);
        double c2_selection = time_selection_sort(case2_array, 2);
        double c2_insertion = time_insertion_sort(case2_array, 2);

        // Case 3: 90% Sorted
        MyArray case3_array = generate_case3_array(n);
        double c3_bubble = time_bubble_sort(case3_array, 3);
        double c3_selection = time_selection_sort(case3_array, 3);
        double c3_insertion = time_insertion_sort(case3_array, 3);

        // Case 4: 50% Sorted
        MyArray case4_array = generate_case4_array(n);
        double c4_bubble = time_bubble_sort(case4_array, 4);
        double c4_selection = time_selection_sort(case4_array, 4);
        double c4_insertion = time_insertion_sort(case4_array, 4);

        // Summary for spreadsheet
        std::cout << "\nSummary for Size " << n << " (Milliseconds):" << std::endl;
        std::cout << "Case,Bubble,Selection,Insertion" << std::endl;
        std::cout << "Case 1," << c1_bubble << "," << c1_selection << "," << c1_insertion << std::endl;
        std::cout << "Case 2," << c2_bubble << "," << c2_selection << "," << c2_insertion << std::endl;
        std::cout << "Case 3," << c3_bubble << "," << c3_selection << "," << c3_insertion << std::endl;
        std::cout << "Case 4," << c4_bubble << "," << c4_selection << "," << c4_insertion << std::endl;
    }
}

int main() {
    run_all_benchmarks();
    return 0;
}