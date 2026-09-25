//
// Created by phoenix559 on 9/24/26.
//
#include "Recursive_Sort.h"


void Lab5::merge_sort_starter() {
    int low = 0;
    int high = length - 1;
    merge_sort(low, high);
}

void ::Lab5::merge_sort(int low, int high) {
    if (length == 0) {
        return;
    }
    else if (length == 1) {
        return;
    }
    int mid = low + (high - low) / 2;
    merge_sort(low, mid);
    merge_sort( mid + 1, high);
    merge(low, mid, high);

}

void Lab5::merge(int low, int mid, int high) {

}

int main() {
    MyArray arr = MyArray();
}